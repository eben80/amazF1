#include "ui.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#include <time.h>

static lv_obj_t * screen;
static lv_obj_t * header;
static lv_obj_t * header_logo;
static lv_obj_t * info_label;
static lv_obj_t * track_label;
static lv_obj_t * weather_label;

static View active_view = VIEW_MAIN;

struct TZMapping {
    const char * name;
    const char * tz;
};

LV_IMG_DECLARE(f1_logo_small);

static const TZMapping tz_map[] = {
    {"UTC UTC", "UTC0"},
    {"London GMT/BST", "GMT0BST,M3.5.0/2,M10.5.0/3"},
    {"Berlin CET/CEST", "CET-1CEST,M3.5.0,M10.5.0/3"},
    {"Paris CET/CEST", "CET-1CEST,M3.5.0,M10.5.0/3"},
    {"Madrid CET/CEST", "CET-1CEST,M3.5.0,M10.5.0/3"},
    {"Rome CET/CEST", "CET-1CEST,M3.5.0,M10.5.0/3"},
    {"New York EST/EDT", "EST5EDT,M3.2.0,M11.1.0"},
    {"Chicago CST/CDT", "CST6CDT,M3.2.0,M11.1.0"},
    {"Denver MST/MDT", "MST7MDT,M3.2.0,M11.1.0"},
    {"Los Angeles PST/PDT", "PST8PDT,M3.2.0,M11.1.0"},
    {"Sao Paulo BRT", "<-03>3"},
    {"Tokyo JST", "JST-9"},
    {"Shanghai CST", "CST-8"},
    {"Singapore SGT", "SGT-8"},
    {"Sydney AEST/AEDT", "AEST-10AEDT,M10.1.0,M4.1.0/3"},
    {"Melbourne AEST/AEDT", "AEST-10AEDT,M10.1.0,M4.1.0/3"},
    {"Brisbane AEST", "AEST-10"},
    {"Perth AWST", "AWST-8"},
    {"Dubai GST", "GST-4"},
    {"Riyadh AST", "AST-3"},
    {"Istanbul TRT", "TRT-3"},
    {"Mexico City CST/CDT", "CST6CDT,M3.2.0,M11.1.0"}
};

// View Containers
static lv_obj_t * view_containers[8];
static DynamicJsonDocument * calendar_doc = nullptr;

// Main View Objects
static lv_obj_t * timing_table;
static lv_obj_t * idle_container;
static lv_obj_t * next_race_summary_label;
static lv_obj_t * last_race_summary_label;
static lv_obj_t * next_flag_img;
static lv_obj_t * last_flag_img;
static lv_obj_t * winner_flag_img;

// Other View Objects
static lv_obj_t * results_table;
static lv_obj_t * standings_table;
static lv_obj_t * constructors_table;
static lv_obj_t * calendar_table;
static lv_obj_t * next_race_details_label;
static lv_obj_t * event_detail_header_label;
static lv_obj_t * event_detail_table;

static void tz_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint16_t id = lv_dropdown_get_selected(obj);
        if (id < sizeof(tz_map)/sizeof(tz_map[0])) {
            ui_set_timezone(tz_map[id].tz);
        }
    }
}

static void back_to_calendar_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        ui_set_view(VIEW_CALENDAR);
    }
}

static void calendar_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint16_t row, col;
        lv_table_get_selected_cell(obj, &row, &col);
        if (row > 0 && calendar_doc) {
            JsonArray arr = calendar_doc->as<JsonArray>();
            if (row <= arr.size()) {
                ui_update_event_detail(arr[row - 1]);
            }
        }
    }
}

static void table_draw_cb(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(dsc->part == LV_PART_ITEMS) {
        uint32_t col_cnt = lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id % col_cnt;

        // Column 2 is PTS in results/standings/constructors
        if(col == 2) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
        }
    }
}

