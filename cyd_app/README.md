# F1 Live Timing for ESP32-2432S028 (Cheap Yellow Display)

This subfolder contains the firmware for the **ESP32-2432S028**, popularly known as the "Cheap Yellow Display" (CYD). It integrates with the project's F1 bridge middleware to display real-time timing data via a touch-enabled LVGL interface.

## 🏁 Hardware Variants

There are three main versions of this board supported by this project. Each requires a specific environment in PlatformIO due to differences in touch controllers and connectors.

### 1. Original CYD (MicroUSB)
- **Model:** ESP32-2432S028R
- **Connectors:** 1x MicroUSB (Power/Data).
- **Display:** 2.8" ILI9341 (320x240).
- **Touch:** **XPT2046** (Resistive, SPI-based).
- **PlatformIO Env:** `env:cyd`

### 2. CYD2USB (USB-C)
- **Model:** ESP32-2432S028-USB-C
- **Connectors:** 2x USB-C (one for Power/Data, one for Power only).
- **Display:** 2.8" ILI9341 (320x240).
- **Touch:** **GT911** (Capacitive, I2C-based).
- **PlatformIO Env:** `env:cyd2usb`

### 3. CYD-USB-C Hybrid (V2/V3)
- **Model:** ESP32-2432S028 V2/V3 Hybrid.
- **Connectors:** 1x MicroUSB and 1x USB-C.
- **Display:** 2.8" ILI9341 (320x240).
- **Touch:** **GT911** (Capacitive, I2C-based).
- **PlatformIO Env:** `env:cyd-v2-v3`

---

## 🛠️ GPIO Mapping & Components

The ESP32-2432S028 includes several onboard components. Below is the standard GPIO mapping for most models:

### 📺 TFT Display (ILI9341)
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| **MOSI** | 13 | Master Out Slave In |
| **SCLK** | 14 | Serial Clock |
| **CS** | 15 | Chip Select |
| **DC** | 2 | Data / Command |
| **RST** | -1 / EN | Reset (typically wired to hardware EN) |
| **BL** | 21 | Backlight (PWM) |

### 🖐️ Touch Controllers
| Signal | XPT2046 (SPI) | GT911 (I2C) |
| :--- | :--- | :--- |
| **CS / SDA** | 33 | 33 |
| **CLK / SCL** | 14 | 32 |
| **MOSI** | 13 | - |
| **MISO** | 12 | - |
| **INT / IRQ** | 36 | -1 |
| **RST** | - | -1 |

### 💡 Additional Components
| Component | GPIO | Description |
| :--- | :--- | :--- |
| **RGB LED (Red)** | 4 | PWM Control |
| **RGB LED (Green)** | 16 | PWM Control |
| **RGB LED (Blue)** | 17 | PWM Control |
| **LDR (Light Sensor)** | 34 | Analog Input (Light intensity) |
| **Audio (Speaker)** | 26 | Mono output (via transistor) |
| **SD Card CS** | 5 | SPI Chip Select |

---

## 🚀 Setup & Flashing

1.  **Install PlatformIO:**
    Download and install the PlatformIO extension for Visual Studio Code.
2.  **Open Project:**
    Open the `cyd_app` folder in VS Code.
3.  **Configure WiFi & Bridge:**
    Open `include/config.h` and update your WiFi credentials and bridge URL:
    ```cpp
    #define WIFI_SSID "YOUR_SSID"
    #define WIFI_PASSWORD "YOUR_PASSWORD"
    #define BRIDGE_URL "https://your-f1-bridge-domain.com/status"
    ```
4.  **TFT_eSPI Configuration:**
    The `platformio.ini` file is pre-configured with the correct build flags for all CYD hardware variants. You do **not** need to modify the library's `User_Setup.h` file manually.
5.  **Build & Flash:**
    Connect your board and select the appropriate environment in the PlatformIO project task menu based on the identification guide above. Click the **Build & Upload** button (Arrow icon) in the status bar.

## ❓ Troubleshooting

- **Touch Screen Not Working:** Ensure you have selected the correct environment for your hardware. MicroUSB-only models (XPT2046) use `cyd`, while USB-C or Hybrid models (GT911) typically require `cyd2usb` or `cyd-v2-v3`.
- **WiFi Connection Fails:** Check that your network is 2.4GHz. SSIDs and passwords are case sensitive in `config.h`.
- **No Data Displayed:** Confirm that the Python bridge middleware is running and that your CYD has internet access to reach the configured `BRIDGE_URL`.
