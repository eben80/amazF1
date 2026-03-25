#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <LittleFS.h>
#include <Preferences.h>
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

    File * f = new File();
    const char * flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
    *f = LittleFS.open(full_path, flags);
    if (!*f || f->isDirectory()) {
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
static lv_color_t buf[SCREEN_WIDTH * 40];

// Global State
Preferences preferences;

// LVGL Display Callback
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, false);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// LVGL Touchpad Callback
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
#if defined(CYD_XPT2046) || defined(CYD_V2_V3_XPT2046)
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        data->state = LV_INDEV_STATE_PR;
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
    View view = ui_get_view();
    const char* url;
    switch(view) {
        case VIEW_RESULTS: url = RESULTS_URL; break;
        case VIEW_STANDINGS: url = STANDINGS_URL; break;
        case VIEW_CONSTRUCTORS: url = CONSTRUCTORS_URL; break;
        case VIEW_CALENDAR: url = CALENDAR_URL; break;
        case VIEW_NEXT_RACE:
        case VIEW_MAIN:
        default: url = ui_get_sim_mode() ? MOCK_URL : STATUS_URL; break;
    }

    Serial.print("Fetching data from: ");
    Serial.println(url);

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            DynamicJsonDocument doc(12288); // Increased for larger responses
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                switch(view) {
                    case VIEW_RESULTS: ui_update_results(doc.as<JsonObject>()); break;
                    case VIEW_STANDINGS: ui_update_standings(doc.as<JsonObject>()); break;
                    case VIEW_CONSTRUCTORS: ui_update_constructors(doc.as<JsonObject>()); break;
                    case VIEW_CALENDAR: ui_update_calendar(doc.as<JsonObject>()); break;
                    case VIEW_NEXT_RACE: ui_update_next_race(doc.as<JsonObject>()); break;
                    case VIEW_MAIN:
                    default: ui_update_status(doc.as<JsonObject>()); break;
                }
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

// Gesture Handling
static void event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_GESTURE) {
        View view = ui_get_view();
        if (view == VIEW_EVENT_DETAIL) {
            ui_set_view(VIEW_CALENDAR);
            return;
        }

        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_LEFT) {
            if (view == VIEW_SETTINGS) view = VIEW_MAIN;
            else if (view == VIEW_MAIN) view = VIEW_RESULTS;
            else if (view == VIEW_RESULTS) view = VIEW_NEXT_RACE;
            else if (view == VIEW_NEXT_RACE) view = VIEW_STANDINGS;
            else if (view == VIEW_STANDINGS) view = VIEW_CONSTRUCTORS;
            else if (view == VIEW_CONSTRUCTORS) view = VIEW_CALENDAR;
            else if (view == VIEW_CALENDAR) view = VIEW_SETTINGS; // Wrap around
            ui_set_view(view);
            fetch_data();
        } else if (dir == LV_DIR_RIGHT) {
            if (view == VIEW_CALENDAR) view = VIEW_CONSTRUCTORS;
            else if (view == VIEW_CONSTRUCTORS) view = VIEW_STANDINGS;
            else if (view == VIEW_STANDINGS) view = VIEW_NEXT_RACE;
            else if (view == VIEW_NEXT_RACE) view = VIEW_RESULTS;
            else if (view == VIEW_RESULTS) view = VIEW_MAIN;
            else if (view == VIEW_MAIN) view = VIEW_SETTINGS;
            else if (view == VIEW_SETTINGS) view = VIEW_CALENDAR; // Wrap around
            ui_set_view(view);
            fetch_data();
        }
    }
}

void setup() {
    Serial.begin(115200);
    LittleFS.begin(true);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Turn off onboard RGB LED (Common Anode, set HIGH to turn OFF)
    pinMode(4, OUTPUT); digitalWrite(4, HIGH);  // Red
    pinMode(16, OUTPUT); digitalWrite(16, HIGH); // Green
    pinMode(17, OUTPUT); digitalWrite(17, HIGH); // Blue

    WiFiManager wm;
    if (!wm.autoConnect("F1-Timing-Display")) ESP.restart();

    lv_init();
    tft.begin();
    tft.setRotation(1);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * 40);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

#ifdef CYD_XPT2046
    touchSPI.begin(6, 12, 13, TOUCH_CS);
    ts.begin(touchSPI);
    ts.setRotation(1);
#elif defined(CYD_V2_V3_XPT2046)
    touchSPI.begin(TOUCH_CLK, TOUCH_DOUT, TOUCH_DIN, TOUCH_CS);
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

    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);
    fs_drv.letter = 'S';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;
    lv_fs_drv_register(&fs_drv);

    lv_png_init();
    ui_init();

    // Load settings from preferences
    preferences.begin("f1-app", true);
    String saved_tz = preferences.getString("tz", TZ_INFO);
    bool saved_sim = preferences.getBool("sim", false);
    uint8_t saved_bright = preferences.getUChar("bright", 255);
    preferences.end();
    ui_set_timezone(saved_tz.c_str());
    ui_set_sim_mode(saved_sim);
    ui_set_brightness(saved_bright);

    // Time Sync
    configTzTime(saved_tz.c_str(), NTP_SERVER);
    Serial.println("Time configured with NTP.");

    // Setup Gesture Event
    lv_obj_add_event_cb(lv_scr_act(), event_cb, LV_EVENT_GESTURE, NULL);

    fetch_data();
}

unsigned long last_poll = 0;

void loop() {
    lv_timer_handler();
    if (ui_get_view() == VIEW_MAIN && (millis() - last_poll > POLL_INTERVAL)) {
        fetch_data();
        last_poll = millis();
    }
    delay(5);
}