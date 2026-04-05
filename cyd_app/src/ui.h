#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <ArduinoJson.h>

enum View {
    VIEW_SETTINGS,
    VIEW_MAIN,
    VIEW_RESULTS,
    VIEW_NEXT_RACE,
    VIEW_STANDINGS,
    VIEW_CONSTRUCTORS,
    VIEW_CALENDAR,
    VIEW_EVENT_DETAIL
};

void ui_init();
void ui_set_view(View view);
View ui_get_view();
void ui_set_timezone(const char* tz);
void ui_set_sim_mode(bool enabled);
bool ui_get_sim_mode();
void ui_set_portrait_mode(bool enabled);
bool ui_get_portrait_mode();
void ui_set_brightness(uint8_t val);
uint8_t ui_get_brightness();
bool ui_update_status(const JsonObject& data);
void ui_update_next_race(const JsonObject& data);
void ui_update_results(const JsonObject& data);
void ui_update_standings(const JsonObject& data);
void ui_update_constructors(const JsonObject& data);
void ui_update_calendar(const JsonObject& data);
void ui_update_event_detail(const JsonObject& data);
void ui_show_message(const char* msg);

typedef void (*RotationCallback)(bool portrait);
void ui_set_rotation_cb(RotationCallback cb);

// Helper for local time formatting
void ui_format_local_time(const char* iso_time, char* out_buf, size_t out_size);

#endif