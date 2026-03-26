/*******************************************************************************
 * Size: 8 px
 * Bpp: 2
 * Opts: --bpp 2 --size 8 --no-compress --stride 1 --align 1 --font Formula1-Regular_web_0.ttf --range 32-127,160-255 --format lvgl -o f1font_8.c
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



#ifndef F1FONT_8
#define F1FONT_8 1
#endif

#if F1FONT_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x66, 0x65, 0x16,

    /* U+0022 "\"" */
    0x5c, 0x5c, 0x0,

    /* U+0023 "#" */
    0x5, 0x50, 0xff, 0xc0, 0xcc, 0x1f, 0xf8, 0x26,
    0x40, 0xcc, 0x0,

    /* U+0024 "$" */
    0x5, 0x3, 0xfc, 0x95, 0x3, 0xe0, 0xb, 0xc0,
    0x59, 0x7f, 0xc0, 0x50,

    /* U+0025 "%" */
    0x7c, 0x32, 0x16, 0x6, 0x88, 0x2, 0x68, 0x1a,
    0x58, 0xc7, 0xd0,

    /* U+0026 "&" */
    0xf, 0xe0, 0x30, 0x2, 0xe2, 0x64, 0x7c, 0x90,
    0xe0, 0xfd, 0xd0,

    /* U+0027 "'" */
    0x55, 0x0,

    /* U+0028 "(" */
    0x35, 0x86, 0x18, 0x61, 0x83, 0x40,

    /* U+0029 ")" */
    0x70, 0x82, 0x8, 0x20, 0x87, 0x0,

    /* U+002A "*" */
    0x0, 0x28, 0x7d, 0x24,

    /* U+002B "+" */
    0x8, 0x7f, 0x8, 0x4,

    /* U+002C "," */
    0x6, 0x90,

    /* U+002D "-" */
    0x70,

    /* U+002E "." */
    0x6,

    /* U+002F "/" */
    0x14, 0x83, 0xc, 0x62, 0x4c, 0x0,

    /* U+0030 "0" */
    0x2f, 0x86, 0x6, 0x90, 0x39, 0x3, 0x60, 0x62,
    0xfc,

    /* U+0031 "1" */
    0x7c, 0x3, 0x0, 0xc0, 0x30, 0xc, 0x2f, 0xe0,

    /* U+0032 "2" */
    0x7f, 0xc0, 0x9, 0x2, 0x82, 0xc0, 0x60, 0xb,
    0xfd,

    /* U+0033 "3" */
    0xbf, 0xc0, 0x60, 0x2f, 0x80, 0xc, 0x0, 0xc7,
    0xf8,

    /* U+0034 "4" */
    0x2, 0xc0, 0x37, 0x2, 0x4c, 0x18, 0x30, 0x7f,
    0xf0, 0x3, 0x0,

    /* U+0035 "5" */
    0x7f, 0xc6, 0x0, 0x7f, 0x80, 0xc, 0x0, 0x87,
    0xf8,

    /* U+0036 "6" */
    0x2f, 0xd6, 0x0, 0xbf, 0xc9, 0x6, 0x60, 0x62,
    0xfc,

    /* U+0037 "7" */
    0xbf, 0xc0, 0xc, 0x2, 0x40, 0x30, 0xc, 0x1,
    0x80,

    /* U+0038 "8" */
    0x3f, 0xc6, 0x9, 0x3f, 0xc6, 0x5, 0x90, 0x63,
    0xfc,

    /* U+0039 "9" */
    0x3f, 0x89, 0x9, 0x90, 0x53, 0xfd, 0x0, 0x97,
    0xf8,

    /* U+003A ":" */
    0x60, 0x0, 0x60,

    /* U+003B ";" */
    0x60, 0x0, 0x65,

    /* U+003C "<" */
    0x0, 0x23, 0x4d, 0x8,

    /* U+003D "=" */
    0x7e, 0x0, 0x7e,

    /* U+003E ">" */
    0x0, 0x60, 0x1c, 0x28, 0x10,

    /* U+003F "?" */
    0x7e, 0x0, 0x60, 0x18, 0xb8, 0x0, 0x9, 0x0,

    /* U+0040 "@" */
    0x7f, 0xd0, 0x0, 0x92, 0xb9, 0x58, 0x66, 0x61,
    0x98, 0xaf, 0xe0,

    /* U+0041 "A" */
    0x7, 0x40, 0x33, 0x1, 0x48, 0xf, 0xf8, 0x20,
    0x22, 0x0, 0x60,

    /* U+0042 "B" */
    0x7f, 0xd6, 0x6, 0x7f, 0xc6, 0x6, 0x60, 0x27,
    0xfd,

    /* U+0043 "C" */
    0x2f, 0xe6, 0x0, 0x90, 0x9, 0x0, 0x60, 0x2,
    0xfe,

    /* U+0044 "D" */
    0x7f, 0xd1, 0x80, 0xc6, 0x3, 0x18, 0xc, 0x60,
    0x31, 0xff, 0x40,

    /* U+0045 "E" */
    0x7f, 0xd6, 0x0, 0x7f, 0xd6, 0x0, 0x60, 0x7,
    0xfd,

    /* U+0046 "F" */
    0x7f, 0xd6, 0x0, 0x7f, 0xd6, 0x0, 0x60, 0x6,
    0x0,

    /* U+0047 "G" */
    0x2f, 0xf1, 0x80, 0x9, 0x1f, 0x24, 0x8, 0x60,
    0x30, 0xbf, 0x80,

    /* U+0048 "H" */
    0x60, 0x25, 0x80, 0x97, 0xff, 0x58, 0x9, 0x60,
    0x25, 0x80, 0x90,

    /* U+0049 "I" */
    0x22, 0x22, 0x22,

    /* U+004A "J" */
    0x2, 0x40, 0x90, 0x24, 0x9, 0x2, 0x1f, 0x80,

    /* U+004B "K" */
    0x60, 0xa1, 0x89, 0x7, 0xe0, 0x18, 0xd0, 0x60,
    0xc1, 0x81, 0xc0,

    /* U+004C "L" */
    0x60, 0x6, 0x0, 0x60, 0x6, 0x0, 0x60, 0x7,
    0xfc,

    /* U+004D "M" */
    0x1c, 0xe, 0xd, 0x85, 0xc3, 0x32, 0x30, 0x8c,
    0xc9, 0x62, 0x61, 0x64, 0x74, 0x60,

    /* U+004E "N" */
    0x38, 0xc, 0x69, 0xc, 0x63, 0xc, 0x61, 0x8c,
    0x60, 0x9c, 0x60, 0x3c,

    /* U+004F "O" */
    0x2f, 0xe1, 0x80, 0x99, 0x1, 0x64, 0x5, 0x60,
    0x24, 0xbf, 0x80,

    /* U+0050 "P" */
    0x7f, 0xd6, 0x3, 0x60, 0x37, 0xfd, 0x60, 0x6,
    0x0,

    /* U+0051 "Q" */
    0x2f, 0xe1, 0x80, 0x99, 0x1, 0x64, 0x5, 0x60,
    0x24, 0xbf, 0x80, 0x1c, 0x0,

    /* U+0052 "R" */
    0x7f, 0xe1, 0x80, 0xc6, 0xbd, 0x19, 0xc0, 0x61,
    0x81, 0x82, 0x80,

    /* U+0053 "S" */
    0x3f, 0xc9, 0x0, 0x39, 0x0, 0x2c, 0x0, 0x97,
    0xfc,

    /* U+0054 "T" */
    0xbf, 0xe0, 0x50, 0x5, 0x0, 0x50, 0x5, 0x0,
    0x50,

    /* U+0055 "U" */
    0x60, 0x25, 0x80, 0x96, 0x2, 0x58, 0x9, 0x20,
    0x20, 0xbf, 0x80,

    /* U+0056 "V" */
    0x90, 0x30, 0xc1, 0x83, 0x9, 0x6, 0x30, 0xd,
    0x80, 0x2c, 0x0,

    /* U+0057 "W" */
    0x90, 0xe0, 0x96, 0xb, 0xc, 0x31, 0x64, 0xc2,
    0x21, 0x98, 0x1b, 0xe, 0x40, 0xe0, 0xb0,

    /* U+0058 "X" */
    0x60, 0x30, 0xa3, 0x0, 0xf4, 0x6, 0x30, 0x30,
    0x91, 0x80, 0xc0,

    /* U+0059 "Y" */
    0x90, 0x30, 0xc3, 0x0, 0xe4, 0x2, 0xc0, 0x6,
    0x0, 0x18, 0x0,

    /* U+005A "Z" */
    0x7f, 0xc0, 0xc, 0x7, 0x41, 0x80, 0x60, 0x7,
    0xfc,

    /* U+005B "[" */
    0x75, 0x86, 0x18, 0x61, 0x87, 0x40,

    /* U+005C "\\" */
    0xc2, 0x46, 0xc, 0x30, 0x81, 0x40,

    /* U+005D "]" */
    0x70, 0x82, 0x8, 0x20, 0x87, 0x0,

    /* U+005E "^" */
    0x10, 0x28,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x10, 0x80,

    /* U+0061 "a" */
    0x7f, 0x41, 0xf2, 0x8d, 0x83, 0x7f, 0xc0,

    /* U+0062 "b" */
    0x60, 0x7, 0xf8, 0x60, 0x86, 0x9, 0x60, 0x87,
    0xf8,

    /* U+0063 "c" */
    0x2f, 0x98, 0x5, 0x1, 0x80, 0x2f, 0x80,

    /* U+0064 "d" */
    0x0, 0x82, 0xfc, 0x60, 0x85, 0x8, 0x60, 0x82,
    0xfc,

    /* U+0065 "e" */
    0x2f, 0x86, 0xc, 0x7f, 0xc6, 0x0, 0x2f, 0xc0,

    /* U+0066 "f" */
    0x39, 0xbd, 0x30, 0x30, 0x30, 0x30,

    /* U+0067 "g" */
    0x3f, 0xc9, 0xc, 0x50, 0xc2, 0xfc, 0x0, 0xc3,
    0xf4,

    /* U+0068 "h" */
    0x60, 0x7, 0xf8, 0x60, 0xc6, 0xc, 0x60, 0xc6,
    0xc,

    /* U+0069 "i" */
    0x16, 0x66, 0x66,

    /* U+006A "j" */
    0x8, 0x20, 0x82, 0x8, 0x23, 0x40,

    /* U+006B "k" */
    0x60, 0x6, 0xc, 0x63, 0x7, 0xd0, 0x63, 0x6,
    0xc,

    /* U+006C "l" */
    0x66, 0x66, 0x66,

    /* U+006D "m" */
    0x7f, 0xfd, 0x60, 0x83, 0x60, 0x83, 0x60, 0x83,
    0x60, 0x83,

    /* U+006E "n" */
    0x7f, 0x86, 0xc, 0x60, 0xc6, 0xc, 0x60, 0xc0,

    /* U+006F "o" */
    0x2f, 0x86, 0x9, 0x50, 0x56, 0x9, 0x2f, 0x80,

    /* U+0070 "p" */
    0x7f, 0x86, 0x9, 0x60, 0x96, 0x9, 0x7f, 0x86,
    0x0,

    /* U+0071 "q" */
    0x2f, 0xc6, 0x8, 0x50, 0x86, 0x8, 0x2f, 0xc0,
    0x8,

    /* U+0072 "r" */
    0x3e, 0x60, 0x60, 0x60, 0x60,

    /* U+0073 "s" */
    0x7f, 0x64, 0x2, 0xe0, 0x6, 0x7f, 0x40,

    /* U+0074 "t" */
    0x30, 0xbd, 0x30, 0x30, 0x30, 0x2d,

    /* U+0075 "u" */
    0x60, 0xc6, 0xc, 0x60, 0xc6, 0xc, 0x3f, 0xc0,

    /* U+0076 "v" */
    0x90, 0x93, 0xc, 0x31, 0x81, 0xa0, 0xe, 0x0,

    /* U+0077 "w" */
    0x92, 0x82, 0x52, 0x85, 0x26, 0x58, 0x39, 0x2c,
    0x2c, 0x38,

    /* U+0078 "x" */
    0x60, 0xc2, 0x64, 0xe, 0x2, 0x70, 0x60, 0xc0,

    /* U+0079 "y" */
    0x90, 0xc6, 0x8, 0x32, 0x41, 0xb0, 0x9, 0x7,
    0x80,

    /* U+007A "z" */
    0x7f, 0x40, 0xd0, 0xd1, 0xc0, 0x7f, 0x80,

    /* U+007B "{" */
    0x28, 0xc3, 0x28, 0x30, 0xc2, 0x80,

    /* U+007C "|" */
    0x22, 0x22, 0x22, 0x20,

    /* U+007D "}" */
    0xa0, 0xc3, 0xa, 0x30, 0xca, 0x0,

    /* U+007E "~" */
    0x26, 0x26,

    /* U+00A1 "¡" */
    0x61, 0x56, 0x66,

    /* U+00A2 "¢" */
    0x2, 0x2, 0xfc, 0x52, 0x9, 0x20, 0x52, 0x2,
    0xfc, 0x2, 0x0,

    /* U+00A3 "£" */
    0xb, 0xe1, 0x80, 0xbf, 0xe2, 0x40, 0x24, 0xb,
    0xfe,

    /* U+00A4 "¤" */
    0x0, 0x2, 0xe8, 0x31, 0x83, 0x18, 0x2e, 0x80,
    0x0,

    /* U+00A5 "¥" */
    0x90, 0x30, 0xc3, 0x1, 0xe4, 0x1f, 0xf8, 0x7f,
    0xe0, 0x18, 0x0,

    /* U+00A6 "¦" */
    0x22, 0x10, 0x12, 0x20,

    /* U+00A7 "§" */
    0x3f, 0xc6, 0x0, 0x7f, 0x49, 0xc, 0x2a, 0xc0,
    0xc, 0x7f, 0x80,

    /* U+00A8 "¨" */
    0x28,

    /* U+00A9 "©" */
    0x1a, 0xa0, 0x80, 0x25, 0x78, 0xe7, 0x3, 0x9c,
    0xc, 0x9e, 0x61, 0xaa, 0x0,

    /* U+00AA "ª" */
    0x75, 0xaa, 0x80,

    /* U+00AB "«" */
    0x0, 0x0, 0x85, 0x36, 0x83, 0x68, 0x8, 0x50,

    /* U+00AE "®" */
    0x1a, 0x45, 0xa4, 0x9a, 0x45, 0x54, 0x2a, 0x40,

    /* U+00AF "¯" */
    0xa0,

    /* U+00B0 "°" */
    0x28, 0x88, 0x28,

    /* U+00B1 "±" */
    0x8, 0x7f, 0x8, 0x0, 0x7e,

    /* U+00B2 "²" */
    0x71, 0xce, 0x0,

    /* U+00B3 "³" */
    0xb4, 0x86, 0x40,

    /* U+00B4 "´" */
    0x15,

    /* U+00B6 "¶" */
    0x3f, 0x7b, 0xf7, 0xbf, 0x72, 0xf7, 0x1, 0x70,
    0x17, 0x1, 0x70,

    /* U+00B7 "·" */
    0xc0,

    /* U+00B8 "¸" */
    0x16,

    /* U+00B9 "¹" */
    0x91, 0x4b, 0x0,

    /* U+00BA "º" */
    0xa8, 0xcc, 0xa8,

    /* U+00BB "»" */
    0x0, 0x6, 0x20, 0x1c, 0xd2, 0x9c, 0x12, 0x0,

    /* U+00BC "¼" */
    0x20, 0x22, 0x8, 0x28, 0x80, 0x44, 0x9, 0xa2,
    0x2a, 0x0, 0x0,

    /* U+00BD "½" */
    0x20, 0x22, 0x5, 0x20, 0xc2, 0x88, 0x8, 0xa1,
    0x49, 0x20, 0xa0,

    /* U+00BF "¿" */
    0x6, 0x0, 0x2, 0xe1, 0x40, 0x90, 0xb, 0xe0,

    /* U+00C0 "À" */
    0x0, 0x0, 0x8, 0x0, 0x0, 0x1, 0xd0, 0xc,
    0xc0, 0x52, 0x3, 0xfe, 0x8, 0x8, 0x80, 0x18,

    /* U+00C1 "Á" */
    0x0, 0x0, 0x8, 0x0, 0x0, 0x1, 0xd0, 0xc,
    0xc0, 0x52, 0x3, 0xfe, 0x8, 0x8, 0x80, 0x18,

    /* U+00C2 "Â" */
    0x1, 0x0, 0x29, 0x0, 0x0, 0x1, 0xd0, 0xc,
    0xc0, 0x52, 0x3, 0xfe, 0x8, 0x8, 0x80, 0x18,

    /* U+00C3 "Ã" */
    0xa, 0x80, 0x0, 0x0, 0x74, 0x3, 0x30, 0x14,
    0x80, 0xff, 0x82, 0x2, 0x20, 0x6,

    /* U+00C4 "Ä" */
    0x9, 0x80, 0x0, 0x0, 0x74, 0x3, 0x30, 0x14,
    0x80, 0xff, 0x82, 0x2, 0x20, 0x6,

    /* U+00C5 "Å" */
    0x2, 0x0, 0x15, 0x0, 0x20, 0x1, 0xd0, 0xc,
    0xc0, 0x52, 0x3, 0xfe, 0x8, 0x8, 0x80, 0x18,

    /* U+00C6 "Æ" */
    0x2, 0xff, 0xe0, 0x93, 0x0, 0x8, 0x3f, 0xe2,
    0xff, 0x0, 0x20, 0x30, 0x9, 0x3, 0xfe,

    /* U+00C7 "Ç" */
    0x2f, 0xe6, 0x0, 0x90, 0x9, 0x0, 0x60, 0x2,
    0xfe, 0x3, 0x0, 0x10,

    /* U+00C8 "È" */
    0x4, 0x0, 0x60, 0x0, 0x7, 0xfd, 0x60, 0x7,
    0xfd, 0x60, 0x6, 0x0, 0x7f, 0xd0,

    /* U+00C9 "É" */
    0x1, 0x0, 0x30, 0x0, 0x7, 0xfd, 0x60, 0x7,
    0xfd, 0x60, 0x6, 0x0, 0x7f, 0xd0,

    /* U+00CA "Ê" */
    0x1, 0x0, 0xa4, 0x0, 0x7, 0xfd, 0x60, 0x7,
    0xfd, 0x60, 0x6, 0x0, 0x7f, 0xd0,

    /* U+00CB "Ë" */
    0xd, 0x40, 0x0, 0x7f, 0xd6, 0x0, 0x7f, 0xd6,
    0x0, 0x60, 0x7, 0xfd,

    /* U+00CC "Ì" */
    0x46, 0x2, 0x22, 0x22, 0x20,

    /* U+00CD "Í" */
    0x10, 0xc0, 0x8, 0x20, 0x82, 0x8, 0x20,

    /* U+00CE "Î" */
    0x4, 0x29, 0x0, 0x8, 0x8, 0x8, 0x8, 0x8,
    0x8,

    /* U+00CF "Ï" */
    0xd4, 0x2, 0x8, 0x20, 0x82, 0x8,

    /* U+00D0 "Ð" */
    0x7f, 0xd1, 0x80, 0xcb, 0xd3, 0x18, 0xc, 0x60,
    0x31, 0xff, 0x40,

    /* U+00D1 "Ñ" */
    0x6, 0x50, 0x8, 0x80, 0x0, 0x0, 0x38, 0xc,
    0x69, 0xc, 0x63, 0xc, 0x61, 0x8c, 0x60, 0x9c,
    0x60, 0x3c,

    /* U+00D2 "Ò" */
    0x1, 0x0, 0x8, 0x0, 0x0, 0xb, 0xf8, 0x60,
    0x26, 0x40, 0x59, 0x1, 0x58, 0x9, 0x2f, 0xe0,

    /* U+00D3 "Ó" */
    0x0, 0x0, 0x8, 0x0, 0x0, 0xb, 0xf8, 0x60,
    0x26, 0x40, 0x59, 0x1, 0x58, 0x9, 0x2f, 0xe0,

    /* U+00D4 "Ô" */
    0x1, 0x0, 0x2a, 0x0, 0x0, 0xb, 0xf8, 0x60,
    0x26, 0x40, 0x59, 0x1, 0x58, 0x9, 0x2f, 0xe0,

    /* U+00D5 "Õ" */
    0x9, 0x80, 0x26, 0x0, 0x0, 0xb, 0xf8, 0x60,
    0x26, 0x40, 0x59, 0x1, 0x58, 0x9, 0x2f, 0xe0,

    /* U+00D6 "Ö" */
    0x9, 0x80, 0x0, 0x2, 0xfe, 0x18, 0x9, 0x90,
    0x16, 0x40, 0x56, 0x2, 0x4b, 0xf8,

    /* U+00D7 "×" */
    0x51, 0x3c, 0x3d, 0x1,

    /* U+00D8 "Ø" */
    0x2f, 0xf1, 0x81, 0xd9, 0x15, 0x65, 0x45, 0x74,
    0x24, 0xff, 0x80,

    /* U+00D9 "Ù" */
    0x1, 0x0, 0x8, 0x0, 0x0, 0x18, 0x9, 0x60,
    0x25, 0x80, 0x96, 0x2, 0x48, 0x8, 0x2f, 0xe0,

    /* U+00DA "Ú" */
    0x0, 0x0, 0x8, 0x0, 0x0, 0x18, 0x9, 0x60,
    0x25, 0x80, 0x96, 0x2, 0x48, 0x8, 0x2f, 0xe0,

    /* U+00DB "Û" */
    0x1, 0x0, 0x2a, 0x0, 0x0, 0x18, 0x9, 0x60,
    0x25, 0x80, 0x96, 0x2, 0x48, 0x8, 0x2f, 0xe0,

    /* U+00DC "Ü" */
    0x9, 0x80, 0x0, 0x6, 0x2, 0x58, 0x9, 0x60,
    0x25, 0x80, 0x92, 0x2, 0xb, 0xf8,

    /* U+00DD "Ý" */
    0x1, 0x0, 0x8, 0x0, 0x0, 0x24, 0xc, 0x30,
    0xc0, 0x39, 0x0, 0xb0, 0x1, 0x80, 0x6, 0x0,

    /* U+00DE "Þ" */
    0x60, 0x7, 0xfd, 0x60, 0x36, 0x3, 0x7f, 0xd6,
    0x0,

    /* U+00DF "ß" */
    0x2f, 0xd2, 0x6, 0x67, 0xd6, 0x3, 0x60, 0x36,
    0xbd,

    /* U+00E0 "à" */
    0xc, 0x1, 0x7, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E1 "á" */
    0x6, 0x1, 0x7, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E2 "â" */
    0xd, 0x4, 0x47, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E3 "ã" */
    0x19, 0x4, 0x87, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E4 "ä" */
    0x17, 0x0, 0x7, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E5 "å" */
    0x5, 0x1, 0x47, 0xf4, 0x1f, 0x28, 0xd8, 0x37,
    0xfc,

    /* U+00E6 "æ" */
    0x7f, 0xbf, 0x1, 0xf0, 0x62, 0x8e, 0xba, 0x83,
    0x0, 0x7f, 0xbf, 0x40,

    /* U+00E7 "ç" */
    0x2f, 0x98, 0x5, 0x1, 0x80, 0x2f, 0x82, 0x40,
    0x40,

    /* U+00E8 "è" */
    0xc, 0x0, 0x40, 0x2f, 0x86, 0xc, 0x7f, 0xc6,
    0x0, 0x2f, 0xc0,

    /* U+00E9 "é" */
    0x3, 0x0, 0x10, 0x2f, 0x86, 0xc, 0x7f, 0xc6,
    0x0, 0x2f, 0xc0,

    /* U+00EA "ê" */
    0xa, 0x0, 0x50, 0x2f, 0x86, 0xc, 0x7f, 0xc6,
    0x0, 0x2f, 0xc0,

    /* U+00EB "ë" */
    0xa, 0x0, 0x0, 0x2f, 0x86, 0xc, 0x7f, 0xc6,
    0x0, 0x2f, 0xc0,

    /* U+00EC "ì" */
    0x81, 0x66, 0x66, 0x60,

    /* U+00ED "í" */
    0x30, 0x46, 0x18, 0x61, 0x86, 0x0,

    /* U+00EE "î" */
    0x18, 0x10, 0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+00EF "ï" */
    0x25, 0x0, 0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+00F0 "ð" */
    0x0, 0x0, 0xa9, 0x9, 0xc3, 0xfd, 0x90, 0x99,
    0x9, 0x3f, 0x80,

    /* U+00F1 "ñ" */
    0x19, 0x41, 0x20, 0x7f, 0x86, 0xc, 0x60, 0xc6,
    0xc, 0x60, 0xc0,

    /* U+00F2 "ò" */
    0x8, 0x0, 0x0, 0x2f, 0x86, 0x9, 0x50, 0x56,
    0x9, 0x2f, 0x80,

    /* U+00F3 "ó" */
    0x3, 0x0, 0x10, 0x2f, 0x86, 0x9, 0x50, 0x56,
    0x9, 0x2f, 0x80,

    /* U+00F4 "ô" */
    0xa, 0x0, 0x50, 0x2f, 0x86, 0x9, 0x50, 0x56,
    0x9, 0x2f, 0x80,

    /* U+00F5 "õ" */
    0x19, 0x41, 0x20, 0x2f, 0x86, 0x9, 0x50, 0x56,
    0x9, 0x2f, 0x80,

    /* U+00F6 "ö" */
    0xa, 0x0, 0x0, 0x2f, 0x86, 0x9, 0x50, 0x56,
    0x9, 0x2f, 0x80,

    /* U+00F7 "÷" */
    0x14, 0x7e, 0x0, 0x14, 0x0,

    /* U+00F8 "ø" */
    0x2f, 0xc6, 0x19, 0x55, 0x56, 0x49, 0x3f, 0x80,

    /* U+00F9 "ù" */
    0xc, 0x0, 0x40, 0x60, 0xc6, 0xc, 0x60, 0xc6,
    0xc, 0x3f, 0xc0,

    /* U+00FA "ú" */
    0x2, 0x0, 0x40, 0x60, 0xc6, 0xc, 0x60, 0xc6,
    0xc, 0x3f, 0xc0,

    /* U+00FB "û" */
    0x9, 0x0, 0x10, 0x60, 0xc6, 0xc, 0x60, 0xc6,
    0xc, 0x3f, 0xc0,

    /* U+00FC "ü" */
    0x17, 0x0, 0x0, 0x60, 0xc6, 0xc, 0x60, 0xc6,
    0xc, 0x3f, 0xc0,

    /* U+00FD "ý" */
    0x1, 0x0, 0x50, 0x0, 0x9, 0xc, 0x60, 0x83,
    0x24, 0x1b, 0x0, 0x90, 0x78, 0x0,

    /* U+00FE "þ" */
    0x60, 0x7, 0xf8, 0x60, 0x96, 0x9, 0x60, 0x97,
    0xf8, 0x60, 0x0,

    /* U+00FF "ÿ" */
    0x17, 0x0, 0x0, 0x90, 0xc6, 0x8, 0x32, 0x41,
    0xb0, 0x9, 0x7, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 33, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 34, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 58, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 6, .adv_w = 107, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 33, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 53, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 59, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 69, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 73, .adv_w = 35, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 75, .adv_w = 43, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 34, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 83, .adv_w = 102, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 102, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 34, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 36, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 180, .adv_w = 59, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 184, .adv_w = 65, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 187, .adv_w = 59, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 192, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 106, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 40, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 100, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 86, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 146, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 124, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 381, .adv_w = 103, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 158, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 100, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 484, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 490, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 496, .adv_w = 90, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 498, .adv_w = 49, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 499, .adv_w = 90, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 501, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 90, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 60, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 556, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 37, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 37, .box_w = 3, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 574, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 37, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 137, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 621, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 630, .adv_w = 61, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 63, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 93, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 129, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 88, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 86, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 691, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 704, .adv_w = 40, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 708, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 714, .adv_w = 110, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 716, .adv_w = 34, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 719, .adv_w = 89, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 730, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 100, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 40, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 763, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 774, .adv_w = 65, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 775, .adv_w = 119, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 791, .adv_w = 97, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 799, .adv_w = 91, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 807, .adv_w = 65, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 808, .adv_w = 55, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 811, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 816, .adv_w = 39, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 819, .adv_w = 40, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 822, .adv_w = 90, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 823, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 834, .adv_w = 39, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 835, .adv_w = 82, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 836, .adv_w = 36, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 839, .adv_w = 51, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 842, .adv_w = 97, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 850, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 861, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 880, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 972, .adv_w = 164, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 999, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1027, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1041, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1053, .adv_w = 40, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1058, .adv_w = 40, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1065, .adv_w = 40, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 40, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1080, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1125, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1141, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1157, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 68, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1191, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1218, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1250, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 100, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1280, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1289, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1298, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1307, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1316, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1325, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1334, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1343, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1352, .adv_w = 145, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1364, .adv_w = 82, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1373, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1384, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1395, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1406, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1417, .adv_w = 37, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1421, .adv_w = 37, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1427, .adv_w = 37, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1434, .adv_w = 37, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1441, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1452, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1463, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1474, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1485, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1496, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1507, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1518, .adv_w = 65, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1523, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1542, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1553, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1564, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1575, .adv_w = 86, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1589, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1600, .adv_w = 86, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1}
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
    0, 0, -9, 0, 0, 0, 0, 0,
    0, -12, -19, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    -3, -3, -3, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, -3, -3, 0, 0,
    -8, 0, 0, 0, 0, -3, -3, 0,
    0, 0, -8, 0, -5, -4, -3, -10,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -3, -4, -3, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    -8, -3, -10, -4, -3, 0, 0, 0,
    0, 0, 0, 0, -12, 0, -17, -12,
    0, -19, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -13, -5, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 0, -3, 0,
    0, 0, -3, 0, 0, -3, 0, 0,
    0, -5, -5, -4, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, -1, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -3, 0, 0, 0, -1, 0, -4, -3,
    0, 0, -5, -1, 0, 0, -8, 0,
    0, 0, 0, -3, -5, 0, 0, 0,
    -3, 0, -3, -3, -3, -5, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, -1, 0, -1, 0, 0,
    0, -4, 0, 0, -13, 0, 0, -4,
    0, 0, -4, 0, 0, 0, -6, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -12, 0, -12, -9, 0, -13,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -1, 0, -4, 0, 0, 0,
    -6, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -4, -3, 0, 0,
    0, 0, 0, 0, -5, 0, 0, -3,
    0, -1, 0, 0, 0, 0, -3, 0,
    -5, -5, -3, -5, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -1, 0, 0, 0, 0, -4,
    0, 0, -5, 0, 0, 0, -3, 0,
    0, 0, 0, -3, 0, 0, -9, 0,
    -3, -3, 0, 0, -3, 0, 0, 0,
    -5, 0, -5, -5, 0, -5, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, -3, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, -22, -6, -3, 0,
    -3, 0, -12, 0, 0, -3, 0, 0,
    0, -15, -13, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, -5, 0, -4, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -20,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, -9, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, -3,
    -3, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, 0, 0, -3, 0, 0, -3, 0,
    0, 0, -4, 0, -8, -1, 0, 0,
    -3, 0, 0, 0, 0, 0, -14, -4,
    -14, -13, 0, -18, 0, -8, 0, -1,
    -1, -1, 0, 0, 0, -3, -1, -9,
    -6, 0, -3, 0, 0, -3, -6, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    -4, 0, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, -3, 0, 0, 0, 0,
    0, -5, -5, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, -3, -1, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, -15, -4, -3, 0, 0, 0,
    -3, 0, -5, 0, 0, 0, 0, -12,
    -32, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -1, 0, -1,
    0, -1, -1, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, -18, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -1, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -1, -3, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, -4, 0, 0,
    0, 0, -5, -5, -5, 0, -4, -1,
    0, 0, 0, 0, 0, 0, -24, 0,
    0, -5, 0, 0, -4, 0, 0, 0,
    -5, 0, -13, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -20, -4, -18, -15,
    0, -23, 0, -4, 0, -3, -3, -3,
    0, 0, 0, -4, -3, -17, -12, 0,
    -6, 0, 0, 0, -10, 0, 0, -1,
    -4, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -8, 0,
    -8, -8, 0, -10, 0, -3, 0, -1,
    0, 0, 0, 0, 0, 0, -1, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -3, 0, 0, 0,
    -3, 0, -4, -3, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, -5,
    -15, -9, 0, 0, 0, 0, -5, 0,
    0, -3, 0, 0, 0, -13, -32, -6,
    0, -1, 0, 0, -3, -3, -5, -4,
    -5, 0, 0, -4, 0, -3, 0, -3,
    -1, 0, 0, 0, 0, -3, 0, 0,
    -1, 0, 0, -19, 0, 0, 0, 0,
    0, -3, 0, 0, -1, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, -3, -4,
    0, -4, 0, 0, 0, -2, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -1, 0, 0, 0, -5, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, -4,
    -3, -1, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -9, -12, -8,
    -3, 0, 0, 0, -15, 0, 0, -3,
    0, 0, -9, -14, -23, -8, -3, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -10, 0, -9, -9, -10, -8, 0,
    -9, -6, -1, -3, -3, -8, -3, 0,
    -1, -19, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, -5, -17, -6, -3, 0, 0, 0,
    -6, 0, 0, -4, 0, 0, 0, -14,
    -20, -8, -4, -1, 0, 0, 0, 0,
    0, 0, -3, 0, -4, -8, -1, -8,
    -6, -6, -6, 0, -3, 0, 0, -4,
    0, -5, 0, 0, -4, -18, -5, 0,
    0, 0, 0, -4, -12, -6, -3, 0,
    0, -3, -9, 0, 0, -3, 0, 0,
    -6, -13, -17, -8, -3, -3, 0, 0,
    0, 0, 0, 0, -1, 0, -4, -6,
    -1, -6, -4, -6, -5, 0, -3, 0,
    0, -3, 0, -4, 0, 0, -4, -14,
    -3, 0, 0, 0, 0, -3, 0, 0,
    -3, 0, 0, 0, -3, 0, 0, -3,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -5, 0, -1, 0, 0,
    0, -5, -3, 0, -1, 0, 0, 0,
    -4, 0, -3, 0, 0, 0, 0, -10,
    -19, -8, -5, 0, 0, 0, -13, 0,
    0, -4, 0, -3, 0, -17, -23, -10,
    -4, -3, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -12, -3, -10, -6, -12,
    -9, 0, -5, -4, -3, -4, -3, -6,
    -5, 0, -4, -19, -5, 0, 0, 0,
    0, -3, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, -1, 0,
    0, -1, 0, 0, 0, -3, 0, -3,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, -3, -3, 0, -6, -1, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    -9, -6, 0, -8, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, -6,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, 0, -9, -6, 0, -10, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -4, 0, -4, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -3, 0,
    -3, -1, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, -1, -3, 0,
    0, 0, -10, 0, -8, -5, -4, -10,
    -3, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -1, -3, -3, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, -5, 0, 0, 0, 0, 0,
    0, -8, -17, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    -3, 0, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, -5, -4, 0, -4, 0, 0,
    0, -5, 0, -4, 0, 0, -4, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, -9, -17, 0,
    0, 0, -5, 0, 0, 0, 0, -3,
    0, 0, 0, -3, 3, -1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -4, -5,
    0, -5, -1, 0, 0, 0, 0, -1,
    0, 0, -2, 0, 0, -1, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -13, -3,
    -1, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, -6, -13, 0, 0, 0,
    -6, 0, 0, 0, -5, 0, -5, 0,
    0, -1, 0, -1, 0, -4, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, -3,
    -5, -3, 0, 0, 0, 0, -4, 0,
    0, 0, 0, 0, 0, -6, -12, 0,
    0, 0, -1, 0, 0, 0, -3, 0,
    -3, 0, 0, -1, 0, -1, 0, -1,
    -3, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, -10, 0, 0, 0, 0,
    0, -4, 0, 0, -1, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -4, -3,
    0, -4, 0, 0, 0, -3, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -8, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -6, 0, 0, 0, -3, 0,
    0, 0, -1, 0, -3, 0, 0, -3,
    0, -1, 0, -3, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, -9, -4, 0, -6, 0, -4,
    0, -4, 0, -3, 0, 0, -1, 0,
    0, -3, -3, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -3, 0, 0, 0,
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
const lv_font_t f1font_8 = {
#else
lv_font_t f1font_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
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



#endif /*#if F1FONT_8*/
