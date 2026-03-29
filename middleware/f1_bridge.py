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
try:
    from fastf1_livetiming.signalr.connection import Connection
except ImportError:
    Connection = None
import uvicorn
import requests

app = FastAPI()

# --- Configuration ---
# Force LOG_LEVEL to DEBUG to see everything
LOG_LEVEL = "DEBUG" 
logger.remove()
logger.add(sys.stderr, level=LOG_LEVEL)

# Also capture the standard logging used by the SignalR library
logging.basicConfig(level=logging.DEBUG)
SIGNALR_URL = "https://livetiming.formula1.com/signalr"
JOLPICA_BASE = "https://api.jolpi.ca/ergast/f1"

# --- Mappings ---
TRACK_STATUS_MAP = {
    "1": "Clear",
    "2": "Yellow Flag",
    "4": "Safety Car",
    "5": "Red Flag",
    "6": "VSC",
    "7": "VSC Ending"
}
FLAG_MAPPING = {
    "British": "🇬🇧", "German": "🇩🇪", "Italian": "🇮🇹", "Monegasque": "🇲🇨",
    "French": "🇫🇷", "New Zealander": "🇳🇿", "Austrian": "🇦🇹", "Spanish": "🇪🇸",
    "Argentine": "🇦🇷", "Finnish": "🇫🇮", "Mexican": "🇲🇽", "Dutch": "🇳🇱",
    "Australian": "🇦🇺", "Brazilian": "🇧🇷", "Thai": "🇹🇭", "Japanese": "🇯🇵",
    "Canadian": "🇨🇦", "American": "🇺🇸", "Danish": "🇩🇰", "Chinese": "🇨🇳",
    "United Kingdom": "🇬🇧", "Germany": "🇩🇪", "Italy": "🇮🇹", "Monaco": "🇲🇨",
    "France": "🇫🇷", "New Zealand": "🇳🇿", "Austria": "🇦🇹", "Spain": "🇪🇸",
    "Argentina": "🇦🇷", "Finland": "🇫🇮", "Mexico": "🇲🇽", "Netherlands": "🇳🇱",
    "Australia": "🇦🇺", "Brazil": "🇧🇷", "Thailand": "🇹🇭", "Japan": "🇯🇵",
    "Canada": "🇨🇦", "USA": "🇺🇸", "Denmark": "🇩🇰", "China": "🇨🇳",
    "UK": "🇬🇧", "United Arab Emirates": "🇦🇪", "Saudi Arabia": "🇸🇦", "Bahrain": "🇧🇭",
    "Hungary": "🇭🇺", "Belgium": "🇧🇪", "Singapore": "🇸🇬", "Azerbaijan": "🇦🇿"
}

ISO_MAPPING = {
    "British": "gb", "German": "de", "Italian": "it", "Monegasque": "mc",
    "French": "fr", "New Zealander": "nz", "Austrian": "at", "Spanish": "es",
    "Argentine": "ar", "Finnish": "fi", "Mexican": "mx", "Dutch": "nl",
    "Australian": "au", "Brazilian": "br", "Thai": "th", "Japanese": "jp",
    "Canadian": "ca", "American": "us", "Danish": "dk", "Chinese": "cn",
    "United Kingdom": "gb", "Germany": "de", "Italy": "it", "Monaco": "mc",
    "France": "fr", "New Zealand": "nz", "Austria": "at", "Spain": "es",
    "Argentina": "ar", "Finland": "fi", "Mexico": "mx", "Netherlands": "nl",
    "Australia": "au", "Brazil": "br", "Thailand": "th", "Japan": "jp",
    "Canada": "ca", "USA": "us", "Denmark": "dk", "China": "cn",
    "UK": "gb", "United Arab Emirates": "ae", "Saudi Arabia": "sa", "Bahrain": "bh",
    "Hungary": "hu", "Belgium": "be", "Singapore": "sg", "Azerbaijan": "az"
}

TEAM_COLORS = {
    "Mercedes": "27F4D2", "Ferrari": "E80020", "Red Bull": "3671C6",
    "Red Bull Racing": "3671C6", "McLaren": "FF8000", "Aston Martin": "229971",
    "Alpine F1 Team": "0093CC", "Alpine": "0093CC", "RB F1 Team": "6692FF",
    "RB": "6692FF", "Haas F1 Team": "B6BABD", "Haas": "B6BABD",
    "Williams": "64C4FF", "Audi": "52E252", "Sauber": "52E252",
    "Cadillac F1 Team": "FFFFFF", "Cadillac": "FFFFFF",
    "Racing Bulls": "6692FF", "Kick Sauber": "52E252"
}

