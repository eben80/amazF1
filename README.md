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
The app automatically toggles between **Live Timing** during sessions and an **Idle Dashboard** (Previous winner + Next race) during off-periods. It uses tire compound graphics and team-specific colors to provide a professional-looking timing tower.
