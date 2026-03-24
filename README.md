# AmazF1 - Live Timing for Amazfit Bip 6

This project consists of a Zepp OS mini-program and a Python middleware bridge to display live Formula 1 timing data on an Amazfit Bip 6 (390x450 resolution) using **Zepp OS 4.0 API**.

## Architecture

1.  **Python Middleware (`middleware/f1_bridge.py`):**
    *   Connects to the official F1 SignalR feed.
    *   Fetches previous and next race information via the [Jolpica API](https://api.jolpi.ca/ergast/f1/).
    *   Serves JSON status via an HTTPS reverse proxy (Nginx).
2.  **Zepp OS App (API 4.0):**
    *   **Side Service (`app-side/index.js`):** Polls the middleware from the phone securely via HTTPS.
    *   **Device App (`page/index.js`):** Displays a real-time timing tower, race status, and weather.

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
*   **Real-time Tower:** Displays the top 10 drivers with their current position (P1-P10).
*   **Team Colors:** Driver names are rendered in their official constructor colors.
*   **Gap to Leader:** Shows the interval or gap for each driver.
*   **Tire Compounds:** Displays visual icons for Hard, Medium, and Soft tires currently in use.
*   **Auto-Refresh:** The data polls every 30 seconds to ensure the tower is up-to-date.

### 🏎️ Idle Dashboard Mode
*   **Next Race:** Shows the upcoming Grand Prix name, circuit, country flag, and date.
*   **Last Race:** Displays the previous race winner with their nationality flag and team (in team colors).
*   **Session Times:** All upcoming session times (Practice, Quali, Sprint, Race) are automatically converted to the watch's **local time**.

### 📱 Navigation & UI
*   **Gesture Driven:**
    *   **Swipe Left:** Navigate through: Dashboard ➡️ Last Results ➡️ Next Race Details ➡️ Driver Standings ➡️ Constructor Standings ➡️ Full Calendar.
    *   **Swipe Right:** Navigate back through the screens.
*   **Interactive Calendar:** Click any race in the calendar view to see the full weekend schedule.
*   **Persistence:** The app uses `setStayWake` to remain active when the screen turns off and intercepts the back button to prevent accidental exits.
*   **Status Handling:** Correctly handles non-finishing drivers, showing **DNF** (Retired) or **DNS** (Did not start) instead of points where applicable.

---

## 🛠️ Data Stack
*   **SignalR:** Real-time data stream from official F1 servers.
*   **Jolpica/Ergast API:** Historical results, standings, and schedule data.
*   **FastAPI Middleware:** Python bridge that simplifies and merges data for the watch.
*   **ZML Framework:** Facilitates communication between the watch and the phone's side service.
