import base64
import json
import os
import zlib
import asyncio
import sys
import aiohttp
import logging
import time
from datetime import datetime
from loguru import logger
from fastapi import FastAPI
from fastf1_livetiming.signalr.connection import Connection
import uvicorn
import requests

app = FastAPI()

# --- Configuration ---
LOG_LEVEL = os.getenv("LOG_LEVEL", "INFO").upper()
logger.remove()
logger.add(sys.stderr, level=LOG_LEVEL)

SIGNALR_URL = "https://livetiming.formula1.com/signalr"
JOLPICA_BASE = "https://api.jolpi.ca/ergast/f1"

# --- State ---
class F1State:
    def __init__(self):
        self.last_data_time = 0
        self.session_info = {}
        self.timing_data = {}
        self.weather_data = {}
        self.track_status = "AllClear"
        self.lap_count = {"current": 0, "total": 0}
        self.driver_list = {}
        self.is_live = False
        self.upcoming_race = {}
        self.previous_race = {}

state = F1State()

# --- Helper Logic ---
def decode_message(payload):
    try:
        if not isinstance(payload, str) or len(payload) < 5:
            return None
        missing_padding = len(payload) % 4
        if missing_padding:
            payload += "=" * (4 - missing_padding)
        data = base64.b64decode(payload)
        return zlib.decompress(data, -zlib.MAX_WBITS).decode("utf-8")
    except Exception:
        return None

def update_live_status():
    now = time.time()
    if now - state.last_data_time < 300:
        state.is_live = True
    else:
        state.is_live = False

