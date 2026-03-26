/*******************************************************************************
 * Size: 10 px
 * Bpp: 2
 * Opts: --bpp 2 --size 10 --no-compress --stride 1 --align 1 --font Formula1-Regular_web_0.ttf --range 32-127,160-255 --format lvgl -o f1font_10.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef F1FONT_10
#define F1FONT_10 1
#endif

#if F1FONT_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x77, 0x33, 0x32, 0x70,

    /* U+0022 "\"" */
    0x76, 0x66, 0x15,

    /* U+0023 "#" */
    0x3, 0x18, 0x3f, 0xff, 0x6, 0x30, 0x9, 0x30,
    0x7f, 0xfc, 0xc, 0x90, 0x18, 0xc0,

    /* U+0024 "$" */
    0x1, 0x0, 0xc, 0x2, 0xff, 0x9c, 0xc0, 0x77,
    0x0, 0x2f, 0x80, 0x36, 0x80, 0xca, 0x7f, 0xf0,
    0xc, 0x0,

    /* U+0025 "%" */
    0x7f, 0xc, 0x24, 0xca, 0x3, 0xe3, 0x0, 0xc,
    0xf8, 0x9, 0x93, 0x3, 0x24, 0xc2, 0x43, 0xe0,

    /* U+0026 "&" */
    0x7, 0xfc, 0x2, 0x80, 0x0, 0x70, 0x0, 0xbf,
    0x1c, 0x60, 0x7c, 0x1c, 0xf, 0x3, 0xfd, 0x70,

    /* U+0027 "'" */
    0x76, 0x10,

    /* U+0028 "(" */
    0x2c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x2c,

    /* U+0029 ")" */
    0x74, 0x61, 0xc7, 0x1c, 0x71, 0x9d,

    /* U+002A "*" */
    0x11, 0x6, 0x87, 0xf4, 0x9c, 0x0, 0x0,

    /* U+002B "+" */
    0xc, 0x3, 0x7, 0xfc, 0x30, 0x4, 0x0,

    /* U+002C "," */
    0x23, 0x60,

    /* U+002D "-" */
    0x7c,

    /* U+002E "." */
    0x7,

    /* U+002F "/" */
    0xc, 0x1c, 0x18, 0x24, 0x30, 0x30, 0x60, 0x90,
    0x40,

    /* U+0030 "0" */
    0x1f, 0xf4, 0x34, 0x1c, 0x70, 0xd, 0x70, 0xd,
    0x70, 0xd, 0x34, 0x1c, 0x1f, 0xf4,

    /* U+0031 "1" */
    0x7e, 0x0, 0x70, 0x7, 0x0, 0x70, 0x7, 0x0,
    0x70, 0xbf, 0xf0,

    /* U+0032 "2" */
    0x7f, 0xf4, 0x0, 0xb0, 0x7, 0x41, 0xe0, 0x28,
    0x1, 0xc0, 0x7, 0xff, 0x80,

    /* U+0033 "3" */
    0xbf, 0xf4, 0x7, 0x40, 0xb0, 0x7, 0xf8, 0x0,
    0x34, 0x0, 0x97, 0xfe, 0x0,

    /* U+0034 "4" */
    0x0, 0xf0, 0x7, 0x64, 0x1c, 0x24, 0x70, 0x24,
    0xbf, 0xfe, 0x0, 0x24, 0x0, 0x24,

    /* U+0035 "5" */
    0x7f, 0xf9, 0xc0, 0x7, 0x0, 0x1f, 0xfc, 0x0,
    0x28, 0x0, 0xa7, 0xfe, 0x0,

    /* U+0036 "6" */
    0x1f, 0xfc, 0x34, 0x0, 0x70, 0x0, 0x7f, 0xf4,
    0x60, 0xc, 0x30, 0xc, 0x1f, 0xf4,

    /* U+0037 "7" */
    0xbf, 0xf4, 0x0, 0xd0, 0x7, 0x0, 0x30, 0x3,
    0x40, 0x1c, 0x0, 0xc0, 0x0,

    /* U+0038 "8" */
    0x2f, 0xf0, 0xc0, 0xa3, 0x2, 0x8b, 0xfc, 0x70,
    0x1d, 0xc0, 0x72, 0xff, 0x40,

    /* U+0039 "9" */
    0x2f, 0xe2, 0x80, 0xaa, 0x1, 0xcf, 0xff, 0x0,
    0x1c, 0x0, 0xa7, 0xfe, 0x0,

    /* U+003A ":" */
    0x70, 0x0, 0x7,

    /* U+003B ";" */
    0x70, 0x0, 0x33, 0x60,

    /* U+003C "<" */
    0x0, 0x6, 0x2c, 0x34, 0xe, 0x1,

    /* U+003D "=" */
    0x7f, 0x80, 0x7, 0xf8,

    /* U+003E ">" */
    0x0, 0x20, 0x2d, 0xb, 0x38, 0x10,

    /* U+003F "?" */
    0x7f, 0x80, 0xa, 0x0, 0xa1, 0xf8, 0x0, 0x0,
    0x0, 0x1c, 0x0,

    /* U+0040 "@" */
    0x3f, 0xf8, 0x0, 0x2, 0x81, 0xfe, 0x30, 0xc1,
    0xcc, 0x30, 0x73, 0xc, 0x1c, 0xc1, 0xff, 0xf0,

    /* U+0041 "A" */
    0x2, 0xd0, 0x0, 0xdc, 0x0, 0x93, 0x40, 0x30,
    0x70, 0x2f, 0xfd, 0xc, 0x1, 0xca, 0x0, 0x34,

    /* U+0042 "B" */
    0x3f, 0xf4, 0x30, 0x1c, 0x30, 0x1c, 0x3f, 0xf4,
    0x30, 0xc, 0x30, 0xc, 0x3f, 0xf8,

    /* U+0043 "C" */
    0x1f, 0xfc, 0x34, 0x0, 0x70, 0x0, 0x70, 0x0,
    0x70, 0x0, 0x34, 0x0, 0x1f, 0xfc,

    /* U+0044 "D" */
    0x3f, 0xf4, 0x30, 0xd, 0x30, 0x6, 0x30, 0x7,
    0x30, 0x6, 0x30, 0xd, 0x3f, 0xf4,

    /* U+0045 "E" */
    0x3f, 0xfc, 0xc0, 0x3, 0x0, 0xf, 0xff, 0x30,
    0x0, 0xc0, 0x3, 0xff, 0xc0,

    /* U+0046 "F" */
    0x3f, 0xfc, 0xc0, 0x3, 0x0, 0xf, 0xff, 0x30,
    0x0, 0xc0, 0x3, 0x0, 0x0,

    /* U+0047 "G" */
    0x1f, 0xfd, 0x34, 0x0, 0x70, 0x0, 0x70, 0xbe,
    0x70, 0x6, 0x34, 0xa, 0x1f, 0xfc,

    /* U+0048 "H" */
    0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x3f, 0xff,
    0x30, 0x7, 0x30, 0x3, 0x30, 0x3,

    /* U+0049 "I" */
    0xcc, 0xcc, 0xcc, 0xc0,

    /* U+004A "J" */
    0x0, 0xd0, 0xd, 0x0, 0xd0, 0xd, 0x0, 0xd0,
    0xc, 0x7f, 0x40,

    /* U+004B "K" */
    0x30, 0x1c, 0x30, 0x34, 0x30, 0xd0, 0x3f, 0x80,
    0x31, 0xd0, 0x30, 0x74, 0x30, 0x1d,

    /* U+004C "L" */
    0x30, 0x0, 0xc0, 0x3, 0x0, 0xc, 0x0, 0x30,
    0x0, 0xc0, 0x3, 0xff, 0x80,

    /* U+004D "M" */
    0xf, 0x1, 0xd0, 0x6d, 0xd, 0xc2, 0x68, 0x33,
    0xd, 0x72, 0x8d, 0x30, 0xcd, 0x25, 0xc3, 0x70,
    0xa6, 0x7, 0x81, 0xc0,

    /* U+004E "N" */
    0x2d, 0x1, 0xcd, 0xc0, 0x73, 0x2c, 0x1c, 0xc3,
    0x87, 0x30, 0x31, 0xcc, 0x7, 0x73, 0x0, 0xb4,

    /* U+004F "O" */
    0x1f, 0xf8, 0xd, 0x2, 0xc7, 0x0, 0x31, 0xc0,
    0xc, 0x70, 0x3, 0xd, 0x2, 0xc1, 0xff, 0x80,

    /* U+0050 "P" */
    0x3f, 0xf8, 0x30, 0xd, 0x30, 0xd, 0x3f, 0xf8,
    0x30, 0x0, 0x30, 0x0, 0x30, 0x0,

    /* U+0051 "Q" */
    0x1f, 0xf8, 0xd, 0x2, 0xc7, 0x0, 0x31, 0xc0,
    0xc, 0x70, 0x3, 0xd, 0x2, 0xc1, 0xff, 0x80,
    0x1, 0xc0,

    /* U+0052 "R" */
    0x3f, 0xf8, 0x30, 0xd, 0x30, 0xd, 0x33, 0xf8,
    0x31, 0xc0, 0x30, 0xb0, 0x30, 0x2c,

    /* U+0053 "S" */
    0x2f, 0xf9, 0xc0, 0x7, 0x40, 0x2, 0xf4, 0x0,
    0x28, 0x0, 0xa7, 0xff, 0x0,

    /* U+0054 "T" */
    0xff, 0xfd, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40,
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40,

    /* U+0055 "U" */
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0x7,
    0x30, 0x7, 0x34, 0xb, 0x1f, 0xfc,

    /* U+0056 "V" */
    0xb0, 0xa, 0x30, 0xc, 0x28, 0x1c, 0x1c, 0x34,
    0xd, 0x70, 0x7, 0xa0, 0x3, 0xc0,

    /* U+0057 "W" */
    0xa0, 0x2c, 0x7, 0x30, 0x3a, 0xa, 0x34, 0x67,
    0xc, 0x28, 0x93, 0x1c, 0x1c, 0xc3, 0x68, 0xe,
    0xc2, 0xb4, 0x7, 0x40, 0xf0,

    /* U+0058 "X" */
    0x70, 0xd, 0x28, 0x28, 0xd, 0x70, 0x7, 0xd0,
    0xe, 0x70, 0x28, 0x28, 0x70, 0xe,

    /* U+0059 "Y" */
    0xb0, 0xd, 0x38, 0x28, 0xd, 0x70, 0x7, 0xc0,
    0x2, 0x80, 0x2, 0x40, 0x2, 0x40,

    /* U+005A "Z" */
    0x7f, 0xf4, 0x0, 0xa0, 0xa, 0x1, 0xd0, 0x2c,
    0x1, 0xc0, 0x7, 0xff, 0x80,

    /* U+005B "[" */
    0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c,

    /* U+005C "\\" */
    0xd0, 0xa0, 0x70, 0x30, 0x34, 0x24, 0x18, 0xc,
    0x4,

    /* U+005D "]" */
    0x7c, 0x71, 0xc7, 0x1c, 0x71, 0xdf,

    /* U+005E "^" */
    0xd, 0xd, 0xc0,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x50, 0xc0,

    /* U+0061 "a" */
    0x7f, 0xd0, 0x7, 0xc0, 0xb3, 0xe, 0xc, 0x70,
    0x30, 0xff, 0xc0,

    /* U+0062 "b" */
    0x30, 0x0, 0xff, 0x83, 0x3, 0x4c, 0xa, 0x30,
    0x28, 0xc0, 0xd3, 0xfe, 0x0,

    /* U+0063 "c" */
    0x1f, 0xf3, 0x0, 0x70, 0x7, 0x0, 0x30, 0x1,
    0xff,

    /* U+0064 "d" */
    0x0, 0x24, 0x7f, 0xd3, 0x2, 0x5c, 0x9, 0x70,
    0x24, 0xc0, 0x91, 0xff, 0x40,

    /* U+0065 "e" */
    0x1f, 0xe0, 0xc0, 0x97, 0xff, 0x5c, 0x0, 0x30,
    0x0, 0x7f, 0xd0,

    /* U+0066 "f" */
    0x2f, 0x7f, 0xd3, 0x0, 0xc0, 0x30, 0xc, 0x3,
    0x0,

    /* U+0067 "g" */
    0x2f, 0xf5, 0xc0, 0xd6, 0x3, 0x5c, 0xd, 0x2f,
    0xf4, 0x0, 0xc3, 0xfe, 0x0,

    /* U+0068 "h" */
    0x30, 0x0, 0xff, 0x83, 0x3, 0xc, 0xd, 0x30,
    0x34, 0xc0, 0xd3, 0x3, 0x40,

    /* U+0069 "i" */
    0x33, 0x33, 0x33, 0x30,

    /* U+006A "j" */
    0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0x38,

    /* U+006B "k" */
    0x30, 0x0, 0xc0, 0xd3, 0xa, 0xc, 0xa0, 0x3f,
    0x0, 0xc7, 0x3, 0x3, 0x40,

    /* U+006C "l" */
    0x33, 0x33, 0x33, 0x30,

    /* U+006D "m" */
    0x3f, 0xff, 0xd3, 0x3, 0x7, 0x30, 0x30, 0x33,
    0x3, 0x3, 0x30, 0x30, 0x33, 0x3, 0x3,

    /* U+006E "n" */
    0x3f, 0xe0, 0xc0, 0xc3, 0x3, 0x4c, 0xd, 0x30,
    0x34, 0xc0, 0xd0,

    /* U+006F "o" */
    0x1f, 0xe0, 0xc0, 0xa7, 0x1, 0xdc, 0x7, 0x30,
    0x28, 0x7f, 0x80,

    /* U+0070 "p" */
    0x3f, 0xe0, 0xc0, 0xa3, 0x1, 0x8c, 0x6, 0x30,
    0x28, 0xff, 0x83, 0x0, 0x0,

    /* U+0071 "q" */
    0x1f, 0xf4, 0xc0, 0x97, 0x2, 0x5c, 0x9, 0x30,
    0x24, 0x7f, 0xd0, 0x2, 0x40,

    /* U+0072 "r" */
    0x2f, 0x8c, 0x3, 0x0, 0xc0, 0x30, 0xc, 0x0,

    /* U+0073 "s" */
    0x3f, 0xe6, 0x0, 0x39, 0x0, 0x6e, 0x0, 0x77,
    0xfd,

    /* U+0074 "t" */
    0x30, 0x3f, 0xd3, 0x0, 0xc0, 0x30, 0xd, 0x1,
    0xf4,

    /* U+0075 "u" */
    0x30, 0x34, 0xc0, 0xd3, 0x3, 0x4c, 0xd, 0x30,
    0x34, 0xbf, 0xd0,

    /* U+0076 "v" */
    0xa0, 0x1c, 0x30, 0x34, 0x28, 0x30, 0xc, 0x90,
    0xd, 0xc0, 0x3, 0x40,

    /* U+0077 "w" */
    0xa0, 0xf0, 0x67, 0x1e, 0x49, 0x32, 0x98, 0xc3,
    0x74, 0xcc, 0x2b, 0xe, 0x80, 0xe0, 0xb0,

    /* U+0078 "x" */
    0x70, 0x34, 0x73, 0x40, 0xb8, 0x3, 0x70, 0x38,
    0xa1, 0xc0, 0xd0,

    /* U+0079 "y" */
    0xa0, 0x34, 0xc0, 0xc2, 0x8a, 0x3, 0x30, 0xb,
    0x80, 0xc, 0x7, 0xd0, 0x0,

    /* U+007A "z" */
    0x7f, 0xe0, 0xa, 0x3, 0x81, 0xd0, 0x70, 0x7,
    0xff,

    /* U+007B "{" */
    0x1d, 0x24, 0x34, 0xb0, 0x30, 0x24, 0x24, 0x1d,

    /* U+007C "|" */
    0xcc, 0xcc, 0xcc, 0xcc, 0x40,

    /* U+007D "}" */
    0xf0, 0x34, 0x24, 0x1c, 0x28, 0x24, 0x34, 0xf0,

    /* U+007E "~" */
    0x76, 0x26, 0xc0,

    /* U+00A1 "¡" */
    0x72, 0x33, 0x37, 0x70,

    /* U+00A2 "¢" */
    0x1, 0x80, 0x7f, 0xd3, 0x18, 0x18, 0x60, 0x61,
    0x80, 0xc6, 0x1, 0xff, 0x40, 0x60,

    /* U+00A3 "£" */
    0x2, 0xfc, 0xd, 0x0, 0xc, 0x0, 0xbf, 0xfc,
    0x1c, 0x0, 0x1c, 0x0, 0xbf, 0xfc,

    /* U+00A4 "¤" */
    0x0, 0x0, 0xbe, 0x82, 0x8a, 0xc, 0xc, 0x38,
    0xa0, 0xbe, 0x80, 0x0, 0x0,

    /* U+00A5 "¥" */
    0x70, 0xd, 0x28, 0x24, 0x9, 0x60, 0x7f, 0xfc,
    0x2, 0x40, 0x7f, 0xfc, 0x2, 0x40,

    /* U+00A6 "¦" */
    0xcc, 0xc0, 0xc, 0xcc, 0x0,

    /* U+00A7 "§" */
    0x2f, 0xf5, 0xc0, 0x3, 0xe4, 0x28, 0x5d, 0x74,
    0x34, 0x1b, 0xc0, 0x3, 0x1f, 0xf8,

    /* U+00A8 "¨" */
    0xcc, 0x0,

    /* U+00A9 "©" */
    0xb, 0xfd, 0xd, 0x0, 0xd6, 0x2f, 0x59, 0x98,
    0x6, 0x66, 0x1, 0x98, 0xbd, 0x63, 0x40, 0x34,
    0x2f, 0xf4,

    /* U+00AA "ª" */
    0xbc, 0x2d, 0xa9, 0xbd,

    /* U+00AB "«" */
    0x0, 0x0, 0x18, 0x62, 0xdb, 0xd, 0x34, 0xe,
    0x38, 0x4, 0x10,

    /* U+00AE "®" */
    0x1a, 0x90, 0xaa, 0x55, 0x89, 0x96, 0xa2, 0x28,
    0x54, 0x6a, 0x40,

    /* U+00AF "¯" */
    0xb8,

    /* U+00B0 "°" */
    0x3d, 0x63, 0x3d,

    /* U+00B1 "±" */
    0x8, 0x3, 0x7, 0xfc, 0x30, 0x0, 0xf, 0xe0,

    /* U+00B2 "²" */
    0xb8, 0xba, 0x3e,

    /* U+00B3 "³" */
    0xbc, 0xd1, 0xae,

    /* U+00B4 "´" */
    0x14, 0xc0,

    /* U+00B6 "¶" */
    0x2f, 0xe9, 0x7f, 0xe9, 0xbf, 0xe9, 0x7f, 0xe9,
    0x6, 0xe9, 0x0, 0xa9, 0x0, 0xa9, 0x0, 0xa9,

    /* U+00B7 "·" */
    0xa, 0x0,

    /* U+00B8 "¸" */
    0x14, 0xc0,

    /* U+00B9 "¹" */
    0xa0, 0xc3, 0x2d,

    /* U+00BA "º" */
    0x7d, 0x82, 0x82, 0x7d,

    /* U+00BB "»" */
    0x0, 0x0, 0x82, 0x2, 0xdb, 0x42, 0xcb, 0x38,
    0xe0, 0x41, 0x0,

    /* U+00BC "¼" */
    0xd0, 0x30, 0x82, 0x8b, 0x4c, 0x0, 0x0, 0x28,
    0xf0, 0xc9, 0xc6, 0x2b, 0x40, 0x4,

    /* U+00BD "½" */
    0xd0, 0x30, 0x81, 0x82, 0xd, 0x2d, 0x30, 0x18,
    0xb0, 0xd0, 0xd3, 0xd, 0x14, 0x79,

    /* U+00BF "¿" */
    0x2, 0x80, 0x0, 0x1f, 0x87, 0x0, 0x60, 0x7,
    0x0, 0x1f, 0xf0,

    /* U+00C0 "À" */
    0x2, 0x40, 0x0, 0x20, 0x0, 0x0, 0x0, 0xb,
    0x40, 0x3, 0x70, 0x2, 0x4d, 0x0, 0xc1, 0xc0,
    0xbf, 0xf4, 0x30, 0x7, 0x28, 0x0, 0xd0,

    /* U+00C1 "Á" */
    0x0, 0x90, 0x0, 0x30, 0x0, 0x0, 0x0, 0xb,
    0x40, 0x3, 0x70, 0x2, 0x4d, 0x0, 0xc1, 0xc0,
    0xbf, 0xf4, 0x30, 0x7, 0x28, 0x0, 0xd0,

    /* U+00C2 "Â" */
    0x1, 0xc0, 0x0, 0xd8, 0x0, 0x0, 0x0, 0xb,
    0x40, 0x3, 0x70, 0x2, 0x4d, 0x0, 0xc1, 0xc0,
    0xbf, 0xf4, 0x30, 0x7, 0x28, 0x0, 0xd0,

    /* U+00C3 "Ã" */
    0x7, 0x60, 0x2, 0x6c, 0x0, 0x0, 0x0, 0xb,
    0x40, 0x3, 0x70, 0x2, 0x4d, 0x0, 0xc1, 0xc0,
    0xbf, 0xf4, 0x30, 0x7, 0x28, 0x0, 0xd0,

    /* U+00C4 "Ä" */
    0x3, 0x60, 0x0, 0x0, 0x0, 0x2d, 0x0, 0xd,
    0xc0, 0x9, 0x34, 0x3, 0x7, 0x2, 0xff, 0xd0,
    0xc0, 0x1c, 0xa0, 0x3, 0x40,

    /* U+00C5 "Å" */
    0x1, 0x80, 0x0, 0x60, 0x0, 0x0, 0x0, 0xb,
    0x40, 0x3, 0x70, 0x2, 0x4d, 0x0, 0xc1, 0xc0,
    0xbf, 0xf4, 0x30, 0x7, 0x28, 0x0, 0xd0,

    /* U+00C6 "Æ" */
    0x0, 0xbf, 0xff, 0x0, 0xa3, 0x80, 0x0, 0x70,
    0xe0, 0x0, 0x34, 0x3f, 0xfc, 0x1f, 0xfe, 0x0,
    0xc, 0x3, 0x80, 0xa, 0x0, 0xff, 0xf0,

    /* U+00C7 "Ç" */
    0x1f, 0xfc, 0x34, 0x0, 0x70, 0x0, 0x70, 0x0,
    0x70, 0x0, 0x34, 0x0, 0x1f, 0xfc, 0x0, 0xc0,
    0x1, 0x40,

    /* U+00C8 "È" */
    0x3, 0x0, 0x5, 0x0, 0x0, 0xf, 0xff, 0x30,
    0x0, 0xc0, 0x3, 0xff, 0xcc, 0x0, 0x30, 0x0,
    0xff, 0xf0,

    /* U+00C9 "É" */
    0x0, 0xc0, 0x2, 0x0, 0x0, 0xf, 0xff, 0x30,
    0x0, 0xc0, 0x3, 0xff, 0xcc, 0x0, 0x30, 0x0,
    0xff, 0xf0,

    /* U+00CA "Ê" */
    0x2, 0x80, 0x1a, 0x40, 0x0, 0xf, 0xff, 0x30,
    0x0, 0xc0, 0x3, 0xff, 0xcc, 0x0, 0x30, 0x0,
    0xff, 0xf0,

    /* U+00CB "Ë" */
    0x6, 0xa0, 0x0, 0x3, 0xff, 0xcc, 0x0, 0x30,
    0x0, 0xff, 0xf3, 0x0, 0xc, 0x0, 0x3f, 0xfc,

    /* U+00CC "Ì" */
    0x60, 0xc0, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc0,

    /* U+00CD "Í" */
    0x68, 0xc, 0xcc, 0xcc, 0xcc,

    /* U+00CE "Î" */
    0xd, 0xd, 0xc0, 0x0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0,

    /* U+00CF "Ï" */
    0xcc, 0x0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30,

    /* U+00D0 "Ð" */
    0x3f, 0xf4, 0x30, 0xd, 0x30, 0x6, 0xff, 0x47,
    0x30, 0x6, 0x30, 0xd, 0x3f, 0xf4,

    /* U+00D1 "Ñ" */
    0x2, 0x88, 0x0, 0xdd, 0x0, 0x0, 0x0, 0xb4,
    0x7, 0x37, 0x1, 0xcc, 0xb0, 0x73, 0xe, 0x1c,
    0xc0, 0xc7, 0x30, 0x1d, 0xcc, 0x2, 0xd0,

    /* U+00D2 "Ò" */
    0x2, 0x40, 0x0, 0x20, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x34, 0xb, 0x1c, 0x0, 0xc7, 0x0, 0x31,
    0xc0, 0xc, 0x34, 0xb, 0x7, 0xfe, 0x0,

    /* U+00D3 "Ó" */
    0x0, 0x90, 0x0, 0x30, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x34, 0xb, 0x1c, 0x0, 0xc7, 0x0, 0x31,
    0xc0, 0xc, 0x34, 0xb, 0x7, 0xfe, 0x0,

    /* U+00D4 "Ô" */
    0x1, 0xc0, 0x0, 0xd8, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x34, 0xb, 0x1c, 0x0, 0xc7, 0x0, 0x31,
    0xc0, 0xc, 0x34, 0xb, 0x7, 0xfe, 0x0,

    /* U+00D5 "Õ" */
    0x7, 0x60, 0x1, 0x6c, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x34, 0xb, 0x1c, 0x0, 0xc7, 0x0, 0x31,
    0xc0, 0xc, 0x34, 0xb, 0x7, 0xfe, 0x0,

    /* U+00D6 "Ö" */
    0x3, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x34, 0xb, 0x1c, 0x0, 0xc7, 0x0, 0x31,
    0xc0, 0xc, 0x34, 0xb, 0x7, 0xfe, 0x0,

    /* U+00D7 "×" */
    0x11, 0x4e, 0xc1, 0xe0, 0xdd, 0x0, 0x0,

    /* U+00D8 "Ø" */
    0x1f, 0xfb, 0xd, 0x3, 0x87, 0x2, 0x31, 0xc2,
    0xc, 0x72, 0x3, 0xf, 0x2, 0xc3, 0xff, 0x80,

    /* U+00D9 "Ù" */
    0x2, 0x40, 0x0, 0x80, 0x0, 0x0, 0x30, 0x7,
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0x7,
    0x34, 0xb, 0x1f, 0xfc,

    /* U+00DA "Ú" */
    0x0, 0xa0, 0x0, 0x80, 0x0, 0x0, 0x30, 0x7,
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0x7,
    0x34, 0xb, 0x1f, 0xfc,

    /* U+00DB "Û" */
    0x1, 0xc0, 0x3, 0x70, 0x0, 0x0, 0x30, 0x7,
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0x7,
    0x34, 0xb, 0x1f, 0xfc,

    /* U+00DC "Ü" */
    0x3, 0x30, 0x0, 0x0, 0x0, 0x0, 0x30, 0x7,
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0x7,
    0x34, 0xb, 0x1f, 0xfc,

    /* U+00DD "Ý" */
    0x0, 0xc0, 0x1, 0x80, 0x0, 0x0, 0xb0, 0xd,
    0x38, 0x28, 0xd, 0x70, 0x7, 0xc0, 0x2, 0x80,
    0x2, 0x40, 0x2, 0x40,

    /* U+00DE "Þ" */
    0x30, 0x0, 0x3f, 0xf8, 0x30, 0xd, 0x30, 0x9,
    0x30, 0xd, 0x3f, 0xf8, 0x30, 0x0,

    /* U+00DF "ß" */
    0x1f, 0xf4, 0x30, 0xc, 0x30, 0xc, 0x33, 0xf8,
    0x30, 0xc, 0x30, 0xd, 0x33, 0xf8,

    /* U+00E0 "à" */
    0x9, 0x0, 0xc, 0x0, 0x0, 0x1f, 0xf4, 0x1,
    0xf0, 0x2c, 0xc3, 0x83, 0x1c, 0xc, 0x3f, 0xf0,

    /* U+00E1 "á" */
    0x1, 0x40, 0xc, 0x0, 0x0, 0x1f, 0xf4, 0x1,
    0xf0, 0x2c, 0xc3, 0x83, 0x1c, 0xc, 0x3f, 0xf0,

    /* U+00E2 "â" */
    0x1, 0x0, 0x2d, 0x0, 0x44, 0x1f, 0xf4, 0x1,
    0xf0, 0x2c, 0xc3, 0x83, 0x1c, 0xc, 0x3f, 0xf0,

    /* U+00E3 "ã" */
    0xc, 0x50, 0x5a, 0x41, 0x58, 0x1f, 0xf4, 0x1,
    0xf0, 0x2c, 0xc3, 0x83, 0x1c, 0xc, 0x3f, 0xf0,

    /* U+00E4 "ä" */
    0xc, 0xc0, 0x0, 0x7, 0xfd, 0x0, 0x7c, 0xb,
    0x30, 0xe0, 0xc7, 0x3, 0xf, 0xfc,

    /* U+00E5 "å" */
    0x6, 0x0, 0x21, 0x0, 0x60, 0x1f, 0xf4, 0x1,
    0xf0, 0x2c, 0xc3, 0x83, 0x1c, 0xc, 0x3f, 0xf0,

    /* U+00E6 "æ" */
    0x3f, 0xef, 0xf0, 0x7, 0xd0, 0x60, 0xa3, 0xff,
    0x8e, 0xc, 0x0, 0x60, 0x34, 0x0, 0xff, 0x7f,
    0xe0,

    /* U+00E7 "ç" */
    0x1f, 0xf3, 0x0, 0x70, 0x7, 0x0, 0x30, 0x1,
    0xff, 0x3, 0x0, 0x20,

    /* U+00E8 "è" */
    0x6, 0x0, 0xc, 0x0, 0x0, 0x7, 0xf8, 0x30,
    0x25, 0xff, 0xd7, 0x0, 0xc, 0x0, 0x1f, 0xf4,

    /* U+00E9 "é" */
    0x0, 0x80, 0x9, 0x0, 0x0, 0x7, 0xf8, 0x30,
    0x25, 0xff, 0xd7, 0x0, 0xc, 0x0, 0x1f, 0xf4,

    /* U+00EA "ê" */
    0x1, 0x0, 0x1e, 0x0, 0x44, 0x7, 0xf8, 0x30,
    0x25, 0xff, 0xd7, 0x0, 0xc, 0x0, 0x1f, 0xf4,

    /* U+00EB "ë" */
    0x9, 0xc0, 0x0, 0x1, 0xfe, 0xc, 0x9, 0x7f,
    0xf5, 0xc0, 0x3, 0x0, 0x7, 0xfd,

    /* U+00EC "ì" */
    0x50, 0xc0, 0xc, 0x30, 0xc3, 0xc, 0x30,

    /* U+00ED "í" */
    0x18, 0xc0, 0xc, 0x30, 0xc3, 0xc, 0x30,

    /* U+00EE "î" */
    0x4, 0xb, 0x81, 0x10, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x0,

    /* U+00EF "ï" */
    0x33, 0x0, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc,

    /* U+00F0 "ð" */
    0x0, 0x0, 0x1e, 0x60, 0x2f, 0x0, 0xa, 0x3f,
    0xfa, 0x80, 0x6a, 0x2, 0x8f, 0xf8,

    /* U+00F1 "ñ" */
    0x9, 0x50, 0x69, 0x41, 0x48, 0xf, 0xf8, 0x30,
    0x30, 0xc0, 0xd3, 0x3, 0x4c, 0xd, 0x30, 0x34,

    /* U+00F2 "ò" */
    0x2, 0x0, 0xc, 0x0, 0x0, 0x7, 0xf8, 0x30,
    0x29, 0xc0, 0x77, 0x1, 0xcc, 0xa, 0x1f, 0xe0,

    /* U+00F3 "ó" */
    0x0, 0xc0, 0x9, 0x0, 0x0, 0x7, 0xf8, 0x30,
    0x29, 0xc0, 0x77, 0x1, 0xcc, 0xa, 0x1f, 0xe0,

    /* U+00F4 "ô" */
    0x1, 0x0, 0x1f, 0x0, 0x44, 0x7, 0xf8, 0x30,
    0x29, 0xc0, 0x77, 0x1, 0xcc, 0xa, 0x1f, 0xe0,

    /* U+00F5 "õ" */
    0x9, 0x20, 0x29, 0x80, 0x89, 0x7, 0xf8, 0x30,
    0x29, 0xc0, 0x77, 0x1, 0xcc, 0xa, 0x1f, 0xe0,

    /* U+00F6 "ö" */
    0x9, 0xc0, 0x0, 0x1, 0xfe, 0xc, 0xa, 0x70,
    0x1d, 0xc0, 0x73, 0x2, 0x87, 0xf8,

    /* U+00F7 "÷" */
    0x0, 0x3, 0x0, 0x1, 0xfe, 0x0, 0x3, 0x0,
    0x0,

    /* U+00F8 "ø" */
    0x1f, 0xf4, 0xc1, 0xe7, 0x19, 0xdc, 0x87, 0x38,
    0x28, 0xff, 0x80,

    /* U+00F9 "ù" */
    0x5, 0x0, 0xc, 0x0, 0x0, 0xc, 0xd, 0x30,
    0x34, 0xc0, 0xd3, 0x3, 0x4c, 0xd, 0x2f, 0xf4,

    /* U+00FA "ú" */
    0x1, 0x80, 0xc, 0x0, 0x0, 0xc, 0xd, 0x30,
    0x34, 0xc0, 0xd3, 0x3, 0x4c, 0xd, 0x2f, 0xf4,

    /* U+00FB "û" */
    0x1, 0x0, 0x2e, 0x0, 0x44, 0xc, 0xd, 0x30,
    0x34, 0xc0, 0xd3, 0x3, 0x4c, 0xd, 0x2f, 0xf4,

    /* U+00FC "ü" */
    0xc, 0xc0, 0x0, 0x3, 0x3, 0x4c, 0xd, 0x30,
    0x34, 0xc0, 0xd3, 0x3, 0x4b, 0xfd,

    /* U+00FD "ý" */
    0x2, 0x40, 0xc, 0x0, 0x0, 0x28, 0xd, 0x30,
    0x30, 0xa2, 0x80, 0xcc, 0x2, 0xe0, 0x3, 0x1,
    0xf4, 0x0,

    /* U+00FE "þ" */
    0x30, 0x0, 0xff, 0x83, 0x2, 0x8c, 0x6, 0x30,
    0x18, 0xc0, 0xa3, 0xfe, 0xc, 0x0,

    /* U+00FF "ÿ" */
    0xc, 0xc0, 0x0, 0xa, 0x3, 0x4c, 0xc, 0x28,
    0xa0, 0x33, 0x0, 0xb8, 0x0, 0xc0, 0x7d, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 42, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 72, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 7, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 39, .adv_w = 137, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 137, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 42, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 73, .adv_w = 59, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 81, .adv_w = 59, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 87, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 94, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 44, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 103, .adv_w = 54, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 104, .adv_w = 42, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 53, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 114, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 119, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 119, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 42, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 45, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 252, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 258, .adv_w = 81, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 262, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 268, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 143, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 138, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 121, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 130, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 121, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 142, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 50, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 101, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 107, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 183, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 155, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 139, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 136, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 533, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 119, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 141, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 130, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 197, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 59, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 672, .adv_w = 53, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 681, .adv_w = 59, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 687, .adv_w = 113, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 690, .adv_w = 62, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 691, .adv_w = 113, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 693, .adv_w = 109, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 103, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 74, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 772, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 46, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 46, .box_w = 4, .box_h = 8, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 797, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 810, .adv_w = 46, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 171, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 120, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 864, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 877, .adv_w = 76, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 903, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 116, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 162, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 108, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 965, .adv_w = 104, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 974, .adv_w = 58, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 982, .adv_w = 50, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 987, .adv_w = 58, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 995, .adv_w = 138, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 998, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1002, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1016, .adv_w = 121, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1030, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1043, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 50, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1062, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1076, .adv_w = 82, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1078, .adv_w = 149, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1096, .adv_w = 60, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1100, .adv_w = 122, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1111, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1122, .adv_w = 82, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1123, .adv_w = 69, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1126, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1134, .adv_w = 48, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1137, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1140, .adv_w = 113, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1142, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1158, .adv_w = 49, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1160, .adv_w = 102, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1162, .adv_w = 45, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1165, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1169, .adv_w = 122, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1180, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1194, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1208, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1219, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1288, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1311, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1332, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1355, .adv_w = 205, .box_w = 13, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1378, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1396, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1414, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1432, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1450, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1466, .adv_w = 50, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1474, .adv_w = 50, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1479, .adv_w = 50, .box_w = 5, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1492, .adv_w = 50, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1501, .adv_w = 130, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1515, .adv_w = 155, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1538, .adv_w = 139, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1561, .adv_w = 139, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 139, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1607, .adv_w = 139, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1630, .adv_w = 139, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1653, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1660, .adv_w = 139, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1676, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1696, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1716, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1736, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1756, .adv_w = 125, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1776, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1790, .adv_w = 127, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1804, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1820, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1836, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1852, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1868, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1882, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1898, .adv_w = 181, .box_w = 11, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1915, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1927, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1943, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1959, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1975, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1989, .adv_w = 46, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1996, .adv_w = 46, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2003, .adv_w = 46, .box_w = 5, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 2015, .adv_w = 46, .box_w = 4, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 2023, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2037, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2053, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2069, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2085, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2101, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2117, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2131, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2140, .adv_w = 120, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2151, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2167, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2183, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2199, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2213, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2231, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2245, .adv_w = 108, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_1[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 0, 0, 11, 12, 13,
    14, 15, 16, 17, 0, 18, 19, 20,
    21, 22, 23, 24, 25
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 161, .range_length = 29, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_1, .list_length = 29, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    },
    {
        .range_start = 191, .range_length = 65, .glyph_id_start = 122,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 0, 1, 3, 4, 3, 4,
    5, 6, 7, 8, 9, 10, 11, 12,
    13, 9, 6, 14, 14, 0, 3, 15,
    0, 16, 17, 9, 18, 6, 19, 20,
    21, 0, 0, 22, 23, 24, 25, 26,
    6, 27, 6, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 2, 37, 0, 0,
    4, 0, 38, 39, 40, 0, 0, 41,
    0, 38, 0, 0, 42, 0, 38, 38,
    39, 39, 0, 43, 44, 45, 0, 46,
    47, 48, 49, 50, 2, 0, 0, 0,
    0, 0, 0, 0, 51, 0, 0, 0,
    6, 1, 0, 52, 0, 1, 0, 1,
    1, 0, 0, 3, 0, 1, 1, 15,
    0, 0, 0, 17, 17, 17, 17, 17,
    17, 0, 18, 0, 0, 0, 0, 0,
    0, 0, 0, 6, 26, 6, 6, 6,
    6, 6, 3, 6, 31, 31, 31, 31,
    35, 53, 9, 38, 38, 38, 38, 38,
    38, 0, 40, 0, 0, 0, 0, 0,
    0, 0, 0, 54, 38, 39, 39, 39,
    39, 39, 3, 39, 0, 0, 0, 0,
    49, 39, 49
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 2,
    1, 0, 3, 1, 4, 5, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 7,
    13, 14, 15, 16, 16, 17, 4, 0,
    0, 0, 18, 0, 7, 0, 0, 0,
    7, 0, 0, 19, 0, 0, 20, 21,
    7, 0, 7, 0, 22, 23, 24, 25,
    26, 27, 28, 29, 0, 30, 3, 0,
    5, 0, 31, 0, 32, 32, 32, 33,
    34, 0, 0, 0, 0, 0, 35, 35,
    32, 35, 32, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 0, 0, 3, 0,
    0, 32, 45, 0, 46, 0, 46, 0,
    7, 1, 17, 47, 0, 1, 0, 1,
    1, 0, 0, 4, 0, 1, 1, 0,
    0, 0, 0, 18, 18, 18, 18, 18,
    18, 48, 7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 21, 7, 7, 7,
    7, 7, 4, 7, 24, 24, 24, 24,
    28, 0, 49, 31, 31, 31, 31, 31,
    31, 31, 32, 32, 32, 32, 32, 0,
    0, 0, 0, 50, 35, 32, 32, 32,
    32, 32, 4, 32, 39, 39, 39, 39,
    43, 0, 43
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -11, 0, 0, 0, 0, 0,
    0, -14, -24, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    -3, -3, -3, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -10, -3, -3, 0, 0,
    -10, 0, 0, 0, 0, -3, -3, 0,
    0, 0, -10, 0, -6, -5, -3, -13,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -3, -5, -3, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    -10, -3, -13, -5, -3, 0, 0, 0,
    0, 0, 0, 0, -14, 0, -21, -14,
    0, -24, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -16, -6, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, -3, 0,
    0, 0, -3, 0, 0, -3, 0, 0,
    0, -6, -6, -5, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -2, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    -3, 0, 0, 0, -2, 0, -5, -3,
    0, 0, -6, -2, 0, 0, -10, 0,
    0, 0, 0, -3, -6, 0, 0, 0,
    -3, 0, -3, -3, -3, -6, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -2, 0, -2, 0, 0,
    0, -5, 0, 0, -16, 0, 0, -5,
    0, 0, -5, 0, 0, 0, -8, 0,
    -11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -14, 0, -14, -11, 0, -16,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -2, 0, -5, 0, 0, 0,
    -8, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -5, -3, 0, 0,
    0, 0, 0, 0, -6, 0, 0, -3,
    0, -2, 0, 0, 0, 0, -3, 0,
    -6, -6, -3, -6, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -2, 0, 0, 0, 0, -5,
    0, 0, -6, 0, 0, 0, -3, 0,
    0, 0, 0, -3, 0, 0, -11, 0,
    -3, -3, 0, 0, -3, 0, 0, 0,
    -6, 0, -6, -6, 0, -6, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, -3, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -10, -27, -8, -3, 0,
    -3, 0, -14, 0, 0, -3, 0, 0,
    0, -19, -16, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -6, 0, -5, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -26,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, -11, 0, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -5, -3,
    -3, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, 0, 0, -3, 0, 0, -3, 0,
    0, 0, -5, 0, -10, -2, 0, 0,
    -3, 0, 0, 0, 0, 0, -18, -5,
    -18, -16, 0, -22, 0, -10, 0, -2,
    -2, -2, 0, 0, 0, -3, -2, -11,
    -8, 0, -3, 0, 0, -3, -8, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    -5, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -3, 0, 0, 0, 0,
    0, -6, -6, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -3, -3, -2, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, -19, -5, -3, 0, 0, 0,
    -3, 0, -6, 0, 0, 0, 0, -14,
    -40, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -2, 0, -2,
    0, -2, -2, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, -22, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -2, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -2, -3, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, -10, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -3, -5, 0, 0,
    0, 0, -6, -6, -6, 0, -5, -2,
    0, 0, 0, 0, 0, 0, -30, 0,
    0, -6, 0, 0, -5, 0, 0, 0,
    -6, 0, -16, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -26, -5, -22, -19,
    0, -29, 0, -5, 0, -3, -3, -3,
    0, 0, 0, -5, -3, -21, -14, 0,
    -8, 0, 0, 0, -13, 0, 0, -2,
    -5, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -10, 0,
    -10, -10, 0, -13, 0, -3, 0, -2,
    0, 0, 0, 0, 0, 0, -2, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -3, 0, 0, 0,
    -3, 0, -5, -3, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, -6,
    -19, -11, 0, 0, 0, 0, -6, 0,
    0, -3, 0, 0, 0, -16, -40, -8,
    0, -2, 0, 0, -3, -3, -6, -5,
    -6, 0, 0, -5, 0, -3, 0, -3,
    -2, 0, 0, 0, 0, -3, 0, 0,
    -2, 0, 0, -24, 0, 0, 0, 0,
    0, -3, 0, 0, -2, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, -3, -5,
    0, -5, 0, 0, 0, -2, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -2, 0, 0, 0, -6, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, -5,
    -3, -2, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, -14, -10,
    -3, 0, 0, 0, -19, 0, 0, -3,
    0, 0, -11, -18, -29, -10, -3, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -13, 0, -11, -11, -13, -10, 0,
    -11, -8, -2, -3, -3, -10, -3, 0,
    -2, -24, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, -6, -21, -8, -3, 0, 0, 0,
    -8, 0, 0, -5, 0, 0, 0, -18,
    -26, -10, -5, -2, 0, 0, 0, 0,
    0, 0, -3, 0, -5, -10, -2, -10,
    -8, -8, -8, 0, -3, 0, 0, -5,
    0, -6, 0, 0, -5, -22, -6, 0,
    0, 0, 0, -5, -14, -8, -3, 0,
    0, -3, -11, 0, 0, -3, 0, 0,
    -8, -16, -21, -10, -3, -3, 0, 0,
    0, 0, 0, 0, -2, 0, -5, -8,
    -2, -8, -5, -8, -6, 0, -3, 0,
    0, -3, 0, -5, 0, 0, -5, -18,
    -3, 0, 0, 0, 0, -3, 0, 0,
    -3, 0, 0, 0, -3, 0, 0, -3,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -6, 0, -2, 0, 0,
    0, -6, -3, 0, -2, 0, 0, 0,
    -5, 0, -3, 0, 0, 0, 0, -13,
    -24, -10, -6, 0, 0, 0, -16, 0,
    0, -5, 0, -3, 0, -21, -29, -13,
    -5, -3, 0, 0, 0, 0, 0, 0,
    0, 0, -5, -14, -3, -13, -8, -14,
    -11, 0, -6, -5, -3, -5, -3, -8,
    -6, 0, -5, -24, -6, 0, 0, 0,
    0, -3, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -2, 0,
    0, -2, 0, 0, 0, -3, 0, -3,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, -3, -3, 0, -8, -2, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    -11, -8, 0, -10, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, -8,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -13, 0, -11, -8, 0, -13, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -5, 0, -5, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -3, 0,
    -3, -2, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, -2, -3, 0,
    0, 0, -13, 0, -10, -6, -5, -13,
    -3, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -2, -3, -3, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, -10, -21, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    -3, 0, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -6, -5, 0, -5, 0, 0,
    0, -6, 0, -5, 0, 0, -5, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, -11, -21, 0,
    0, 0, -6, 0, 0, 0, 0, -3,
    0, 0, 0, -3, 3, -2, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -5, -6,
    0, -6, -2, 0, 0, 0, 0, -2,
    0, 0, -2, 0, 0, -2, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, -16, -3,
    -2, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, -8, -16, 0, 0, 0,
    -8, 0, 0, 0, -6, 0, -6, 0,
    0, -2, 0, -2, 0, -5, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 0, 0, 0, 0, -3,
    -6, -3, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, -8, -14, 0,
    0, 0, -2, 0, 0, 0, -3, 0,
    -3, 0, 0, -2, 0, -2, 0, -2,
    -3, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, -13, 0, 0, 0, 0,
    0, -5, 0, 0, -2, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -5, -3,
    0, -5, 0, 0, 0, -3, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -10, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, -8, 0, 0, 0, -3, 0,
    0, 0, -2, 0, -3, 0, 0, -3,
    0, -2, 0, -3, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, 0, -11, -5, 0, -8, 0, -5,
    0, -5, 0, -3, 0, 0, -2, 0,
    0, -3, -3, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    -13, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -11, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 54,
    .right_class_cnt     = 50,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 2,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t f1font_10 = {
#else
lv_font_t f1font_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    // .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if F1FONT_10*/
