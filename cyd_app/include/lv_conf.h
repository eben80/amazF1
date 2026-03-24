/**
 * @file lv_conf.h
 * Configuration file for LVGL
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888)*/
#define LV_COLOR_DEPTH 16

/*Swap the 2 bytes of RGB565 color. Useful if the display has an 8-bit interface (e.g. SPI)*/
#define LV_COLOR_16_SWAP 0

/*=========================
   MEMORY SETTINGS
 *=========================*/

/*1: use custom malloc/free, 0: use the library's `lv_mem_alloc()`/`lv_mem_free()`*/
#define LV_MEM_CUSTOM 0
#if LV_MEM_CUSTOM == 0
    /*Size of the memory used by `lv_mem_alloc` in bytes (>= 2kB)*/
    #define LV_MEM_SIZE (32U * 1024U)          /*[bytes]*/

    /*Compiler prefix for a static array to use as memory pool*/
    #define LV_MEM_ATTR
#else       /*LV_MEM_CUSTOM*/
    #define LV_MEM_CUSTOM_INCLUDE <stdlib.h>   /*Header for the dynamic memory function*/
    #define LV_MEM_CUSTOM_ALLOC   malloc
    #define LV_MEM_CUSTOM_FREE    free
    #define LV_MEM_CUSTOM_REALLOC realloc
#endif     /*LV_MEM_CUSTOM*/

/*====================
   HAL SETTINGS
 *====================*/

/*Default display refresh period. LVG will redraw at most this period [ms]*/
#define LV_DISP_DEF_REFR_PERIOD 30      /*[ms]*/

/*Input device read period in milliseconds*/
#define LV_INDEV_DEF_READ_PERIOD 30     /*[ms]*/

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*1: Enable GPU interface*/
#define LV_USE_GPU_ARM2D 0
#define LV_USE_GPU_STM32_DMA2D 0

/*=====================
 *  COMPILER SETTINGS
 *====================*/

/*Define a custom attribute to `lv_tick_inc` function*/
#define LV_TICK_CUSTOM 1
#if LV_TICK_CUSTOM
    #define LV_TICK_CUSTOM_INCLUDE "Arduino.h"         /*Header for the system time function*/
    #define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())    /*Expression evaluating to current system time in ms*/
#endif   /*LV_TICK_CUSTOM*/

/*1: Add a 2-byte extra space to every line to make the buffer alignment OK*/
#define LV_MEM_BUF_MAX_NUM 16

/*===================
 * WIDGET USAGE
 *===================*/

#define LV_USE_ARC          1
#define LV_USE_BAR          1
#define LV_USE_BTN          1
#define LV_USE_BTNMATRIX    1
#define LV_USE_CANVAS       1
#define LV_USE_CHECKBOX     1
#define LV_USE_DROPDOWN     1
#define LV_USE_IMG          1
#define LV_USE_LABEL        1
#define LV_USE_LINE         1
#define LV_USE_ROLLER       1
#define LV_USE_SLIDER       1
#define LV_USE_SWITCH       1
#define LV_USE_TEXTAREA     1
#define LV_USE_TABLE        1

/*==================
 * EXTRA COMPONENTS
 *==================*/

#define LV_USE_FLEX 1
#define LV_USE_GRID 1

/*==================
 * THEMES
 *==================*/

#define LV_USE_THEME_DEFAULT 1

/*==================
 * FONT USAGE
 *==================*/

#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/*=================
 *  DEBUG SETTINGS
 *=================*/

#define LV_USE_ASSERT_NULL          1
#define LV_USE_ASSERT_MALLOC        1
#define LV_USE_ASSERT_STYLE         0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ           0

#define LV_USE_FS_POSIX             0

#define LV_USE_PNG 1

#endif /*LV_CONF_H*/