DRIVER_MAPPING = {
    "63": {"abbrev": "RUS", "name": "George Russell", "team": "Mercedes", "color": "27F4D2"},
    "12": {"abbrev": "ANT", "name": "Andrea Kimi Antonelli", "team": "Mercedes", "color": "27F4D2"},
    "16": {"abbrev": "LEC", "name": "Charles Leclerc", "team": "Ferrari", "color": "E80020"},
    "44": {"abbrev": "HAM", "name": "Lewis Hamilton", "team": "Ferrari", "color": "E80020"},
    "87": {"abbrev": "BEA", "name": "Oliver Bearman", "team": "Haas F1 Team", "color": "B6BABD"},
    "1": {"abbrev": "NOR", "name": "Lando Norris", "team": "McLaren", "color": "FF8000"},
    "10": {"abbrev": "GAS", "name": "Pierre Gasly", "team": "Alpine F1 Team", "color": "0093CC"},
    "3": {"abbrev": "VER", "name": "Max Verstappen", "team": "Red Bull", "color": "3671C6"},
    "30": {"abbrev": "LAW", "name": "Liam Lawson", "team": "RB F1 Team", "color": "6692FF"},
    "41": {"abbrev": "LIN", "name": "Arvid Lindblad", "team": "RB F1 Team", "color": "6692FF"},
    "6": {"abbrev": "HAD", "name": "Isack Hadjar", "team": "Red Bull", "color": "3671C6"},
    "81": {"abbrev": "PIA", "name": "Oscar Piastri", "team": "McLaren", "color": "FF8000"},
    "55": {"abbrev": "SAI", "name": "Carlos Sainz", "team": "Williams", "color": "64C4FF"},
    "5": {"abbrev": "BOR", "name": "Gabriel Bortoleto", "team": "Audi", "color": "52E252"},
    "43": {"abbrev": "COL", "name": "Franco Colapinto", "team": "Alpine F1 Team", "color": "0093CC"},
    "31": {"abbrev": "OCO", "name": "Esteban Ocon", "team": "Haas F1 Team", "color": "B6BABD"},
    "27": {"abbrev": "HUL", "name": "Nico Hülkenberg", "team": "Audi", "color": "52E252"},
    "23": {"abbrev": "ALB", "name": "Alexander Albon", "team": "Williams", "color": "64C4FF"},
    "77": {"abbrev": "BOT", "name": "Valtteri Bottas", "team": "Cadillac F1 Team", "color": "FFFFFF"},
    "11": {"abbrev": "PER", "name": "Sergio Pérez", "team": "Cadillac F1 Team", "color": "FFFFFF"},
    "14": {"abbrev": "ALO", "name": "Fernando Alonso", "team": "Aston Martin", "color": "229971"},
    "18": {"abbrev": "STR", "name": "Lance Stroll", "team": "Aston Martin", "color": "229971"}
}

# --- State Persistence ---
STATE_FILE = "f1_state.json"

class F1State:
    def __init__(self):
        self.last_data_time = 0
        self.session_key = 0
        self.session_info = {}
        self.timing_data = {}
        self.weather_data = {}
        self.track_status = "AllClear"
        self.lap_count = {"current": 0, "total": 0}
        self.driver_list = {}
        self.is_live = False
        self.upcoming_race = {}
        self.previous_race = {}
        self.race_control_message = ""

    def save(self):
        try:
            data = {
                "last_data_time": self.last_data_time,
                "session_key": self.session_key,
                "session_info": self.session_info,
                "timing_data": self.timing_data,
                "weather_data": self.weather_data,
                "track_status": self.track_status,
                "lap_count": self.lap_count,
                "driver_list": self.driver_list,
                "race_control_message": self.race_control_message,
                "timestamp": time.time()
            }
            with open(STATE_FILE, 'w') as f:
                json.dump(data, f)
            logger.debug("State saved to disk")
        except Exception as e:
            logger.error(f"Error saving state: {e}")

    def load(self):
        if not os.path.exists(STATE_FILE):
            return
        try:
            with open(STATE_FILE, 'r') as f:
                data = json.load(f)

            # Don't load if older than 12 hours
            if time.time() - data.get("timestamp", 0) > 43200:
                logger.info("Persisted state is too old, ignoring")
                return

            self.last_data_time = data.get("last_data_time", 0)
            self.session_key = data.get("session_key", 0)
            self.session_info = data.get("session_info", {})
            self.timing_data = data.get("timing_data", {})
            self.weather_data = data.get("weather_data", {})
            self.track_status = data.get("track_status", "AllClear")
            self.lap_count = data.get("lap_count", {"current": 0, "total": 0})
            self.driver_list = data.get("driver_list", {})
            self.race_control_message = data.get("race_control_message", "")

            # Recalculate is_live
            update_live_status()
            logger.info("State recovered from disk")
        except Exception as e:
            logger.error(f"Error loading state: {e}")

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
    diff = now - state.last_data_time
    if diff < 300:
        state.is_live = True
    else:
        state.is_live = False

    # Clear session-specific data if no live data for > 3 hours
    if diff > 10800 and state.timing_data:
        logger.info("No live data for > 3 hours, clearing session data")
        state.timing_data = {}
        state.lap_count = {"current": 0, "total": 0}
        state.race_control_message = ""

