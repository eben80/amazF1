# AmazF1 - Live Timing for Amazfit Bip 6 & ESP32 (CYD)

This project provides a complete ecosystem to display live Formula 1 timing data. It includes a **Zepp OS mini-program** for Amazfit smartwatches (390x450 resolution) and a standalone **ESP32 firmware** for the "Cheap Yellow Display" (CYD), all powered by a centralized Python middleware bridge.

## Architecture

1.  **Python Middleware (`middleware/f1_bridge.py`):**
    *   Connects to the official F1 SignalR feed for real-time telemetry.
    *   Fetches previous and next race information, standings, and calendars via the [Jolpica API](https://api.jolpi.ca/ergast/f1/).
    *   Serves unified JSON data via a secure HTTPS endpoint.
2.  **Zepp OS App (API 4.0):**
    *   **Side Service (`app-side/index.js`):** Secures communication between the watch and the middleware.
    *   **Device App (`page/index.js`):** A gesture-driven UI for timing, standings, and race schedules.
3.  **CYD ESP32 App (`cyd_app/`):**
    *   **LVGL UI:** A high-performance dashboard with persistent settings and localized time conversion.
    *   **Hardware Agnostic:** Supports multiple CYD variants (MicroUSB, USB-C, capacitive/resistive touch).

---

## 🚀 Setup: Windows Development (Zeus CLI)

To develop and test the watch app on a Windows device:

1.  **Install Node.js:**
    Download and install the LTS version from [nodejs.org](https://nodejs.org/).
2.  **Install Zeus CLI:**
    ```bash
    npm install -g @zeppos/zeus-cli
    ```
3.  **Clone & Install Dependencies:**
    ```bash
    cd <project_directory>
    npm install
    ```
    *Note: If you see build warnings about unresolved ZML imports, ensure `npm install` has completed successfully in the project root.*
4.  **Configure Bridge URL:**
    The app is pre-configured to use `https://ebski.co/status`. To change this, edit `app-side/index.js`.
5.  **Build & Preview:**
    *   To build the `.zab` package: `zeus build`
    *   To preview in the simulator: `zeus dev`

---

## 🔒 Setup: HTTPS Reverse Proxy (Existing Nginx)

Since you already have `ebski.co` set up with HTTPS, you only need to add the reverse proxy location block to your Nginx configuration to point to the `f1bridge` service running on port 8000.

### 1. Update Nginx Configuration
Add the following `location` block inside your existing `server` block for `ebski.co`:

```nginx
server {
    # ... your existing HTTPS configuration ...
    server_name ebski.co;

    location /status {
        proxy_pass http://127.0.0.1:8000/status;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

### 2. Restart Nginx
```bash
sudo nginx -t
sudo systemctl restart nginx
```

### 3. Middleware as a Service
Ensure your `f1bridge` service is running on your EC2 instance:
*   **Restart/Stop/Status:** `sudo systemctl [restart|stop|status] f1bridge`
*   **View Logs:** `sudo journalctl -u f1bridge -f`

---

## 🎨 Design Specifications (Image Sizes)

The app uses assets located in the `assets/` directory. Replace the placeholders with PNG images matching these dimensions:

*   **App Icon (`icon.png`):** 102x102 px (Square).
*   **F1 Logo (`assets/f1_logo.png`):** 120x40 px (Transparent).
*   **Tire Compound Icons (`assets/soft.png`, `assets/medium.png`, `assets/hard.png`):** 24x24 px (Circular, Transparent).

---

## Graphics & Features

The app automatically toggles between **Live Timing** during sessions and an **Idle Dashboard** during off-periods.

### 🏁 Live Timing Mode
*   **Adaptive Timing Tower:**
    *   **Race:** Displays Gap to Leader and Interval to Next.
    *   **Practice/Qualifying:** Displays Best Lap and Gap to Fastest.
*   **Real-time Indicators:**
    *   **Pit Status:** Drivers in the pit are marked with a `[P]` prefix.
    *   **Track Activity:** Drivers on an out-lap display `OUT LAP` in the timing column.
    *   **Position Tracking:** Real-time up/down arrows (`^`/`v`) show position changes during the session.
*   **Race Control:** Circularly scrolling display of the latest race control messages in the header.
*   **Team Colors:** Driver names and team titles rendered in their official 2026 HEX colors.
*   **Haptic/Visual Alerts:** Watch vibrates and CYD LED flashes (Red/Yellow/Orange) during track status changes (SC, VSC, Red Flag).
*   **Auto-Refresh:** Smart 5-second polling ensures the data is always fresh during live sessions.

### 🏎️ Idle Dashboard Mode
*   **Next Race:** Comprehensive summary of the upcoming GP, including circuit details and country flags.
*   **Last Race:** Snapshot of the previous podium winner and winning team.
*   **Weekend Schedule:** Full weekend breakdown (FP1, FP2, FP3, Quali, Sprint, Race) with **automatic local time conversion**.
*   **Interactive Calendar:** Drill down into any season event to see specific session timings.

### 📱 Navigation & UI
*   **Gesture Driven:**
    *   **Swipe Left/Right:** Seamlessly cycle through Dashboard, Results, Standings, and Calendar.
    *   **Wrap-around logic:** Navigate instantly from the first to the last screen in the cycle.
*   **User Preferences (CYD Only):** Built-in city-based timezone selection that persists across reboots.
*   **Dynamic UI:** Tables automatically resize to fit the available data, and unnecessary scrollbars are hidden for a clean, minimalist look.
*   **Status Handling:** Clear indication of **OFF SESSION** periods and real-time track status (Safety Car, Yellow Flags, etc.).

---

## 🛠️ Data Stack & Reliability
*   **SignalR:** High-frequency data stream from official F1 servers (Base64 + Zlib decoded).
*   **Jolpica/Ergast API:** Historical results, standings, and schedule data.
*   **FastAPI Middleware:** Python bridge that aggregates multiple streams into a single JSON endpoint.
*   **State Persistence:** The middleware automatically saves session state to `f1_state.json`. If the service restarts mid-session, it recovers the last known data instantly (expires after 12 hours).
*   **ZML Framework:** Robust communication bridge between the smartwatch and the mobile "Side Service".

## 📊 Logging & Debugging
*   **Middleware Logs:** The bridge uses `loguru` and standard `logging` to provide detailed debug info about SignalR topic updates.
*   **Watch Logs:** Uses the `@zos/utils` Logger. View logs via the Zepp app's developer mode or Zeus CLI.
