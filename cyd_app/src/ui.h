#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <ArduinoJson.h>

void ui_init();
void ui_update_status(const JsonObject& data);
void ui_show_message(const char* msg);

#endif
