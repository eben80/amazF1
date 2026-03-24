#ifndef CONFIG_H
#define CONFIG_H

// WiFi Settings
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// Middleware Settings
#define BRIDGE_URL "https://your-f1-bridge-domain.com/status"
#define POLL_INTERVAL 10000 // 10 seconds

// Display Settings
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Hardware Pins (ESP32-2432S028)
#define TFT_BL 21
#define I2C_SDA 33
#define I2C_SCL 32
#define GT911_INT -1
#define GT911_RST -1

#endif
