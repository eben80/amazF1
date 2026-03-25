#ifndef CONFIG_H
#define CONFIG_H

// Middleware Settings
#define BASE_URL "http://ebski.co:8000"
#define STATUS_URL BASE_URL "/status"
#define MOCK_URL BASE_URL "/mock_status"
#define RESULTS_URL BASE_URL "/previous_results"
#define STANDINGS_URL BASE_URL "/standings"
#define CONSTRUCTORS_URL BASE_URL "/constructor_standings"
#define CALENDAR_URL BASE_URL "/calendar"

#define POLL_INTERVAL 10000 // 10 seconds

// Time Settings
#define NTP_SERVER "pool.ntp.org"
#define TZ_INFO "UTC0" // Default to UTC, can be changed (e.g., "EST5EDT,M3.2.0,M11.1.0")

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

// Hybrid CYD (V2/V3) SPI Touch Pins
#ifdef CYD_V2_V3_XPT2046
#ifndef TOUCH_CS
#define TOUCH_CS 33
#endif
#define TOUCH_CLK 25
#define TOUCH_DIN 32
#define TOUCH_DOUT 39
#define TOUCH_IRQ 36
#endif

#endif