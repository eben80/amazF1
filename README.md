# AmazF1 - Live Timing for Amazfit Bip 6

This project consists of a Zepp OS mini-program and a Python middleware bridge to display live Formula 1 timing data on an Amazfit Bip 6 (390x450 resolution) using **Zepp OS 4.0 API**.

## Architecture

1.  **Python Middleware (`middleware/f1_bridge.py`):**
    *   Connects to the official F1 SignalR feed.
    *   Fetches previous and next race information via the [Jolpica API](https://api.jolpi.ca/ergast/f1/).
    *   Serves JSON status at `http://ebski.co:8000/status`.
2.  **Zepp OS App (API 4.0):**
    *   **Side Service (`app-side/index.js`):** Polls the middleware from the phone.
    *   **Device App (`page/index.js`):** Displays a real-time timing tower, race status, and weather.

---

## 🚀 Setup: Windows Development (Zeus CLI)

To develop and test the watch app on a Windows device:

1.  **Install Node.js:**
    Download and install the LTS version from [nodejs.org](https://nodejs.org/).
2.  **Install Zeus CLI:**
    Open PowerShell or Command Prompt and run:
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
    The app is pre-configured to use `http://ebski.co:8000/status`. To change this, edit `app-side/index.js`.
5.  **Build & Preview:**
    *   To build the `.zab` package: `zeus build`
    *   To preview in the simulator: `zeus dev`

---

## 🎨 Design Specifications (Image Sizes)

The app uses assets located in the `assets/` directory. Replace the placeholders with PNG images matching these dimensions:

*   **App Icon (`assets/icon.png`):** 102x102 px (Square).
*   **F1 Logo (`assets/f1_logo.png`):** 120x40 px (Transparent).
*   **Tire Compound Icons (`assets/soft.png`, `assets/medium.png`, `assets/hard.png`):** 24x24 px (Circular, Transparent).

---

## 🛠️ Setup: Ubuntu EC2 Middleware (Python venv)

To host the data bridge on an Ubuntu EC2 instance:

1.  **Update System:**
    ```bash
    sudo apt update && sudo apt install -y python3-venv python3-pip
    ```
2.  **Clone & Set Up Virtual Environment:**
    ```bash
    cd <project_directory>/middleware
    python3 -m venv venv
    source venv/bin/activate
    ```
3.  **Install Requirements:**
    ```bash
    pip install -r requirements.txt
    ```

### Managing the Middleware as a Service (systemd)

The bridge is configured as a systemd service named `f1bridge`:

*   **Restart/Stop/Status:** `sudo systemctl [restart|stop|status] f1bridge`
*   **View Logs:** `sudo journalctl -u f1bridge -f`

---

## Graphics & Features
The app automatically toggles between **Live Timing** during sessions and an **Idle Dashboard** (Previous winner + Next race) during off-periods. It uses tire compound graphics and team-specific colors to provide a professional-looking timing tower.
