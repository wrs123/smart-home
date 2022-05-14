/*******************************************************************************
 * Size: 50 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/
#include "lvgl.h"


#ifndef DGITAL_NUMBER_50
#define DGITAL_NUMBER_50 1
#endif

#if DGITAL_NUMBER_50

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t dgital_number_50_glyph_bitmap[] = {
    /* U+0025 "%" */
    0x0, 0x7f, 0xff, 0xf4, 0x0, 0x0, 0x0, 0xf,
    0xfc, 0x0, 0x0, 0x1, 0xff, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0, 0x2, 0xff,
    0xff, 0xfe, 0x0, 0x0, 0x0, 0x7f, 0xe0, 0x0,
    0x0, 0x1c, 0xbf, 0xff, 0xf8, 0xd0, 0x0, 0x0,
    0xff, 0xc0, 0x0, 0x0, 0x7f, 0x15, 0x55, 0x53,
    0xf4, 0x0, 0x2, 0xff, 0x40, 0x0, 0x0, 0xff,
    0x80, 0x0, 0x7, 0xfc, 0x0, 0x7, 0xff, 0x0,
    0x0, 0x0, 0xff, 0x80, 0x0, 0x7, 0xfc, 0x0,
    0xf, 0xfc, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0,
    0x7, 0xfc, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0x0,
    0xff, 0x80, 0x0, 0x7, 0xfc, 0x0, 0x3f, 0xf0,
    0x0, 0x0, 0x0, 0xff, 0x80, 0x0, 0x7, 0xfc,
    0x0, 0xbf, 0xd0, 0x0, 0x0, 0x0, 0xff, 0x80,
    0x0, 0x7, 0xfc, 0x1, 0xff, 0xc0, 0x0, 0x0,
    0x0, 0xff, 0x80, 0x0, 0x7, 0xfc, 0x3, 0xff,
    0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0, 0x7,
    0xfc, 0xb, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0x40, 0x0, 0x7, 0xf8, 0xf, 0xfc, 0x0, 0x0,
    0x0, 0x0, 0x3d, 0x3f, 0xff, 0xf5, 0xe0, 0x2f,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0xff,
    0xfc, 0x40, 0xf, 0xe0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xff, 0xfe, 0x0, 0xb, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0xff, 0xf8, 0x0,
    0x3, 0x80, 0x5, 0x55, 0x50, 0x0, 0x0, 0x5,
    0x55, 0x40, 0x0, 0x1, 0x0, 0x7f, 0xff, 0xfd,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xf8, 0x4, 0xbf, 0xff, 0xfe, 0x50, 0x0,
    0x0, 0x0, 0x0, 0x3f, 0xf0, 0x1f, 0x2f, 0xff,
    0xf8, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xe0,
    0x7f, 0xc0, 0x0, 0x3, 0xfd, 0x0, 0x0, 0x0,
    0x0, 0xff, 0xc0, 0x7f, 0xc0, 0x0, 0x3, 0xfd,
    0x0, 0x0, 0x0, 0x2, 0xff, 0x40, 0x7f, 0xc0,
    0x0, 0x3, 0xfd, 0x0, 0x0, 0x0, 0x7, 0xfe,
    0x0, 0x7f, 0xc0, 0x0, 0x3, 0xfd, 0x0, 0x0,
    0x0, 0xf, 0xfc, 0x0, 0x7f, 0xc0, 0x0, 0x3,
    0xfd, 0x0, 0x0, 0x0, 0x2f, 0xf4, 0x0, 0x7f,
    0xc0, 0x0, 0x3, 0xfd, 0x0, 0x0, 0x0, 0x3f,
    0xf0, 0x0, 0x7f, 0xc0, 0x0, 0x3, 0xfd, 0x0,
    0x0, 0x0, 0xbf, 0xd0, 0x0, 0x7f, 0xc0, 0x0,
    0x3, 0xfd, 0x0, 0x0, 0x1, 0xff, 0x80, 0x0,
    0x7f, 0xc0, 0x0, 0x3, 0xfd, 0x0, 0x0, 0x3,
    0xff, 0x0, 0x0, 0x2f, 0x45, 0x55, 0x51, 0xf8,
    0x0, 0x0, 0xb, 0xfd, 0x0, 0x0, 0x9, 0x3f,
    0xff, 0xfc, 0x60, 0x0, 0x0, 0xf, 0xfc, 0x0,
    0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0,
    0x3f, 0xf4, 0x0, 0x0, 0x0, 0xbf, 0xff, 0xfe,
    0x0, 0x0, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0x0,
    0x3f, 0xff, 0xf8, 0x0,

    /* U+002E "." */
    0xbf, 0x7f, 0xdf, 0xf7, 0xfd, 0xff, 0x7f, 0xdf,
    0xf7, 0xfd,

    /* U+0030 "0" */
    0x0, 0x7f, 0xff, 0xff, 0x0, 0x0, 0x7f, 0xff,
    0xff, 0xf0, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x72, 0xff, 0xff, 0xfd, 0x30, 0x7f, 0x15, 0x55,
    0x54, 0x3f, 0x3f, 0xd0, 0x0, 0x0, 0x2f, 0xef,
    0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0, 0x0,
    0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf, 0xbf,
    0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0,
    0xb, 0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff,
    0x40, 0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0,
    0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xf8,
    0x0, 0x0, 0x0, 0xbe, 0xe0, 0x0, 0x0, 0x0,
    0x3, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xd0, 0x0, 0x0, 0x0,
    0x1e, 0xff, 0x0, 0x0, 0x0, 0x7f, 0xbf, 0xd0,
    0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb,
    0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff, 0x40,
    0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0, 0x2f,
    0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0,
    0x0, 0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf,
    0xbf, 0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0,
    0x0, 0xb, 0xf9, 0xfc, 0x55, 0x55, 0x50, 0xfc,
    0x1c, 0xbf, 0xff, 0xff, 0x4c, 0x0, 0xbf, 0xff,
    0xff, 0xf4, 0x0, 0x1f, 0xff, 0xff, 0xfc, 0x0,
    0x1, 0xff, 0xff, 0xfc, 0x0,

    /* U+0031 "1" */
    0x0, 0x40, 0xe0, 0xf8, 0xfe, 0xbf, 0xbf, 0xef,
    0xfb, 0xfe, 0xff, 0xbf, 0xef, 0xfb, 0xfe, 0xff,
    0xbf, 0xeb, 0xf8, 0xbe, 0x7, 0x80, 0x0, 0x0,
    0x1e, 0x7f, 0xbf, 0xef, 0xfb, 0xfe, 0xff, 0xbf,
    0xef, 0xfb, 0xfe, 0xff, 0xbf, 0xef, 0xfa, 0xfe,
    0x3f, 0x83, 0xe0, 0x38, 0x1,

    /* U+0032 "2" */
    0x0, 0x7f, 0xff, 0xff, 0x0, 0x0, 0xbf, 0xff,
    0xff, 0xf0, 0x0, 0xbf, 0xff, 0xff, 0xfd, 0x0,
    0xff, 0xff, 0xff, 0xfd, 0x30, 0x15, 0x55, 0x55,
    0x54, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xe0,
    0x0, 0x0, 0x0, 0xb, 0xf8, 0x0, 0x0, 0x0,
    0x2, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xbf, 0x80,
    0x0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0, 0x0,
    0xb, 0xf8, 0x0, 0x0, 0x0, 0x2, 0xfe, 0x0,
    0x0, 0x0, 0x0, 0xbf, 0x80, 0x0, 0x0, 0x0,
    0x2f, 0xe0, 0x0, 0x0, 0x0, 0xb, 0xf8, 0x0,
    0x55, 0x55, 0x54, 0xbe, 0x1, 0xff, 0xff, 0xff,
    0xd3, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x83, 0xd2, 0xff, 0xff, 0xfe,
    0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xd0,
    0x0, 0x0, 0x0, 0xf, 0xf4, 0x0, 0x0, 0x0,
    0x3, 0xfd, 0x0, 0x0, 0x0, 0x0, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x3f, 0xd0, 0x0, 0x0, 0x0,
    0xf, 0xf4, 0x0, 0x0, 0x0, 0x3, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x3f, 0xd0, 0x0, 0x0, 0x0, 0xf, 0xf4, 0x0,
    0x0, 0x0, 0x1, 0xfc, 0x55, 0x55, 0x54, 0x0,
    0x1c, 0xbf, 0xff, 0xff, 0xd0, 0x0, 0xbf, 0xff,
    0xff, 0xfd, 0x0, 0x1f, 0xff, 0xff, 0xff, 0xd0,
    0x1, 0xff, 0xff, 0xff, 0xfc,

    /* U+0033 "3" */
    0x7f, 0xff, 0xff, 0xfd, 0x0, 0x1f, 0xff, 0xff,
    0xff, 0x40, 0x7, 0xff, 0xff, 0xff, 0x80, 0x1,
    0xff, 0xff, 0xfe, 0x34, 0x0, 0x15, 0x55, 0x54,
    0xfd, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff,
    0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0, 0x0,
    0x1, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0,
    0x0, 0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x1,
    0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x55, 0x55, 0x54, 0xbf,
    0x3, 0xff, 0xff, 0xff, 0x4b, 0x2f, 0xff, 0xff,
    0xff, 0xf0, 0x2f, 0xff, 0xff, 0xff, 0xe0, 0x2,
    0xff, 0xff, 0xfe, 0x1f, 0x0, 0x0, 0x0, 0x0,
    0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff,
    0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0, 0x0,
    0x1, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0,
    0x0, 0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x1,
    0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x15, 0x55, 0x54, 0xfd,
    0x1, 0xff, 0xff, 0xfe, 0x34, 0x7, 0xff, 0xff,
    0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0x40, 0x7f,
    0xff, 0xff, 0xfd, 0x0,

    /* U+0034 "4" */
    0x40, 0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0,
    0x0, 0x0, 0xef, 0x80, 0x0, 0x0, 0x0, 0xfb,
    0xf8, 0x0, 0x0, 0x0, 0xfe, 0xff, 0x40, 0x0,
    0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0, 0x2f, 0xef,
    0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0, 0x0,
    0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf, 0xbf,
    0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0,
    0xb, 0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff,
    0x40, 0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0,
    0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xf8,
    0x55, 0x55, 0x54, 0xbe, 0xe1, 0xff, 0xff, 0xff,
    0xd3, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x80, 0x2, 0xff, 0xff, 0xfe,
    0x1e, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x80, 0x0,
    0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0, 0x0, 0xb,
    0xf8, 0x0, 0x0, 0x0, 0x2, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0x80, 0x0, 0x0, 0x0, 0x2f,
    0xe0, 0x0, 0x0, 0x0, 0xb, 0xf8, 0x0, 0x0,
    0x0, 0x2, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0x80, 0x0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x0, 0xb, 0xf8, 0x0, 0x0, 0x0, 0x2, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x38,
    0x0, 0x0, 0x0, 0x0, 0x1,

    /* U+0035 "5" */
    0x0, 0x7f, 0xff, 0xff, 0xfd, 0x0, 0x7f, 0xff,
    0xff, 0xfd, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x72, 0xff, 0xff, 0xfd, 0x0, 0x7f, 0x15, 0x55,
    0x54, 0x0, 0x3f, 0xd0, 0x0, 0x0, 0x0, 0xf,
    0xf4, 0x0, 0x0, 0x0, 0x3, 0xfd, 0x0, 0x0,
    0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0x3f,
    0xd0, 0x0, 0x0, 0x0, 0xf, 0xf4, 0x0, 0x0,
    0x0, 0x3, 0xfd, 0x0, 0x0, 0x0, 0x0, 0xff,
    0x40, 0x0, 0x0, 0x0, 0x3f, 0xd0, 0x0, 0x0,
    0x0, 0xf, 0xf4, 0x0, 0x0, 0x0, 0x3, 0xf8,
    0x55, 0x55, 0x54, 0x0, 0xe1, 0xff, 0xff, 0xff,
    0xd0, 0x3, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x80, 0x2, 0xff, 0xff, 0xfe,
    0x1e, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x80, 0x0,
    0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0, 0x0, 0xb,
    0xf8, 0x0, 0x0, 0x0, 0x2, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0x80, 0x0, 0x0, 0x0, 0x2f,
    0xe0, 0x0, 0x0, 0x0, 0xb, 0xf8, 0x0, 0x0,
    0x0, 0x2, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0x80, 0x0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x0, 0xb, 0xf8, 0x1, 0x55, 0x55, 0x50, 0xfc,
    0x1, 0xff, 0xff, 0xff, 0x4c, 0x1, 0xff, 0xff,
    0xff, 0xf4, 0x1, 0xff, 0xff, 0xff, 0xfc, 0x1,
    0xff, 0xff, 0xff, 0xfc, 0x0,

    /* U+0036 "6" */
    0x0, 0x7f, 0xff, 0xff, 0xfd, 0x0, 0x7f, 0xff,
    0xff, 0xfd, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x72, 0xff, 0xff, 0xfd, 0x0, 0x7f, 0x15, 0x55,
    0x54, 0x0, 0x3f, 0xd0, 0x0, 0x0, 0x0, 0xf,
    0xf4, 0x0, 0x0, 0x0, 0x3, 0xfd, 0x0, 0x0,
    0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0x3f,
    0xd0, 0x0, 0x0, 0x0, 0xf, 0xf4, 0x0, 0x0,
    0x0, 0x3, 0xfd, 0x0, 0x0, 0x0, 0x0, 0xff,
    0x40, 0x0, 0x0, 0x0, 0x3f, 0xd0, 0x0, 0x0,
    0x0, 0xf, 0xf4, 0x0, 0x0, 0x0, 0x3, 0xf8,
    0x55, 0x55, 0x54, 0x0, 0xe1, 0xff, 0xff, 0xff,
    0xd0, 0x3, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x83, 0xd2, 0xff, 0xff, 0xfe,
    0x1e, 0xff, 0x0, 0x0, 0x0, 0x7f, 0xbf, 0xd0,
    0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb,
    0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff, 0x40,
    0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0, 0x2f,
    0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0,
    0x0, 0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf,
    0xbf, 0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0,
    0x0, 0xb, 0xf9, 0xfc, 0x55, 0x55, 0x50, 0xfc,
    0x1c, 0xbf, 0xff, 0xff, 0x4c, 0x0, 0xbf, 0xff,
    0xff, 0xf4, 0x0, 0x1f, 0xff, 0xff, 0xfc, 0x0,
    0x1, 0xff, 0xff, 0xfc, 0x0,

    /* U+0037 "7" */
    0xbf, 0xff, 0xff, 0xff, 0xf8, 0x2f, 0xff, 0xff,
    0xff, 0xe2, 0xb, 0xff, 0xff, 0xff, 0x8f, 0x2,
    0xff, 0xff, 0xfe, 0x3f, 0x0, 0x55, 0x55, 0x54,
    0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0,
    0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x2, 0xff,
    0x0, 0x0, 0x0, 0x2, 0xff, 0x0, 0x0, 0x0,
    0x2, 0xff, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0,
    0x0, 0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x2,
    0xff, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0x0, 0x0, 0x0, 0x0, 0xb, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x0, 0x0,
    0xff, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0, 0x0,
    0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x2, 0xff,
    0x0, 0x0, 0x0, 0x2, 0xff, 0x0, 0x0, 0x0,
    0x2, 0xff, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0,
    0x0, 0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x2,
    0xff, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0, 0x0,
    0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0x0, 0x0, 0x0,
    0x0, 0x2f, 0x0, 0x0, 0x0, 0x0, 0xb, 0x0,
    0x0, 0x0, 0x0, 0x1,

    /* U+0038 "8" */
    0x0, 0x7f, 0xff, 0xff, 0x0, 0x0, 0x7f, 0xff,
    0xff, 0xf0, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x72, 0xff, 0xff, 0xfd, 0x30, 0x7f, 0x15, 0x55,
    0x54, 0x3f, 0x3f, 0xd0, 0x0, 0x0, 0x2f, 0xef,
    0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0, 0x0,
    0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf, 0xbf,
    0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0,
    0xb, 0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff,
    0x40, 0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0,
    0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xf8,
    0x55, 0x55, 0x54, 0xbe, 0xe1, 0xff, 0xff, 0xff,
    0xd3, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x83, 0xd2, 0xff, 0xff, 0xfe,
    0x1e, 0xff, 0x0, 0x0, 0x0, 0x7f, 0xbf, 0xd0,
    0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb,
    0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff, 0x40,
    0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0, 0x2f,
    0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0,
    0x0, 0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf,
    0xbf, 0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0,
    0x0, 0xb, 0xf9, 0xfc, 0x55, 0x55, 0x50, 0xfc,
    0x1c, 0xbf, 0xff, 0xff, 0x4c, 0x0, 0xbf, 0xff,
    0xff, 0xf4, 0x0, 0x1f, 0xff, 0xff, 0xfc, 0x0,
    0x1, 0xff, 0xff, 0xfc, 0x0,

    /* U+0039 "9" */
    0x0, 0x7f, 0xff, 0xff, 0x0, 0x0, 0x7f, 0xff,
    0xff, 0xf0, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x72, 0xff, 0xff, 0xfd, 0x30, 0x7f, 0x15, 0x55,
    0x54, 0x3f, 0x3f, 0xd0, 0x0, 0x0, 0x2f, 0xef,
    0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfd, 0x0, 0x0,
    0x2, 0xfe, 0xff, 0x40, 0x0, 0x0, 0xbf, 0xbf,
    0xd0, 0x0, 0x0, 0x2f, 0xef, 0xf4, 0x0, 0x0,
    0xb, 0xfb, 0xfd, 0x0, 0x0, 0x2, 0xfe, 0xff,
    0x40, 0x0, 0x0, 0xbf, 0xbf, 0xd0, 0x0, 0x0,
    0x2f, 0xef, 0xf4, 0x0, 0x0, 0xb, 0xfb, 0xfc,
    0x55, 0x55, 0x55, 0xfe, 0xf5, 0xff, 0xff, 0xff,
    0xd7, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x0, 0xbf,
    0xff, 0xff, 0xff, 0x80, 0x2, 0xff, 0xff, 0xfe,
    0xe, 0x0, 0x0, 0x0, 0x0, 0x2f, 0x80, 0x0,
    0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0, 0x0, 0xb,
    0xf8, 0x0, 0x0, 0x0, 0x2, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0x80, 0x0, 0x0, 0x0, 0x2f,
    0xe0, 0x0, 0x0, 0x0, 0xb, 0xf8, 0x0, 0x0,
    0x0, 0x2, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0x80, 0x0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x0, 0xb, 0xf8, 0x0, 0x55, 0x55, 0x50, 0xfc,
    0x0, 0xbf, 0xff, 0xff, 0x4c, 0x0, 0xbf, 0xff,
    0xff, 0xf4, 0x0, 0xbf, 0xff, 0xff, 0xfc, 0x0,
    0x7f, 0xff, 0xff, 0xfc, 0x0,

    /* U+0043 "C" */
    0x0, 0x7f, 0xff, 0xff, 0xfd, 0x1, 0xff, 0xff,
    0xff, 0xf4, 0x2, 0xff, 0xff, 0xff, 0xd0, 0x1c,
    0xbf, 0xff, 0xff, 0x40, 0x7f, 0x15, 0x55, 0x54,
    0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0,
    0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40, 0x0,
    0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff,
    0x40, 0x0, 0x0, 0x0, 0xff, 0x40, 0x0, 0x0,
    0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0,
    0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0,
    0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40, 0x0,
    0x0, 0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff,
    0x40, 0x0, 0x0, 0x0, 0xff, 0x40, 0x0, 0x0,
    0x0, 0xff, 0x40, 0x0, 0x0, 0x0, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x7f, 0x15, 0x55, 0x54, 0x0,
    0x1c, 0xbf, 0xff, 0xff, 0x40, 0x2, 0xff, 0xff,
    0xff, 0xd0, 0x1, 0xff, 0xff, 0xff, 0xf4, 0x0,
    0x7f, 0xff, 0xff, 0xfd,

    /* U+00B0 "°" */
    0x0, 0x0, 0x0, 0x0, 0xb, 0xfe, 0x40, 0x7,
    0xff, 0xfe, 0x0, 0xfd, 0x2, 0xf4, 0x3e, 0x0,
    0x7, 0xc3, 0xc0, 0x0, 0x3d, 0x7c, 0x0, 0x1,
    0xe7, 0x80, 0x0, 0x1f, 0x7c, 0x0, 0x1, 0xe3,
    0xc0, 0x0, 0x3d, 0x2f, 0x0, 0xb, 0xc0, 0xfd,
    0x7, 0xf4, 0x3, 0xff, 0xfd, 0x0, 0x7, 0xfe,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t dgital_number_50_glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 726, .box_w = 44, .box_h = 36, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 103, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 396, .box_w = 5, .box_h = 36, .ofs_x = 10, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 396, .box_w = 20, .box_h = 36, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1198, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1387, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1576, .adv_w = 396, .box_w = 20, .box_h = 36, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1756, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1945, .adv_w = 396, .box_w = 21, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2134, .adv_w = 356, .box_w = 20, .box_h = 36, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2314, .adv_w = 292, .box_w = 14, .box_h = 14, .ofs_x = 2, .ofs_y = 23}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t dgital_number_50_unicode_list_0[] = {
    0x0, 0x9, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x1e, 0x8b
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t dgital_number_50_cmaps[] =
{
    {
        .range_start = 37, .range_length = 140, .glyph_id_start = 1,
        .unicode_list = dgital_number_50_unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 14, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t dgital_number_50_cache;
static const lv_font_fmt_txt_dsc_t dgital_number_50_font_dsc = {
#else
static lv_font_fmt_txt_dsc_t dgital_number_50_font_dsc = {
#endif
    .glyph_bitmap = dgital_number_50_glyph_bitmap,
    .glyph_dsc = dgital_number_50_glyph_dsc,
    .cmaps = dgital_number_50_cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &dgital_number_50_cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t dgital_number_50 = {
#else
static lv_font_t dgital_number_50 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 37,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &dgital_number_50_font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DGITAL_NUMBER_50*/

