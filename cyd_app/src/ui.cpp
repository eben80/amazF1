#include "ui.h"
#include <ArduinoJson.h>

static lv_obj_t * screen;
static lv_obj_t * table;
static lv_obj_t * info_label;
static lv_obj_t * track_label;
static lv_obj_t * weather_label;

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
}

void ui_update_status(const JsonObject& data) {
    if (data["live"]) {
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
            if (row >= 10) break; // Limit to top 10 for simplicity on small screen
            lv_table_set_cell_value(table, row, 0, entry["pos"] | "-");
            lv_table_set_cell_value(table, row, 1, entry["name"] | "-");

            char gap_int[32];
            snprintf(gap_int, sizeof(gap_int), "%s / %s", entry["gap"] | "-", entry["int"] | "-");
            lv_table_set_cell_value(table, row, 2, gap_int);
            lv_table_set_cell_value(table, row, 3, entry["last"] | "-");
            row++;
        }
    } else {
        lv_label_set_text(info_label, "OFF SESSION");
        lv_label_set_text(track_label, "-");
        lv_label_set_text(weather_label, "CHECKING NEXT RACE...");
    }
}

void ui_show_message(const char* msg) {
    lv_label_set_text(info_label, msg);
}
