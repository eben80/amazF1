#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "config.h"
#include "ui.h"

// Hardware Interface
TFT_eSPI tft = TFT_eSPI();

#ifdef CYD_XPT2046
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
#ifdef CYD_XPT2046
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
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(BRIDGE_URL);
        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            DynamicJsonDocument doc(8192);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                ui_update_status(doc.as<JsonObject>());
            } else {
                ui_show_message("JSON ERROR");
            }
        } else {
            ui_show_message("HTTP ERROR");
        }
        http.end();
    } else {
        ui_show_message("WIFI ERROR");
    }
}

void setup() {
    Serial.begin(115200);

    // WiFi Setup
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");

    // LVGL Setup
    lv_init();
    tft.begin();
    tft.setRotation(1);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * 10);

    // Register Display Driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Register Touch Driver
#ifdef CYD_XPT2046
    touchSPI.begin(6, 12, 13, TOUCH_CS);
    ts.begin(touchSPI);
    ts.setRotation(1);
#elif defined(CYD2USB_GT911)
    ts.begin();
    ts.setRotation(1);
#endif

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // Initialize UI
    ui_init();

    // Initial Fetch
    fetch_data();
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
