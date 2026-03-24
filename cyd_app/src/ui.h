#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <ArduinoJson.h>

enum View {
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
void ui_update_status(const JsonObject& data);
void ui_update_next_race(const JsonObject& data);
void ui_update_results(const JsonObject& data);
void ui_update_standings(const JsonObject& data);
void ui_update_constructors(const JsonObject& data);
void ui_update_calendar(const JsonObject& data);
void ui_update_event_detail(const JsonObject& data);
void ui_show_message(const char* msg);

#endif
