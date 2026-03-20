# F1 Live Timing for Amazfit Bip 6

This project consists of a Zepp OS mini-program and a Python middleware bridge to display live Formula 1 timing data on an Amazfit Bip 6.

## Architecture

1.  **Python Middleware (`middleware/f1_bridge.py`):**
    *   Connects to the official F1 SignalR feed.
    *   Aggregates timing data, weather, and session status.
    *   Fetches previous and next race information from the Jolpica API.
    *   Serves a compact JSON status at `http://YOUR_EC2_IP:8000/status`.

2.  **Zepp OS App:**
    *   **Side Service (`app-side/index.js`):** Polls the middleware from the user's phone.
    *   **Device App (`pages/index.js`):** Displays a real-time timing tower, race status, and weather on the Bip 6 (390x450 AMOLED).

## Setup Instructions

### 1. Middleware (EC2)
*   Install Python 3.9+.
*   `pip install -r middleware/requirements.txt`
*   Run: `python middleware/f1_bridge.py`
*   Ensure port 8000 is open in your EC2 security group.

### 2. Zepp OS App
*   Edit `app-side/index.js` and replace `YOUR_EC2_IP` with your server's public IP address.
*   Install dependencies: `npm install`
*   Build/Preview using the [Zeus CLI](https://docs.zepp.com/docs/guides/tools/cli/).

## Graphics
The app uses tire compound icons (`soft.png`, `medium.png`, `hard.png`) located in the `assets/` directory to visually indicate driver strategies.
