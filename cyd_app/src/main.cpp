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

// LVGL Filesystem bridge for LittleFS
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {
    char full_path[128];
    if (path[0] != '/') {
        snprintf(full_path, sizeof(full_path), "/%s", path);
    } else {
        strncpy(full_path, path, sizeof(full_path));
    }

    Serial.print("LVFS: Opening ");
    Serial.println(full_path);

    File * f = new File();
    const char * flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
    *f = LittleFS.open(full_path, flags);
    if (!*f || f->isDirectory()) {
        Serial.println("LVFS: Open failed.");
        delete f;
        return NULL;
    }
    return (void *)f;
}

static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p) {
    File * f = (File *)file_p;
    f->close();
    delete f;
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br) {
    File * f = (File *)file_p;
    *br = f->read((uint8_t *)buf, btr);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence) {
    File * f = (File *)file_p;
    SeekMode mode = SeekSet;
    if (whence == LV_FS_SEEK_CUR) mode = SeekCur;
    else if (whence == LV_FS_SEEK_END) mode = SeekEnd;
    f->seek(pos, mode);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p) {
    File * f = (File *)file_p;
    *pos_p = f->position();
    return LV_FS_RES_OK;
}

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

void list_files() {
    Serial.println("LittleFS Files:");
    File root = LittleFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.print("  FILE: ");
        Serial.print(file.name());
        Serial.print("  SIZE: ");
        Serial.println(file.size());
        file = root.openNextFile();
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
        list_files();
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

    // Register LittleFS Driver for LVGL
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);
    fs_drv.letter = 'S';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;
    lv_fs_drv_register(&fs_drv);

    // Initialize PNG decoder
    lv_png_init();

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
