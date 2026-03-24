#include "ui.h"
#include <ArduinoJson.h>

static lv_obj_t * screen;
static lv_obj_t * table;
static lv_obj_t * info_label;
static lv_obj_t * track_label;
static lv_obj_t * weather_label;

// Idle Dashboard Objects
static lv_obj_t * idle_container;
static lv_obj_t * next_race_label;
static lv_obj_t * last_race_label;
static lv_obj_t * next_flag_img;
static lv_obj_t * last_flag_img;
static lv_obj_t * winner_flag_img;

void ui_init() {
    screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);

    // Header Area
    info_label = lv_label_create(screen);
    lv_label_set_text(info_label, "F1 LIVE TIMING");
    lv_obj_align(info_label, LV_ALIGN_TOP_LEFT, 10, 10);

    track_label = lv_label_create(screen);
    lv_label_set_text(track_label, "TRACK: -");
    lv_obj_align(track_label, LV_ALIGN_TOP_RIGHT, -10, 10);

    weather_label = lv_label_create(screen);
    lv_label_set_text(weather_label, "AIR: - / TRACK: -");
    lv_obj_align(weather_label, LV_ALIGN_TOP_LEFT, 10, 30);

    // Timing Table
    table = lv_table_create(screen);
    lv_obj_set_size(table, 300, 170);
    lv_obj_align(table, LV_ALIGN_BOTTOM_MID, 0, -10);

    // Configure Columns
    lv_table_set_col_cnt(table, 4);
    lv_table_set_col_width(table, 0, 30);  // P
    lv_table_set_col_width(table, 1, 60);  // Driver
    lv_table_set_col_width(table, 2, 110); // Gap/Int
    lv_table_set_col_width(table, 3, 100); // Last Lap

    // Header Row
    lv_table_set_cell_value(table, 0, 0, "P");
    lv_table_set_cell_value(table, 0, 1, "DRV");
    lv_table_set_cell_value(table, 0, 2, "GAP / INT");
    lv_table_set_cell_value(table, 0, 3, "LAST");

    // Idle Dashboard Container
    idle_container = lv_obj_create(screen);
    lv_obj_set_size(idle_container, 300, 170);
    lv_obj_align(idle_container, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_flag(idle_container, LV_OBJ_FLAG_HIDDEN); // Hidden by default

    next_flag_img = lv_img_create(idle_container);
    lv_obj_align(next_flag_img, LV_ALIGN_TOP_LEFT, 0, 5);

    next_race_label = lv_label_create(idle_container);
    lv_label_set_text(next_race_label, "NEXT RACE: -");
    lv_obj_align(next_race_label, LV_ALIGN_TOP_LEFT, 40, 0);
    lv_label_set_long_mode(next_race_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(next_race_label, 240);

    last_flag_img = lv_img_create(idle_container);
    lv_obj_align(last_flag_img, LV_ALIGN_TOP_LEFT, 0, 85);

    last_race_label = lv_label_create(idle_container);
    lv_label_set_text(last_race_label, "LAST RACE: -");
    lv_obj_align(last_race_label, LV_ALIGN_TOP_LEFT, 40, 80);
    lv_label_set_long_mode(last_race_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(last_race_label, 240);

    winner_flag_img = lv_img_create(idle_container);
    lv_obj_align(winner_flag_img, LV_ALIGN_TOP_LEFT, 0, 125);
}

void ui_update_status(const JsonObject& data) {
    if (data["live"]) {
        lv_obj_add_flag(idle_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(table, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(info_label, data["session"]["name"]);
        lv_label_set_text(track_label, data["track"]);

        const char* air_temp = data["weather"]["air"] | "-";
        const char* track_temp = data["weather"]["track"] | "-";
        char weather_buf[64];
        snprintf(weather_buf, sizeof(weather_buf), "AIR: %sC / TRACK: %sC", air_temp, track_temp);
        lv_label_set_text(weather_label, weather_buf);

        JsonArray timing = data["timing"];
        int row = 1;
        for (JsonObject entry : timing) {
            if (row >= 10) break;
            lv_table_set_cell_value(table, row, 0, entry["pos"] | "-");

            const char* compound = entry["comp"] | "";
            char driver_name[32];
            if (strlen(compound) > 0) {
                // We'll use a symbol or just text for now as adding icons to table cells is complex in LVGL 8.3
                // Alternatively, we can just use the first letter of the compound
                char c = toupper(compound[0]);
                snprintf(driver_name, sizeof(driver_name), "(%c) %s", c, entry["name"] | "-");
            } else {
                snprintf(driver_name, sizeof(driver_name), "%s", entry["name"] | "-");
            }
            lv_table_set_cell_value(table, row, 1, driver_name);

            char gap_int[32];
            snprintf(gap_int, sizeof(gap_int), "%s / %s", entry["gap"] | "-", entry["int"] | "-");
            lv_table_set_cell_value(table, row, 2, gap_int);
            lv_table_set_cell_value(table, row, 3, entry["last"] | "-");
            row++;
        }
    } else {
        lv_obj_add_flag(table, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(idle_container, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(info_label, "OFF SESSION");
        lv_label_set_text(track_label, "-");
        lv_label_set_text(weather_label, "CHECKING NEXT RACE...");

        // Update Next Race
        JsonObject upcoming = data["upcoming"];
        if (!upcoming.isNull()) {
            char next_buf[256];
            snprintf(next_buf, sizeof(next_buf), "#FF1801 NEXT RACE:#\n%s\n%s\n%s",
                     upcoming["name"] | "",
                     upcoming["circuit"] | "", upcoming["date"] | "");
            lv_label_set_text(next_race_label, next_buf);
            lv_label_set_recolor(next_race_label, true);

            const char* code = upcoming["flagCode"] | "un";
            char path[64];
            snprintf(path, sizeof(path), "S:/data/%s.png", code);
            lv_img_set_src(next_flag_img, path);
        }

        // Update Last Race
        JsonObject previous = data["previous"];
        if (!previous.isNull()) {
            char last_buf[256];
            snprintf(last_buf, sizeof(last_buf), "#FFAA00 LAST RACE:#\n%s\nWinner: %s\n%s",
                     previous["name"] | "",
                     previous["winner"] | "",
                     previous["team"] | "");
            lv_label_set_text(last_race_label, last_buf);
            lv_label_set_recolor(last_race_label, true);

            const char* raceCode = previous["flagCode"] | "un";
            char racePath[64];
            snprintf(racePath, sizeof(racePath), "S:/data/%s.png", raceCode);
            lv_img_set_src(last_flag_img, racePath);

            const char* winCode = previous["winnerFlagCode"] | "un";
            char winPath[64];
            snprintf(winPath, sizeof(winPath), "S:/data/%s.png", winCode);
            lv_img_set_src(winner_flag_img, winPath);
        }
    }
}

void ui_show_message(const char* msg) {
    lv_label_set_text(info_label, msg);
}
