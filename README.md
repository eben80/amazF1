# F1 Live Timing for Amazfit Bip 6

This project consists of a Zepp OS mini-program and a Python middleware bridge to display live Formula 1 timing data on an Amazfit Bip 6 (390x450 resolution).

## Architecture

1.  **Python Middleware (`middleware/f1_bridge.py`):**
    *   Connects to the official F1 SignalR feed.
    *   Fetches previous and next race information via the [Jolpica API](https://api.jolpi.ca/ergast/f1/).
    *   Serves JSON status at `http://YOUR_EC2_IP:8000/status`.
2.  **Zepp OS App:**
    *   **Side Service (`app-side/index.js`):** Polls the middleware from the phone.
    *   **Device App (`pages/index.js`):** Displays a real-time timing tower, race status, and weather.

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
4.  **Configure Bridge URL:**
    Edit `app-side/index.js` and replace `YOUR_EC2_IP` with your EC2's public IP address.
5.  **Build & Preview:**
    *   To build the `.zab` package: `zeus build`
    *   To preview in the simulator (requires [Zepp Simulator](https://docs.zepp.com/docs/guides/tools/simulator/)): `zeus dev`

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
4.  **Run in Background:**
    Use `nohup` or `screen` to keep the bridge running:
    ```bash
    nohup python3 f1_bridge.py > bridge.log 2>&1 &
    ```
5.  **Security Group:**
    Ensure your EC2 Security Group allows **Inbound TCP traffic on port 8000** from any IP (or your phone's network).

---

## Graphics & Features
The app uses tire compound icons (`soft.png`, `medium.png`, `hard.png`) in `assets/` to visually indicate strategy. It automatically toggles between **Live Timing** during sessions and an **Idle Dashboard** (Previous winner + Next race) during off-periods.
