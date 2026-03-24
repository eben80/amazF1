#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "config.h"
#include "ui.h"

// Hardware Interface
TFT_eSPI tft = TFT_eSPI();

#if defined(CYD_XPT2046) || defined(CYD_V2_V3_XPT2046)
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
SPIClass touchSPI = SPIClass(VSPI);
XPT2046_Touchscreen ts(TOUCH_CS);
#elif defined(CYD2USB_GT911)
#include <TAMC_GT911.h>
TAMC_GT911 ts = TAMC_GT911(I2C_SDA, I2C_SCL, GT911_INT, GT911_RST, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

// LVGL Buffers
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_WIDTH * 10];

// LVGL Display Callback
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// LVGL Touchpad Callback
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
#if defined(CYD_XPT2046) || defined(CYD_V2_V3_XPT2046)
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        data->state = LV_INDEV_STATE_PR;
        // Simple calibration for XPT2046 (values vary by model)
        data->point.x = map(p.x, 200, 3700, 0, SCREEN_WIDTH);
        data->point.y = map(p.y, 240, 3800, 0, SCREEN_HEIGHT);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
#elif defined(CYD2USB_GT911)
    ts.read();
    if (ts.isTouched) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = ts.points[0].x;
        data->point.y = ts.points[0].y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
#endif
}

// Data Fetching
void fetch_data() {
    Serial.print("Fetching data from: ");
    Serial.println(BRIDGE_URL);

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(BRIDGE_URL);
        int httpCode = http.GET();

        Serial.print("HTTP Response code: ");
        Serial.println(httpCode);

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.print("Payload length: ");
            Serial.println(payload.length());

            DynamicJsonDocument doc(8192);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                Serial.println("JSON parsed successfully.");
                ui_update_status(doc.as<JsonObject>());
            } else {
                Serial.print("JSON deserialization failed: ");
                Serial.println(error.c_str());
                ui_show_message("JSON ERROR");
            }
        } else {
            Serial.print("Error on HTTP request: ");
            Serial.println(http.errorToString(httpCode).c_str());
            ui_show_message("HTTP ERROR");
        }
        http.end();
    } else {
        Serial.println("WiFi Disconnected.");
        ui_show_message("WIFI ERROR");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for serial to stabilize
    Serial.println("\n--- F1 Timing Display ---");

    // Initialize Filesystem
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
    } else {
        Serial.println("LittleFS Mounted.");
    }

    // Turn on Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    Serial.println("TFT Backlight enabled.");

    // WiFi Setup via WiFiManager
    Serial.println("Initializing WiFiManager...");
    WiFiManager wm;
    // wm.resetSettings(); // Clear stored credentials for testing

    if (!wm.autoConnect("F1-Timing-Display")) {
        Serial.println("CRITICAL: Failed to connect to WiFi. Restarting...");
        delay(3000);
        ESP.restart();
    }
    Serial.print("WiFi Connected. IP: ");
    Serial.println(WiFi.localIP());

    // LVGL Setup
    Serial.println("Initializing LVGL...");
    lv_init();
    tft.begin();
    tft.setRotation(1);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * 10);

    // Register Display Driver
    Serial.println("Configuring Display Driver...");
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Register Touch Driver
    Serial.print("Initializing Touch Driver (");
#ifdef CYD_XPT2046
    Serial.println("XPT2046 SPI - Original)...");
    touchSPI.begin(6, 12, 13, TOUCH_CS); // CLK=6, MISO=12, MOSI=13, CS=33
    ts.begin(touchSPI);
    ts.setRotation(1);
#elif defined(CYD_V2_V3_XPT2046)
    Serial.println("XPT2046 SPI - Hybrid V2/V3)...");
    touchSPI.begin(TOUCH_CLK, TOUCH_DOUT, TOUCH_DIN, TOUCH_CS); // CLK=25, MISO=39, MOSI=32, CS=33
    ts.begin(touchSPI);
    ts.setRotation(1);
#elif defined(CYD2USB_GT911)
    Serial.println("GT911 I2C)...");
    ts.begin();
    ts.setRotation(1);
#else
    Serial.println("UNKNOWN)...");
#endif

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // Initialize UI
    Serial.println("Building UI components...");
    ui_init();

    // Initial Fetch
    Serial.println("Triggering initial data fetch...");
    fetch_data();

    Serial.println("Setup complete. Entering main loop.");
}

unsigned long last_poll = 0;

void loop() {
    lv_timer_handler();

    if (millis() - last_poll > POLL_INTERVAL) {
        fetch_data();
        last_poll = millis();
    }

    delay(5);
}