def get_team_color(name):
    if not name:
        return "FFFFFF"

    # Try exact match first
    if name in TEAM_COLORS:
        return TEAM_COLORS[name]

    # Try partial matches
    for k, v in TEAM_COLORS.items():
        if k.lower() in name.lower() or name.lower() in k.lower():
            return v

    return "FFFFFF"

def format_sessions(race):
    sessions = []
    session_map = {
        "FirstPractice": "FP1",
        "SecondPractice": "FP2",
        "ThirdPractice": "FP3",
        "Qualifying": "Qualifying",
        "Sprint": "Sprint",
        "SprintQualifying": "Sprint Quali"
    }

    for key, label in session_map.items():
        s = race.get(key)
        if s:
            sessions.append({
                "name": label,
                "time": f"{s.get('date')}T{s.get('time')}"
            })

    # Add main race
    sessions.append({
        "name": "Race",
        "time": f"{race.get('date')}T{race.get('time')}"
    })

    # Sort sessions by time
    sessions.sort(key=lambda x: x['time'])
    return sessions

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
                        country = race.get('Circuit', {}).get('Location', {}).get('country', '')

                        sessions = format_sessions(race)
                        state.upcoming_race = {
                            "name": race.get('raceName'),
                            "circuit": race.get('Circuit', {}).get('circuitName'),
                            "date": f"{race.get('date')}T{race.get('time')}",
                            "locality": race.get('Circuit', {}).get('Location', {}).get('locality'),
                            "country": country,
                            "flag": FLAG_MAPPING.get(country, "🏁"),
                            "flagCode": ISO_MAPPING.get(country, "un"),
                            "sessions": sessions
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
                            team = results[0].get('Constructor', {}).get('name', '')
                            country = race.get('Circuit', {}).get('Location', {}).get('country', '')
                            winner_nat = winner.get('nationality', '')
                            state.previous_race = {
                                "name": race.get('raceName'),
                                "circuit": race.get('Circuit', {}).get('circuitName'),
                                "winner": f"{winner.get('givenName')} {winner.get('familyName')}",
                                "winnerFlag": FLAG_MAPPING.get(winner_nat, "🏁"),
                                "winnerFlagCode": ISO_MAPPING.get(winner_nat, "un"),
                                "team": team,
                                "teamColor": int(get_team_color(team), 16),
                                "country": country,
                                "flag": FLAG_MAPPING.get(country, "🏁"),
                                "flagCode": ISO_MAPPING.get(country, "un")
                            }
    except Exception as e:
        logger.error(f"Error fetching race schedule: {e}")

# --- Message Handlers ---
async def on_feed(args):
    logger.debug(f"RAW SIGNALR DATA: {args}")
    try:
        topic = None
        any_updates = False
        for arg in args:
            if arg in ["TimingData", "WeatherData", "SessionInfo", "LapCount", "DriverList", "TrackStatus", "RaceControlMessages", "Heartbeat", "TimingAppData", "TimingStats"]:
                topic = arg
                logger.debug(f"SignalR Topic: {topic}")
                continue

            if topic == "Heartbeat" or not topic:
                continue

            # Check if it's actual data and not an empty update
            if isinstance(arg, (dict, str)) and len(str(arg)) > 2:
                state.last_data_time = time.time()
                state.is_live = True
                any_updates = True

            if isinstance(arg, (dict, str)):
                decoded = arg if isinstance(arg, dict) else decode_message(arg)
                if not decoded: continue
                if isinstance(decoded, str): decoded = json.loads(decoded)

                logger.debug(f"Data for {topic}: {str(decoded)[:200]}...")

                if topic == "TimingData":
                    if "SessionPart" in decoded:
                        state.session_info["part"] = decoded["SessionPart"]
                        # Ensure name reflects part if generic
                        if state.session_info.get("name") == "Qualifying":
                             state.session_info["name"] = f"Qualifying {decoded['SessionPart']}"

                    lines = decoded.get("Lines", {})
                    for dnum, line in lines.items():
                        if dnum not in state.timing_data: state.timing_data[dnum] = {}
                        td = state.timing_data[dnum]
                        if "Position" in line: td["pos"] = line["Position"]
                        if "InPit" in line: td["pit"] = line["InPit"]
                        if "PitOut" in line: td["out"] = line["PitOut"]
                        if "KnockedOut" in line: td["knocked"] = line["KnockedOut"]

                        # Status bitmask: 80=InPit, 64=Active, 68=Stopped, 128=Finished/Chequered
                        status_val = line.get("Status", 0)
                        if status_val & 128: td["finished"] = True
                        elif status_val == 64: td["finished"] = False

                        # Gap and Interval handling with dictionary/string flexibility
                        gap = line.get("GapToLeader") or line.get("TimeDiffToFastest")
                        if gap:
                            td["gap"] = gap.get("Value") if isinstance(gap, dict) else gap

                        interval = line.get("IntervalToNext") or line.get("TimeDiffToPositionAhead") or line.get("IntervalToPositionAhead")
                        if interval:
                            td["int"] = interval.get("Value") if isinstance(interval, dict) else interval

                        if "LastLapTime" in line: td["last"] = line["LastLapTime"].get("Value")
                        if "BestLapTime" in line: td["best"] = line["BestLapTime"].get("Value")

                        # BestLapTimes dictionary (segment specific)
                        blts = line.get("BestLapTimes", {})
                        if blts:
                            if "1" in blts and blts["1"].get("Value"): td["q1"] = blts["1"]["Value"]
                            if "2" in blts and blts["2"].get("Value"): td["q2"] = blts["2"]["Value"]
                            if "3" in blts and blts["3"].get("Value"): td["q3"] = blts["3"]["Value"]

                        # Qualifying segments via Stats fallback
                        stats = line.get("Stats", [])
                        if stats:
                            for s in stats:
                                if "Time" in s:
                                    if "Q1" in str(s.get("Text", "")): td["q1"] = s["Time"]
                                    if "Q2" in str(s.get("Text", "")): td["q2"] = s["Time"]
                                    if "Q3" in str(s.get("Text", "")): td["q3"] = s["Time"]

                        stints = line.get("Stints", [])
                        if stints:
                            last_stint = list(stints.values())[-1] if isinstance(stints, dict) else stints[-1]
                            compound = last_stint.get("Compound")
                            if compound:
                                compound = compound.upper()
                                if "SOFT" in compound: td["compound"] = "soft"
                                elif "MEDIUM" in compound: td["compound"] = "medium"
                                elif "HARD" in compound: td["compound"] = "hard"
                                elif "INTER" in compound: td["compound"] = "intermediate"
                                elif "WET" in compound: td["compound"] = "wet"
                                else: td["compound"] = compound.lower()

                elif topic == "TimingAppData":
                    lines = decoded.get("Lines", {})
                    for dnum, line in lines.items():
                        if dnum not in state.timing_data: state.timing_data[dnum] = {}
                        td = state.timing_data[dnum]
                        stints = line.get("Stints")
                        if stints:
                            # stints can be a list or a dict with numeric keys
                            try:
                                if isinstance(stints, dict):
                                    # Get the stint with the highest key
                                    last_key = max(stints.keys(), key=lambda x: int(x))
                                    last_stint = stints[last_key]
                                else:
                                    last_stint = stints[-1]

                                compound = last_stint.get("Compound")
                                if compound:
                                    compound = compound.upper()
                                    if "SOFT" in compound: td["compound"] = "soft"
                                    elif "MEDIUM" in compound: td["compound"] = "medium"
                                    elif "HARD" in compound: td["compound"] = "hard"
                                    elif "INTER" in compound: td["compound"] = "intermediate"
                                    elif "WET" in compound: td["compound"] = "wet"
                                    else: td["compound"] = compound.lower()
                            except (ValueError, IndexError):
                                continue

                elif topic == "TimingStats":
                    lines = decoded.get("Lines", {})
                    for dnum, line in lines.items():
                        if dnum not in state.timing_data: state.timing_data[dnum] = {}
                        td = state.timing_data[dnum]
                        pb = line.get("PersonalBestLapTime")
                        if pb and isinstance(pb, dict):
                            td["best_lap_pos"] = pb.get("Position")

                elif topic == "WeatherData":
                    state.weather_data = {"air": decoded.get("AirTemp"), "track": decoded.get("TrackTemp"), "hum": decoded.get("Humidity"), "rain": decoded.get("Rainfall") == "1"}
                elif topic == "SessionInfo":
                    # Detect session change
                    new_key = decoded.get("Key", 0)
                    if new_key != 0 and state.session_key != 0 and new_key != state.session_key:
                        logger.info(f"Session change detected: {state.session_key} -> {new_key}. Clearing timing data.")
                        state.timing_data = {}
                        state.lap_count = {"current": 0, "total": 0}
                        state.race_control_message = ""

                    if new_key != 0:
                        state.session_key = new_key

                    # Determine part (e.g., Q1/Q2/Q3 or FP1/FP2/FP3)
                    name = decoded.get("Name") or decoded.get("SessionName")
                    part = decoded.get("Number") or 1

                    # Fallback to name parsing if Number is missing
                    if part == 1 and name:
                        if "Qualifying 2" in name or "Q2" in name: part = 2
                        elif "Qualifying 3" in name or "Q3" in name: part = 3

                    # Ensure name is descriptive for Quali
                    if name == "Qualifying":
                        name = f"Qualifying {part}"

                    state.session_info = {
                        "name": name,
                        "type": decoded.get("Type"),
                        "circuit": decoded.get("Meeting", {}).get("Circuit", {}).get("ShortName") or decoded.get("CircuitName"),
                        "status": decoded.get("SessionStatus") or decoded.get("Status"),
                        "part": part
                    }
                elif topic == "LapCount":
                    state.lap_count = {"current": decoded.get("CurrentLap"), "total": decoded.get("TotalLaps")}
                elif topic == "DriverList":
                    for dnum, info in decoded.items():
                        if dnum not in state.driver_list:
                            # Pre-fill with static mapping if available
                            state.driver_list[dnum] = DRIVER_MAPPING.get(dnum, {}).copy()

                        # Only update if key exists in info, otherwise keep old value
                        if "FullName" in info: state.driver_list[dnum]["name"] = info["FullName"]
                        if "TeamName" in info: state.driver_list[dnum]["team"] = info["TeamName"]
                        if "TeamColour" in info: state.driver_list[dnum]["color"] = info["TeamColour"]
                        if "Tla" in info: state.driver_list[dnum]["abbrev"] = info["Tla"]
                elif topic == "TrackStatus":
                    status_code = decoded.get("Status", "1")
                    state.track_status = TRACK_STATUS_MAP.get(status_code, "Normal/Clear")
                elif topic == "RaceControlMessages":
                    messages = decoded.get("Messages", {})
                    if messages:
                        if isinstance(messages, dict):
                            # Get the latest message (highest key if they are numeric strings)
                            try:
                                latest_idx = max(messages.keys(), key=lambda x: int(x))
                                state.race_control_message = messages[latest_idx].get("Message", "")
                            except Exception:
                                # Fallback if keys are not integers
                                state.race_control_message = list(messages.values())[-1].get("Message", "")
                        elif isinstance(messages, list):
                            state.race_control_message = messages[-1].get("Message", "")

        if any_updates:
            state.save()

    except Exception as e:
        logger.error(f"Error in on_feed: {e}")

# --- API Endpoints ---
@app.get("/status")
async def get_status():
    update_live_status()

    # Loosen live detection: if we have timing data OR session info (even if name is null), it's live
    has_timing = len(state.timing_data) > 0
    has_session = bool(state.session_info.get("name")) or bool(state.session_info.get("type"))
    effective_live = state.is_live and (has_timing or has_session)

    if not effective_live and (not state.upcoming_race or not state.previous_race):
        await fetch_race_schedule()

    # Ensure session name fallback
    session_info = state.session_info.copy()
    if not session_info.get("name") and session_info.get("type"):
        session_info["name"] = session_info["type"]

    sorted_timing = []
    for dnum, data in state.timing_data.items():
        # Get info from state, fallback to static mapping, then to defaults
        dinfo_state = state.driver_list.get(dnum, {})
        dinfo_static = DRIVER_MAPPING.get(dnum, {})

        drv_name = dinfo_state.get("abbrev") or dinfo_static.get("abbrev") or dinfo_state.get("name") or dinfo_static.get("name") or dnum
        drv_team = dinfo_state.get("team") or dinfo_static.get("team") or "UNK"
        drv_color = dinfo_state.get("color") or dinfo_static.get("color") or "FFFFFF"

        # Favor segment time for Quali
        best_time = data.get("best", "")
        part = session_info.get("part", 0)
        if "Quali" in session_info.get("name", ""):
            is_knocked = data.get("knocked", False)
            if is_knocked:
                 # Pick the latest available segment time
                 best_time = data.get("q3") or data.get("q2") or data.get("q1") or data.get("best", "")
            else:
                 # Only show the best time for the CURRENT segment
                 if part == 1: best_time = data.get("q1", "")
                 elif part == 2: best_time = data.get("q2", "")
                 elif part == 3: best_time = data.get("q3", "")

        sorted_timing.append({
            "num": dnum,
            "name": drv_name,
            "team": drv_team,
            "teamColor": drv_color,
            "pos": data.get("pos", "99"),
            "gap": data.get("gap", ""),
            "int": data.get("int", ""),
            "last": data.get("last", ""),
            "best": best_time,
            "q1": data.get("q1", ""),
            "q2": data.get("q2", ""),
            "q3": data.get("q3", ""),
            "comp": data.get("compound", ""),
            "pit": data.get("pit", False),
            "out": data.get("out", False),
            "fin": data.get("finished", False),
            "fastest": data.get("best_lap_pos") == 1,
            "col": drv_color
        })
    sorted_timing.sort(key=lambda x: int(x['pos']) if str(x['pos']).isdigit() else 99)

    # If session is over, indicate it
    track_display = state.track_status
    if state.session_info.get("status") == "Finished":
        track_display = "Chequered Flag"

    return {
        "live": effective_live,
        "session": session_info,
        "weather": state.weather_data,
        "message": state.race_control_message,
        "track": track_display,
        "laps": state.lap_count,
        "timing": sorted_timing,
        "upcoming": state.upcoming_race,
        "previous": state.previous_race
    }

@app.get("/mock_status")
async def get_mock_status():
    """Return a realistic dynamic simulated live session, loops every 10 minutes"""
    t = int(time.time())

    # 10 minute cycle (600 seconds) per session type
    cycle_duration = 600
    session_cycle = (t // cycle_duration)
    step = t % cycle_duration

    # Simulate track status changes (more infrequent)
    status = "Clear"
    if 120 <= step < 160: status = "Yellow Flag"
    elif 300 <= step < 400: status = "Safety Car"
    elif 550 <= step: status = "Red Flag"

    # Define 2026 grid with realistic base performance offsets (seconds)
    # (TLA, Team, TeamColor, BasePerformanceOffset)
    drivers_data = [
        ("NOR", "McLaren", "FF8000", 0.0),
        ("PIA", "McLaren", "FF8000", 0.1),
        ("VER", "Red Bull", "3671C6", 0.05),
        ("HAD", "Red Bull", "3671C6", 0.5),
        ("LEC", "Ferrari", "E80020", 0.1),
        ("HAM", "Ferrari", "E80020", 0.15),
        ("RUS", "Mercedes", "27F4D2", 0.2),
        ("ANT", "Mercedes", "27F4D2", 0.3),
        ("ALO", "Aston Martin", "229971", 0.4),
        ("STR", "Aston Martin", "229971", 0.6),
        ("GAS", "Alpine F1 Team", "0093CC", 0.7),
        ("COL", "Alpine F1 Team", "0093CC", 0.8),
        ("SAI", "Williams", "64C4FF", 0.5),
        ("ALB", "Williams", "64C4FF", 0.6),
        ("LAW", "RB F1 Team", "6692FF", 0.7),
        ("LIN", "RB F1 Team", "6692FF", 0.9),
        ("BEA", "Haas F1 Team", "B6BABD", 0.8),
        ("OCO", "Haas F1 Team", "B6BABD", 0.75),
        ("BOR", "Audi", "52E252", 1.0),
        ("HUL", "Audi", "52E252", 0.9),
        ("BOT", "Cadillac F1 Team", "FFFFFF", 1.1),
        ("PER", "Cadillac F1 Team", "FFFFFF", 1.2)
    ]

    # Map drivers to numbers (using our DRIVER_MAPPING where possible)
    drivers = []
    for tla, team, col, perf in drivers_data:
        # Find dnum from DRIVER_MAPPING
        dnum = "99"
        for k, v in DRIVER_MAPPING.items():
            if v["abbrev"] == tla:
                dnum = k
                break
        drivers.append({"tla": tla, "team": team, "color": col, "perf": perf, "num": dnum})

    # Simulate different session types
    session_types = [
        ("FP1", "Practice"), ("FP2", "Practice"), ("FP3", "Practice"),
        ("Qualifying 1", "Qualifying"), ("Qualifying 2", "Qualifying"), ("Qualifying 3", "Qualifying"),
        ("Race", "Race")
    ]
    s_name, s_type = session_types[session_cycle % len(session_types)]

    import random
    # Use session_cycle as seed for consistent ranking within a cycle,
    # but add step-based jitter for position changes
    rng = random.Random(session_cycle)

    # Calculate simulated times
    is_race = (s_type == "Race")
    is_quali = (s_type == "Qualifying")
    base_lap = 80.0 # 1:20.000

    # Sort drivers by performance + some session-specific randomness
    drivers.sort(key=lambda x: x["perf"] + rng.random() * 0.2)

    mock_timing = []

    for pos_idx, d in enumerate(drivers):
        pos = pos_idx + 1
        # Dynamic jitter: occasionally swap positions
        if not is_race and (t // 10) % 5 == 0 and pos_idx < len(drivers)-1:
             if random.Random(t // 10).random() > 0.8:
                 pos = pos_idx + 2
             elif pos_idx > 0 and random.Random((t // 10) + 1).random() > 0.8:
                 pos = pos_idx

        # In Pit simulation:
        # Practice: 40% chance in pit. Quali: 30% chance. Race: 5% chance.
        pit_chance = 0.4 if not is_race else 0.05
        if is_quali: pit_chance = 0.3

        # Seed pit status with driver num + step to make it stay in pit for a while
        pit_seed = random.Random(int(d["num"]) + (step // 60))
        in_pit = (pit_seed.random() < pit_chance)

        # Out lap simulation: if not in pit, but was in pit in the previous minute-bucket
        # (Simplified: 15% of non-pit drivers are on an out-lap)
        is_out = not in_pit and (pit_seed.random() < 0.15)

        # Calculate times
        gap_val = (pos_idx * 0.15) + (d["perf"] * 0.5) + (rng.random() * 0.05)
        interval_val = 0.1 + (rng.random() * 0.2)

        best_time_sec = base_lap + d["perf"] + (rng.random() * 0.1)
        last_time_sec = best_time_sec + (rng.random() * 0.5)

        def fmt_time(s):
            m = int(s // 60)
            sec = s % 60
            return f"{m}:{sec:06.3f}"

        mock_timing.append({
            "num": d["num"],
            "name": d["tla"],
            "team": d["team"],
            "teamColor": d["color"],
            "pos": str(pos),
            "gap": "LEADER" if pos_idx == 0 else f"+{gap_val:.3f}",
            "int": "" if pos_idx == 0 else f"+{interval_val:.3f}",
            "last": fmt_time(last_time_sec) if not in_pit else "",
            "best": fmt_time(best_time_sec),
            "q1": fmt_time(best_time_sec) if "Qualifying" in s_name else "",
            "q2": fmt_time(best_time_sec) if "Qualifying 2" in s_name or "Qualifying 3" in s_name else "",
            "q3": fmt_time(best_time_sec) if "Qualifying 3" in s_name else "",
            "comp": random.Random(int(d["num"]) + session_cycle).choice(["soft", "medium", "hard"]),
            "pit": in_pit,
            "out": is_out,
            "fastest": (pos_idx == 1), # Mock P2 as having the fastest lap
            "col": d["color"]
        })

    # Sort final list by position
    mock_timing.sort(key=lambda x: int(x['pos']))

    # Determine part (Q1/Q2/Q3 or FP1/FP2/FP3)
    part = 1
    if "2" in s_name: part = 2
    elif "3" in s_name: part = 3

    return {
        "live": True,
        "session": {"name": s_name, "type": s_type, "circuit": "Suzuka", "part": part},
        "weather": {"air": "21.5", "track": "38.2", "hum": "45.2", "rain": False},
        "message": "TRACK CLEAR" if status == "Clear" else "DEBRIS ON TRACK",
        "track": status,
        "laps": {"current": (step // 15) if is_race else 0, "total": 53 if is_race else 0},
        "timing": mock_timing,
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
                            status = res.get('status', '')

                            points_display = res.get('points')
                            if status == "Retired":
                                points_display = "DNF"
                            elif status == "Did not start":
                                points_display = "DNS"

                            nationality = driver.get('nationality', '')
                            flag = FLAG_MAPPING.get(nationality, "🏁")
                            team_name = constructor.get('name', '')
                            team_color = TEAM_COLORS.get(team_name, "FFFFFF")

                            formatted_results.append({
                                "firstName": driver.get('givenName'),
                                "lastName": driver.get('familyName'),
                                "constructor": team_name,
                                "position": res.get('position'),
                                "points": points_display,
                                "flag": flag,
                                "color": int(team_color, 16)
                            })
                        res_data = {
                            "raceName": race.get('raceName'),
                            "results": formatted_results
                        }
                        logger.info(f"Returning previous results: {res_data['raceName']} ({len(res_data['results'])} drivers)")
                        return res_data
        logger.warning("No results found in Jolpica response")
        return {"error": "No results found"}
    except Exception as e:
        logger.error(f"Error fetching previous results: {e}")
        import traceback
        logger.error(traceback.format_exc())
        return {"error": str(e)}

@app.get("/standings")
async def get_standings():
    """Fetch driver standings for the 2026 season"""
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{JOLPICA_BASE}/2026/driverstandings.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    standings_lists = data.get('MRData', {}).get('StandingsTable', {}).get('StandingsLists', [])
                    if standings_lists:
                        standings = standings_lists[0].get('DriverStandings', [])
                        formatted_standings = []
                        for s in standings:
                            driver = s.get('Driver', {})
                            nationality = driver.get('nationality', '')
                            formatted_standings.append({
                                "pos": s.get('position'),
                                "name": f"{driver.get('givenName')} {driver.get('familyName')}",
                                "flag": FLAG_MAPPING.get(nationality, "🏁"),
                                "points": s.get('points')
                            })
                        return {"standings": formatted_standings}
        return {"error": "No standings found"}
    except Exception as e:
        logger.error(f"Error fetching standings: {e}")
        return {"error": str(e)}

@app.get("/constructor_standings")
async def get_constructor_standings():
    """Fetch constructor standings for the 2026 season"""
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{JOLPICA_BASE}/2026/constructorstandings.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    standings_lists = data.get('MRData', {}).get('StandingsTable', {}).get('StandingsLists', [])
                    if standings_lists:
                        standings = standings_lists[0].get('ConstructorStandings', [])
                        formatted_standings = []
                        for s in standings:
                            constructor = s.get('Constructor', {})
                            nationality = constructor.get('nationality', '')
                            name = constructor.get('name', '')
                            formatted_standings.append({
                                "pos": s.get('position'),
                                "name": name,
                                "flag": FLAG_MAPPING.get(nationality, "🏁"),
                                "points": s.get('points'),
                                "color": int(get_team_color(name), 16)
                            })
                        return {"standings": formatted_standings}
        return {"error": "No standings found"}
    except Exception as e:
        logger.error(f"Error fetching constructor standings: {e}")
        return {"error": str(e)}

@app.get("/calendar")
async def get_calendar():
    """Fetch the full 2026 race calendar with all session times"""
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{JOLPICA_BASE}/2026.json", timeout=10) as resp:
                if resp.status == 200:
                    data = await resp.json()
                    races = data.get('MRData', {}).get('RaceTable', {}).get('Races', [])
                    formatted_calendar = []

                    for race in races:
                        country = race.get('Circuit', {}).get('Location', {}).get('country', '')
                        sessions = format_sessions(race)
                        formatted_calendar.append({
                            "name": race.get('raceName'),
                            "circuit": race.get('Circuit', {}).get('circuitName'),
                            "date": race.get('date'),
                            "flag": FLAG_MAPPING.get(country, "🏁"),
                            "flagCode": ISO_MAPPING.get(country, "un"),
                            "sessions": sessions
                        })
                    return {"calendar": formatted_calendar}
        return {"error": "No calendar found"}
    except Exception as e:
        logger.error(f"Error fetching calendar: {e}")
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
                topics = ["TimingData", "WeatherData", "SessionInfo", "LapCount", "DriverList", "TrackStatus", "RaceControlMessages", "Heartbeat", "TimingAppData", "TimingStats"]
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
    state.load()
    asyncio.create_task(signalr_worker())
    asyncio.create_task(fetch_race_schedule())

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
