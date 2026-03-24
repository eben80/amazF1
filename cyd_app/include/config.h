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

// USB-C / CYD2USB I2C Touch Pins
#ifdef CYD2USB_GT911
#define I2C_SDA 33
#define I2C_SCL 32
#define GT911_INT -1
#define GT911_RST -1
#endif

// Original CYD MicroUSB SPI Touch Pins
#ifdef CYD_XPT2046
#define TOUCH_CS 33
#define TOUCH_MOSI 13
#define TOUCH_MISO 12
#define TOUCH_CLK 14
#endif

#endif
