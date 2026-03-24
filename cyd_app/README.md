# F1 Live Timing for ESP32-2432S028 (Cheap Yellow Display)

This subfolder contains the firmware for the **ESP32-2432S028** (MicroUSB or USB-C variant), also known as the "Cheap Yellow Display" (CYD). It connects to the same F1 bridge middleware used by the Zepp OS watch app and displays real-time timing data.

## Features
- **Real-time Tower:** Displays the top 10 drivers, their position, name, gap/interval, and last lap time.
- **Track Status:** Updates the current track condition (Yellow Flag, Safety Car, etc.).
- **Weather Info:** Shows current air and track temperatures.
- **LVGL UI:** Professional-grade user interface for the 2.8" touch screen.

## Hardware Requirements
- **Display:** ESP32-2432S028 (2.8" LCD with touch).
- **Power:** MicroUSB or USB-C (depending on your model).
- **Connectivity:** 2.4GHz WiFi.

## Software Requirements
- **PlatformIO:** Recommended for building and flashing.
- **Libraries:**
    - `lvgl/lvgl@^8.3.7`
    - `bodmer/TFT_eSPI@^2.5.31`
    - `bblanchon/ArduinoJson@^6.21.2`
    - `tamctec/TAMC_GT911@^1.0.2` (For CYD2USB)
    - `XPT2046_Touchscreen` (For original CYD)

## Setup & Flashing

1.  **Install PlatformIO:**
    Download and install the PlatformIO extension for Visual Studio Code.
2.  **Open Project:**
    Open the `cyd_app` folder in VS Code.
3.  **Configure WiFi & Bridge:**
    Open `include/config.h` and update your WiFi credentials and bridge URL:
    ```cpp
    #define WIFI_SSID "YOUR_SSID"
    #define WIFI_PASSWORD "YOUR_PASSWORD"
    #define BRIDGE_URL "https://your-domain.com/status"
    ```
4.  **TFT_eSPI Configuration:**
    The `platformio.ini` file is pre-configured with the correct build flags for the CYD hardware. You do **not** need to modify the library's `User_Setup.h` file manually.
5.  **Build & Flash:**
    Connect your CYD to your computer and select the appropriate environment in the PlatformIO project task menu:
    - **`env:cyd`**: Original MicroUSB CYD with XPT2046 SPI Touch.
    - **`env:cyd2usb`**: New USB-C / CYD2USB with GT911 I2C Touch.
6.  Click the **Build & Upload** button in the PlatformIO toolbar.

## Troubleshooting

- **Touch Screen Not Working:** Ensure you selected the correct environment for your hardware. MicroUSB models typically use the `cyd` environment (XPT2046), while USB-C models usually need `cyd2usb` (GT911).
- **WiFi Connection Fails:** Check that your network is 2.4GHz and that the SSID/Password in `config.h` are correct.
- **No Data Displayed:** Ensure the Python bridge middleware is running and accessible from the CYD's network.