void ui_init() {
    screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), LV_PART_MAIN);

    // Header Area (Global)
    header = lv_obj_create(screen);
    lv_obj_set_size(header, 320, 50);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_set_scrollbar_mode(header, LV_SCROLLBAR_MODE_OFF);

    header_logo = lv_img_create(header);
    lv_img_set_src(header_logo, &f1_logo_small);
    lv_obj_align(header_logo, LV_ALIGN_TOP_LEFT, 0, 0);

    info_label = lv_label_create(header);
    lv_label_set_text(info_label, "F1 LIVE TIMING");
    lv_obj_set_style_text_font(info_label, &f1font_14, 0);
    lv_obj_set_style_text_color(info_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(info_label, LV_ALIGN_TOP_LEFT, 60, 0);

    track_label = lv_label_create(header);
    lv_label_set_text(track_label, "-");
    lv_obj_set_style_text_color(track_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(track_label, LV_ALIGN_TOP_RIGHT, 0, 0);

    weather_label = lv_label_create(header);
    lv_label_set_text(weather_label, "AIR: - / TRACK: -");
    lv_obj_set_style_text_color(weather_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(weather_label, LV_ALIGN_TOP_LEFT, 60, 20);

    // Initialize View Containers
    for (int i = 0; i < 8; i++) {
        view_containers[i] = lv_obj_create(screen);
        lv_obj_set_size(view_containers[i], 320, 190);
        lv_obj_align(view_containers[i], LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_obj_set_style_bg_color(view_containers[i], lv_color_hex(0x000000), 0);
        lv_obj_set_style_border_width(view_containers[i], 0, 0);
        lv_obj_set_style_pad_all(view_containers[i], 0, 0);
        lv_obj_add_flag(view_containers[i], LV_OBJ_FLAG_HIDDEN);
        // Ensure gestures bubble up to the screen
        lv_obj_clear_flag(view_containers[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_scroll_dir(view_containers[i], LV_DIR_VER);
        lv_obj_set_scrollbar_mode(view_containers[i], LV_SCROLLBAR_MODE_OFF);
    }

    // --- VIEW_SETTINGS setup ---
    lv_obj_t * settings_cont = view_containers[VIEW_SETTINGS];
    lv_obj_t * tz_label = lv_label_create(settings_cont);
    lv_label_set_text(tz_label, "Select Timezone:");
    lv_obj_set_style_text_color(tz_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(tz_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t * tz_dd = lv_dropdown_create(settings_cont);
    lv_obj_set_width(tz_dd, 280);
    lv_dropdown_clear_options(tz_dd);
    for (int i = 0; i < sizeof(tz_map)/sizeof(tz_map[0]); i++) {
        lv_dropdown_add_option(tz_dd, tz_map[i].name, i);
    }
    lv_obj_align(tz_dd, LV_ALIGN_TOP_MID, 0, 40);
    lv_obj_add_event_cb(tz_dd, tz_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t * info = lv_label_create(settings_cont);
    lv_label_set_text(info, "Changes take effect\nimmediately on next fetch.");
    lv_obj_set_style_text_color(info, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_align(info, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(info, LV_ALIGN_BOTTOM_MID, 0, -20);

    // --- VIEW_MAIN setup ---
    lv_obj_t * main_cont = view_containers[VIEW_MAIN];
    lv_obj_clear_flag(main_cont, LV_OBJ_FLAG_HIDDEN);

    timing_table = lv_table_create(main_cont);
    lv_obj_set_style_text_font(timing_table, &f1font_12, 0);
    lv_obj_set_style_text_color(timing_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(timing_table, 320, LV_SIZE_CONTENT);
    lv_obj_align(timing_table, LV_ALIGN_TOP_MID, 0, 0);
    lv_table_set_col_cnt(timing_table, 4);
    lv_table_set_col_width(timing_table, 0, 45);  // P
    lv_table_set_col_width(timing_table, 1, 65);  // Driver
    lv_table_set_col_width(timing_table, 2, 110); // Gap/Int
    lv_table_set_col_width(timing_table, 3, 100); // Last Lap
    lv_table_set_cell_value(timing_table, 0, 0, "P");
    lv_table_set_cell_value(timing_table, 0, 1, "DRV");
    lv_table_set_cell_value(timing_table, 0, 2, "GAP / INT");
    lv_table_set_cell_value(timing_table, 0, 3, "LAST");

    idle_container = lv_obj_create(main_cont);
    lv_obj_set_size(idle_container, 320, 190);
    lv_obj_align(idle_container, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_add_flag(idle_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_color(idle_container, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_width(idle_container, 0, 0);

    next_flag_img = lv_img_create(idle_container);
    lv_obj_align(next_flag_img, LV_ALIGN_TOP_LEFT, 5, 5);
    next_race_summary_label = lv_label_create(idle_container);
    lv_obj_align(next_race_summary_label, LV_ALIGN_TOP_LEFT, 45, 0);
    lv_obj_set_style_text_font(next_race_summary_label, &f1font_12, 0);
    lv_label_set_long_mode(next_race_summary_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(next_race_summary_label, 270);

    last_flag_img = lv_img_create(idle_container);
    lv_obj_align(last_flag_img, LV_ALIGN_TOP_LEFT, 5, 75);
    last_race_summary_label = lv_label_create(idle_container);
    lv_obj_align(last_race_summary_label, LV_ALIGN_TOP_LEFT, 45, 70);
    lv_obj_set_style_text_font(last_race_summary_label, &f1font_12, 0);
    lv_label_set_long_mode(last_race_summary_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(last_race_summary_label, 270);
    winner_flag_img = lv_img_create(idle_container);
    lv_obj_align(winner_flag_img, LV_ALIGN_TOP_LEFT, 5, 125);

    // --- VIEW_RESULTS setup ---
    results_table = lv_table_create(view_containers[VIEW_RESULTS]);
    lv_obj_set_style_text_font(results_table, &f1font_12, 0);
    lv_obj_set_style_text_color(results_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(results_table, 320, LV_SIZE_CONTENT);
    lv_table_set_col_cnt(results_table, 3);
    lv_table_set_col_width(results_table, 0, 45);
    lv_table_set_col_width(results_table, 1, 215);
    lv_table_set_col_width(results_table, 2, 60);
    lv_obj_add_event_cb(results_table, table_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_table_set_cell_value(results_table, 0, 0, "P");
    lv_table_set_cell_value(results_table, 0, 1, "DRIVER");
    lv_table_set_cell_value(results_table, 0, 2, "PTS");

    // --- VIEW_NEXT_RACE setup ---
    next_race_details_label = lv_label_create(view_containers[VIEW_NEXT_RACE]);
    lv_obj_align(next_race_details_label, LV_ALIGN_TOP_MID, 0, 10);
    lv_label_set_recolor(next_race_details_label, true);
    lv_label_set_long_mode(next_race_details_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(next_race_details_label, 300);

    // --- VIEW_STANDINGS setup ---
    standings_table = lv_table_create(view_containers[VIEW_STANDINGS]);
    lv_obj_set_style_text_font(standings_table, &f1font_12, 0);
    lv_obj_set_style_text_color(standings_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(standings_table, 320, LV_SIZE_CONTENT);
    lv_table_set_col_cnt(standings_table, 3);
    lv_table_set_col_width(standings_table, 0, 45);
    lv_table_set_col_width(standings_table, 1, 215);
    lv_table_set_col_width(standings_table, 2, 60);
    lv_obj_add_event_cb(standings_table, table_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_table_set_cell_value(standings_table, 0, 0, "P");
    lv_table_set_cell_value(standings_table, 0, 1, "DRIVER");
    lv_table_set_cell_value(standings_table, 0, 2, "PTS");

    // --- VIEW_CONSTRUCTORS setup ---
    constructors_table = lv_table_create(view_containers[VIEW_CONSTRUCTORS]);
    lv_obj_set_style_text_font(constructors_table, &f1font_12, 0);
    lv_obj_set_style_text_color(constructors_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(constructors_table, 320, LV_SIZE_CONTENT);
    lv_table_set_col_cnt(constructors_table, 3);
    lv_table_set_col_width(constructors_table, 0, 45);
    lv_table_set_col_width(constructors_table, 1, 215);
    lv_table_set_col_width(constructors_table, 2, 60);
    lv_obj_add_event_cb(constructors_table, table_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_table_set_cell_value(constructors_table, 0, 0, "P");
    lv_table_set_cell_value(constructors_table, 0, 1, "TEAM");
    lv_table_set_cell_value(constructors_table, 0, 2, "PTS");

    // --- VIEW_CALENDAR setup ---
    calendar_table = lv_table_create(view_containers[VIEW_CALENDAR]);
    lv_obj_set_style_text_font(calendar_table, &f1font_12, 0);
    lv_obj_set_style_text_color(calendar_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(calendar_table, 320, LV_SIZE_CONTENT);
    lv_table_set_col_cnt(calendar_table, 2);
    lv_table_set_col_width(calendar_table, 0, 210);
    lv_table_set_col_width(calendar_table, 1, 110);
    lv_obj_add_event_cb(calendar_table, calendar_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_table_set_cell_value(calendar_table, 0, 0, "RACE");
    lv_table_set_cell_value(calendar_table, 0, 1, "DATE");

    // --- VIEW_EVENT_DETAIL setup ---
    event_detail_header_label = lv_label_create(view_containers[VIEW_EVENT_DETAIL]);
    lv_obj_align(event_detail_header_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_text_color(event_detail_header_label, lv_color_hex(0xFFFFFF), 0);
    lv_label_set_recolor(event_detail_header_label, true);
    lv_label_set_long_mode(event_detail_header_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(event_detail_header_label, 300);
    lv_obj_add_flag(event_detail_header_label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(event_detail_header_label, back_to_calendar_event_handler, LV_EVENT_CLICKED, NULL);

    event_detail_table = lv_table_create(view_containers[VIEW_EVENT_DETAIL]);
    lv_obj_set_style_text_font(event_detail_table, &f1font_12, 0);
    lv_obj_set_style_text_color(event_detail_table, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_size(event_detail_table, 320, LV_SIZE_CONTENT);
    lv_obj_align(event_detail_table, LV_ALIGN_TOP_MID, 0, 40);
    lv_table_set_col_cnt(event_detail_table, 2);
    lv_table_set_col_width(event_detail_table, 0, 160);
    lv_table_set_col_width(event_detail_table, 1, 160);
    lv_obj_add_event_cb(event_detail_table, table_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(event_detail_table, back_to_calendar_event_handler, LV_EVENT_CLICKED, NULL);
}

void ui_set_timezone(const char* tz) {
    setenv("TZ", tz, 1);
    tzset();
    Preferences prefs;
    prefs.begin("f1-app", false);
    prefs.putString("tz", tz);
    prefs.end();
    Serial.print("Timezone updated and saved: ");
    Serial.println(tz);

    // Sync dropdown if it exists
    if (view_containers[VIEW_SETTINGS]) {
        lv_obj_t * dd = lv_obj_get_child(view_containers[VIEW_SETTINGS], 1);
        if (dd && lv_obj_check_type(dd, &lv_dropdown_class)) {
            for (int i = 0; i < sizeof(tz_map)/sizeof(tz_map[0]); i++) {
                if (strcmp(tz_map[i].tz, tz) == 0) {
                    lv_dropdown_set_selected(dd, i);
                    break;
                }
            }
        }
    }
}

View ui_get_view() {
    return active_view;
}

void ui_set_view(View view) {
    active_view = view;
    for (int i = 0; i < 8; i++) {
        lv_obj_add_flag(view_containers[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_clear_flag(view_containers[view], LV_OBJ_FLAG_HIDDEN);

    // Reset header for non-main views if needed
    if (view != VIEW_MAIN) {
        lv_label_set_text(track_label, "");
        lv_label_set_text(weather_label, "");
        switch(view) {
            case VIEW_SETTINGS: lv_label_set_text(info_label, "Settings"); break;
            case VIEW_RESULTS: lv_label_set_text(info_label, "LAST RESULTS"); break;
            case VIEW_NEXT_RACE: lv_label_set_text(info_label, "NEXT RACE"); break;
            case VIEW_STANDINGS: lv_label_set_text(info_label, "DRIVERS"); break;
            case VIEW_CONSTRUCTORS: lv_label_set_text(info_label, "CONSTRUCTORS"); break;
            case VIEW_CALENDAR: lv_label_set_text(info_label, "CALENDAR"); break;
            case VIEW_EVENT_DETAIL: lv_label_set_text(info_label, "EVENT DETAIL"); break;
            default: break;
        }
    }
}

void ui_update_status(const JsonObject& data) {
    if (data["live"]) {
        lv_obj_add_flag(idle_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(timing_table, LV_OBJ_FLAG_HIDDEN);

        if (active_view == VIEW_MAIN) {
            lv_label_set_text(info_label, (const char*)(data["session"]["name"] | "-"));
        }
        lv_label_set_text(track_label, (const char*)(data["track"] | "-"));

        const char* air_temp = data["weather"]["air"] | "-";
        const char* track_temp = data["weather"]["track"] | "-";
        char weather_buf[64];
        snprintf(weather_buf, sizeof(weather_buf), "AIR: %sC / TRACK: %sC", air_temp, track_temp);
        lv_label_set_text(weather_label, weather_buf);

        JsonArray timing = data["timing"];
        lv_table_set_row_cnt(timing_table, timing.size() + 1);

        int row = 1;
        for (JsonObject entry : timing) {
            lv_table_set_cell_value(timing_table, row, 0, entry["pos"] | "-");

            const char* compound = entry["comp"] | "";
            char driver_name[64];
            if (strlen(compound) > 0) {
                char c = toupper(compound[0]);
                snprintf(driver_name, sizeof(driver_name), "(%c) %s", c, (const char*)(entry["name"] | "-"));
            } else {
                snprintf(driver_name, sizeof(driver_name), "%s", (const char*)(entry["name"] | "-"));
            }
            lv_table_set_cell_value(timing_table, row, 1, driver_name);

            char gap_int[32];
            snprintf(gap_int, sizeof(gap_int), "%s / %s", entry["gap"] | "-", entry["int"] | "-");
            lv_table_set_cell_value(timing_table, row, 2, gap_int);
            lv_table_set_cell_value(timing_table, row, 3, entry["last"] | "-");
            row++;
        }
    } else {
        lv_obj_add_flag(timing_table, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(idle_container, LV_OBJ_FLAG_HIDDEN);

        if (active_view == VIEW_MAIN) {
            lv_label_set_text(info_label, "OFF SESSION");
        }
        lv_label_set_text(track_label, "-");
        lv_label_set_text(weather_label, "");

        // Update Next Race Summary
        JsonObject upcoming = data["upcoming"];
        if (!upcoming.isNull()) {
            char next_buf[256];
            char local_date[32];
            ui_format_local_time(upcoming["date"] | "", local_date, sizeof(local_date));

            snprintf(next_buf, sizeof(next_buf), "#FF1801 NEXT RACE:#\n%s\n%s\n%s",
                 (const char*)(upcoming["name"] | ""),
                 (const char*)(upcoming["circuit"] | ""), local_date);
            lv_label_set_text(next_race_summary_label, next_buf);
            lv_label_set_recolor(next_race_summary_label, true);

            const char* code = upcoming["flagCode"] | "un";
            if (strlen(code) == 0) code = "un";
            static char next_path[64];
            snprintf(next_path, sizeof(next_path), "S:/%s.png", code);
            lv_img_set_src(next_flag_img, next_path);
        }

        // Update Last Race Summary
        JsonObject previous = data["previous"];
        if (!previous.isNull()) {
            char last_buf[256];
            snprintf(last_buf, sizeof(last_buf), "#FFAA00 LAST RACE:#\n%s\nWinner: %s\n%s",
                 (const char*)(previous["name"] | ""),
                 (const char*)(previous["winner"] | ""),
                 (const char*)(previous["team"] | ""));
            lv_label_set_text(last_race_summary_label, last_buf);
            lv_label_set_recolor(last_race_summary_label, true);

            const char* raceCode = previous["flagCode"] | "un";
            if (strlen(raceCode) == 0) raceCode = "un";
            static char last_path[64];
            snprintf(last_path, sizeof(last_path), "S:/%s.png", raceCode);
            lv_img_set_src(last_flag_img, last_path);

            const char* winCode = previous["winnerFlagCode"] | "un";
            if (strlen(winCode) == 0) winCode = "un";
            static char win_path[64];
            snprintf(win_path, sizeof(win_path), "S:/%s.png", winCode);
            lv_img_set_src(winner_flag_img, win_path);
        }
    }
}

void ui_update_next_race(const JsonObject& data) {
    JsonObject upcoming = data["upcoming"];
    if (!upcoming.isNull()) {
        char buf[512];
        int pos = snprintf(buf, sizeof(buf), "#FF1801 %s#\n%s\n\n",
                           (const char*)(upcoming["name"] | ""),
                           (const char*)(upcoming["circuit"] | ""));

        JsonArray sessions = upcoming["sessions"];
        for (JsonObject s : sessions) {
            char local_time[32];
            ui_format_local_time(s["time"] | "", local_time, sizeof(local_time));
            pos += snprintf(buf + pos, sizeof(buf) - pos, "#FFAA00 %s:# %s\n",
                            s["name"] | "", local_time);
        }
        lv_label_set_text(next_race_details_label, buf);
    }
}

void ui_update_results(const JsonObject& data) {
    lv_label_set_text(info_label, data["raceName"] | "RESULTS");
    JsonArray results = data["results"];
    lv_table_set_row_cnt(results_table, results.size() + 1);

    int row = 1;
    for (JsonObject res : results) {
        lv_table_set_cell_value(results_table, row, 0, (const char*)(res["position"] | "-"));
        char name_buf[128];
        const char* fName = res["firstName"] | "";
        const char* lName = res["lastName"] | "";
        snprintf(name_buf, sizeof(name_buf), "%s %s", fName, lName);
        lv_table_set_cell_value(results_table, row, 1, name_buf);

        char pts_buf[32];
        JsonVariant pts = res["points"];
        if (pts.is<int>()) {
            snprintf(pts_buf, sizeof(pts_buf), "%d", pts.as<int>());
        } else {
            snprintf(pts_buf, sizeof(pts_buf), "%s", pts.as<const char*>());
        }
        lv_table_set_cell_value(results_table, row, 2, pts_buf);
        row++;
    }
}

void ui_update_standings(const JsonObject& data) {
    JsonArray standings = data["standings"];
    lv_table_set_row_cnt(standings_table, standings.size() + 1);

    int row = 1;
    for (JsonObject s : standings) {
        lv_table_set_cell_value(standings_table, row, 0, (const char*)(s["pos"] | "-"));
        lv_table_set_cell_value(standings_table, row, 1, (const char*)(s["name"] | "-"));
        char pts_buf[32];
        JsonVariant pts = s["points"];
        if (pts.is<int>()) {
            snprintf(pts_buf, sizeof(pts_buf), "%d", pts.as<int>());
        } else {
            snprintf(pts_buf, sizeof(pts_buf), "%s", pts.as<const char*>());
        }
        lv_table_set_cell_value(standings_table, row, 2, pts_buf);
        row++;
    }
}

void ui_update_constructors(const JsonObject& data) {
    JsonArray standings = data["standings"];
    lv_table_set_row_cnt(constructors_table, standings.size() + 1);

    int row = 1;
    for (JsonObject s : standings) {
        lv_table_set_cell_value(constructors_table, row, 0, (const char*)(s["pos"] | "-"));
        lv_table_set_cell_value(constructors_table, row, 1, (const char*)(s["name"] | "-"));
        char pts_buf[32];
        JsonVariant pts = s["points"];
        if (pts.is<int>()) {
            snprintf(pts_buf, sizeof(pts_buf), "%d", pts.as<int>());
        } else {
            snprintf(pts_buf, sizeof(pts_buf), "%s", pts.as<const char*>());
        }
        lv_table_set_cell_value(constructors_table, row, 2, pts_buf);
        row++;
    }
}

void ui_update_calendar(const JsonObject& data) {
    JsonArray calendar = data["calendar"];

    // Store data for detail view
    if (calendar_doc) delete calendar_doc;
    // Increased size to 24KB for full calendar with session data
    calendar_doc = new DynamicJsonDocument(24576);
    JsonArray arr = calendar_doc->to<JsonArray>();
    for (JsonObject race : calendar) {
        arr.add(race); // Deep copies everything into calendar_doc
    }

    lv_table_set_row_cnt(calendar_table, calendar.size() + 1);

    int row = 1;
    for (JsonObject race : calendar) {
        lv_table_set_cell_value(calendar_table, row, 0, (const char*)(race["name"] | "-"));
        char local_date[32];
        ui_format_local_time(race["date"] | "", local_date, sizeof(local_date));
        lv_table_set_cell_value(calendar_table, row, 1, local_date);
        row++;
    }
}

void ui_update_event_detail(const JsonObject& data) {
    char buf[512];
    snprintf(buf, sizeof(buf), "#FF1801 %s#\n%s",
                       (const char*)(data["name"] | "-"),
                       (const char*)(data["circuit"] | "-"));
    lv_label_set_text(event_detail_header_label, buf);

    JsonArray sessions = data["sessions"];
    lv_table_set_row_cnt(event_detail_table, sessions.size());

    int row = 0;
    for (JsonObject s : sessions) {
        lv_table_set_cell_value(event_detail_table, row, 0, (const char*)(s["name"] | "-"));
        char local_time[32];
        ui_format_local_time(s["time"] | "", local_time, sizeof(local_time));
        lv_table_set_cell_value(event_detail_table, row, 1, local_time);
        row++;
    }

    ui_set_view(VIEW_EVENT_DETAIL);
}

void ui_show_message(const char* msg) {
    lv_label_set_text(info_label, msg);
}

void ui_format_local_time(const char* iso_time, char* out_buf, size_t out_size) {
    if (!iso_time || strlen(iso_time) < 10) {
        snprintf(out_buf, out_size, "-");
        return;
    }

    if (strlen(iso_time) < 16) {
        // Just a date like YYYY-MM-DD
        int y, m, d;
        if (sscanf(iso_time, "%d-%d-%d", &y, &m, &d) == 3) {
            snprintf(out_buf, out_size, "%02d/%02d", d, m);
        } else {
            snprintf(out_buf, out_size, "%s", iso_time);
        }
        return;
    }

    struct tm tm_utc;
    // Format: 2024-03-09T15:00:00Z
    if (sscanf(iso_time, "%d-%d-%dT%d:%d:%d",
        &tm_utc.tm_year, &tm_utc.tm_mon, &tm_utc.tm_mday,
        &tm_utc.tm_hour, &tm_utc.tm_min, &tm_utc.tm_sec) != 6) {
        snprintf(out_buf, out_size, "%s", iso_time);
        return;
    }

    tm_utc.tm_year -= 1900;
    tm_utc.tm_mon -= 1;
    tm_utc.tm_isdst = 0;

    // mktime() converts local time to time_t (UTC).
    // Since our input tm is already UTC, we need to compensate.
    time_t t = mktime(&tm_utc);
    struct tm tm_check;
    gmtime_r(&t, &tm_check);
    time_t t_gmt = mktime(&tm_check);
    int32_t offset = (int32_t)(t - t_gmt);
    t += offset;

    struct tm * tm_local = localtime(&t);
    strftime(out_buf, out_size, "%d/%m %H:%M", tm_local);
}