async def fetch_race_schedule():
    """Fetch next and previous race from corrected Jolpica-F1 API (async)"""
    try:
        async with aiohttp.ClientSession() as session:
            # Next Race
            async with session.get(f"{JOLPICA_BASE}/current/next.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    races = data.get('MRData', {}).get('RaceTable', {}).get('Races', [])
                    if races:
                        race = races[0]
                        state.upcoming_race = {
                            "name": race.get('raceName'),
                            "circuit": race.get('Circuit', {}).get('circuitName'),
                            "date": f"{race.get('date')}T{race.get('time')}",
                            "locality": race.get('Circuit', {}).get('Location', {}).get('locality')
                        }
            # Previous Race
            async with session.get(f"{JOLPICA_BASE}/current/last/results.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    races = data.get('MRData', {}).get('RaceTable', {}).get('Races', [])
                    if races:
                        race = races[0]
                        results = race.get('Results', [])
                        if results:
                            winner = results[0].get('Driver', {})
                            state.previous_race = {
                                "name": race.get('raceName'),
                                "winner": f"{winner.get('givenName')} {winner.get('familyName')}",
                                "team": results[0].get('Constructor', {}).get('name')
                            }
    except Exception as e:
        logger.error(f"Error fetching race schedule: {e}")

# --- Message Handlers ---
async def on_feed(args):
    try:
        topic = None
        for arg in args:
            if arg in ["TimingData", "WeatherData", "SessionInfo", "LapCount", "DriverList", "TrackStatus", "Heartbeat"]:
                topic = arg
                continue

            if topic == "Heartbeat" or not topic:
                continue

            state.last_data_time = time.time()
            state.is_live = True

            if isinstance(arg, (dict, str)):
                decoded = arg if isinstance(arg, dict) else decode_message(arg)
                if not decoded: continue
                if isinstance(decoded, str): decoded = json.loads(decoded)

                if topic == "TimingData":
                    lines = decoded.get("Lines", {})
                    for dnum, line in lines.items():
                        if dnum not in state.timing_data: state.timing_data[dnum] = {}
                        td = state.timing_data[dnum]
                        if "Position" in line: td["pos"] = line["Position"]
                        if "GapToLeader" in line: td["gap"] = line["GapToLeader"]
                        if "IntervalToNext" in line: td["int"] = line["IntervalToNext"]
                        if "LastLapTime" in line: td["last"] = line["LastLapTime"].get("Value")
                        stints = line.get("Stints", [])
                        if stints:
                            last_stint = list(stints.values())[-1] if isinstance(stints, dict) else stints[-1]
                            td["compound"] = last_stint.get("Compound")

                elif topic == "WeatherData":
                    state.weather_data = {"air": decoded.get("AirTemp"), "track": decoded.get("TrackTemp"), "hum": decoded.get("Humidity"), "rain": decoded.get("Rainfall") == "1"}
                elif topic == "SessionInfo":
                    state.session_info = {"name": decoded.get("SessionName"), "type": decoded.get("Type"), "circuit": decoded.get("CircuitName")}
                elif topic == "LapCount":
                    state.lap_count = {"current": decoded.get("CurrentLap"), "total": decoded.get("TotalLaps")}
                elif topic == "DriverList":
                    for dnum, info in decoded.items():
                        state.driver_list[dnum] = {"name": info.get("FullName"), "team": info.get("TeamName"), "color": info.get("TeamColour"), "abbrev": info.get("Tla")}
                elif topic == "TrackStatus":
                    state.track_status = decoded.get("Status", "AllClear")
    except Exception as e:
        logger.error(f"Error in on_feed: {e}")

# --- API Endpoints ---
@app.get("/status")
async def get_status():
    update_live_status()

    # If we have no session info, it's not really a live session we can display
    effective_live = state.is_live and bool(state.session_info.get("name"))

    if not effective_live and (not state.upcoming_race or not state.previous_race):
        await fetch_race_schedule()

    sorted_timing = []
    for dnum, data in state.timing_data.items():
        dinfo = state.driver_list.get(dnum, {"name": f"D{dnum}", "team": "UNK", "color": "FFFFFF", "abbrev": dnum})
        sorted_timing.append({
            "num": dnum,
            "name": dinfo["abbrev"],
            "team": dinfo["team"],
            "pos": data.get("pos", "99"),
            "gap": data.get("gap", ""),
            "comp": data.get("compound", ""),
            "col": dinfo["color"]
        })
    sorted_timing.sort(key=lambda x: int(x['pos']) if str(x['pos']).isdigit() else 99)

    return {
        "live": effective_live,
        "session": state.session_info,
        "weather": state.weather_data,
        "track": state.track_status,
        "laps": state.lap_count,
        "timing": sorted_timing[:10],
        "upcoming": state.upcoming_race,
        "previous": state.previous_race
    }

@app.get("/previous_results")
async def get_previous_results():
    """Fetch results from the last race with Name, Surname, Constructor, Position, and Points"""
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{JOLPICA_BASE}/current/last/results.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    races = data.get('MRData', {}).get('RaceTable', {}).get('Races', [])
                    if races:
                        race = races[0]
                        results = race.get('Results', [])
                        formatted_results = []
                        for res in results:
                            driver = res.get('Driver', {})
                            constructor = res.get('Constructor', {})
                            formatted_results.append({
                                "firstName": driver.get('givenName'),
                                "lastName": driver.get('familyName'),
                                "constructor": constructor.get('name'),
                                "position": res.get('position'),
                                "points": res.get('points')
                            })
                        return {
                            "raceName": race.get('raceName'),
                            "results": formatted_results
                        }
        return {"error": "No results found"}
    except Exception as e:
        logger.error(f"Error fetching previous results: {e}")
        return {"error": str(e)}

# --- SignalR Background Task ---
async def signalr_worker():
    session = requests.Session()
    session.headers = {"User-agent": "BestHTTP", "Accept-Encoding": "gzip, identity", "Connection": "keep-alive"}
    while True:
        try:
            conn = Connection(SIGNALR_URL, session=session)
            hub = conn.register_hub("Streaming")
            async def on_connect():
                topics = ["TimingData", "WeatherData", "SessionInfo", "LapCount", "DriverList", "TrackStatus", "Heartbeat"]
                hub.server.invoke("Subscribe", topics)
                logger.info("Subscribed to F1 topics")
            conn.connected += on_connect
            hub.client.on("feed", on_feed)
            await conn.start(asyncio.get_running_loop())
        except Exception as e:
            logger.error(f"SignalR worker error: {e}")
        await asyncio.sleep(10)

@app.on_event("startup")
async def startup_event():
    asyncio.create_task(signalr_worker())
    asyncio.create_task(fetch_race_schedule())

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
