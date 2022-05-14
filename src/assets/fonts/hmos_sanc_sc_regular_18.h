/*******************************************************************************
 * Size: 18 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/
#include "lvgl.h"

#ifndef HMOS_SANC_SC_REGULAR_18
#define HMOS_SANC_SC_REGULAR_18 1
#endif

#if HMOS_SANC_SC_REGULAR_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t hmos_sanc_sc_regular_18_glyph_bitmap[] = {
    /* U+5EA6 "度" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x40,
    0x0, 0x1, 0x55, 0x7d, 0x55, 0x40, 0xbf, 0xff,
    0xff, 0xfc, 0xb, 0x7, 0x0, 0x70, 0x0, 0xb5,
    0x75, 0x5b, 0x54, 0xb, 0xff, 0xff, 0xff, 0xc0,
    0xb0, 0x70, 0x7, 0x0, 0xb, 0x7, 0x55, 0xb0,
    0x0, 0xb0, 0x3f, 0xff, 0x0, 0xb, 0x0, 0x0,
    0x0, 0x0, 0xb3, 0xff, 0xff, 0xc0, 0xe, 0xb,
    0x0, 0x78, 0x0, 0xd0, 0x2d, 0x2e, 0x0, 0x1c,
    0x0, 0xbf, 0x40, 0x3, 0xc1, 0xbf, 0xbe, 0x50,
    0x36, 0xfd, 0x0, 0x6f, 0xc0, 0x0, 0x0, 0x0,
    0x0,

    /* U+6E29 "温" */
    0x4, 0x1, 0x55, 0x54, 0x1, 0xe0, 0xbf, 0xff,
    0xc0, 0x7, 0xca, 0x0, 0xc, 0x0, 0x4, 0xbf,
    0xff, 0xc0, 0x20, 0xa, 0x55, 0x5c, 0x7, 0xc0,
    0xa0, 0x0, 0xc0, 0xf, 0xb, 0xff, 0xfc, 0x0,
    0x20, 0x15, 0x55, 0x40, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x21, 0xff, 0xff, 0xe0, 0x7, 0x1c, 0x72,
    0xca, 0x0, 0xa1, 0xc7, 0x1c, 0xa0, 0xd, 0x1c,
    0x71, 0xca, 0x1, 0xc1, 0xc7, 0x1c, 0xa0, 0x2c,
    0x1d, 0x76, 0xdb, 0x43, 0x8f, 0xff, 0xff, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+6E7F "湿" */
    0x8, 0x1, 0x55, 0x55, 0x0, 0xf4, 0xbf, 0xff,
    0xf0, 0x2, 0xda, 0x0, 0x7, 0x0, 0x8, 0xb5,
    0x55, 0xb0, 0x0, 0xb, 0xff, 0xff, 0x3, 0x80,
    0xa0, 0x0, 0x70, 0xf, 0x4b, 0xff, 0xff, 0x0,
    0x24, 0x17, 0x9e, 0x50, 0x0, 0x0, 0x34, 0xd0,
    0x0, 0x25, 0xc3, 0x4d, 0x28, 0x3, 0x4e, 0x34,
    0xd3, 0x0, 0x70, 0x73, 0x4d, 0xb0, 0xb, 0x3,
    0x74, 0xdd, 0x0, 0xe0, 0x3, 0x4d, 0x0, 0x1d,
    0x15, 0x75, 0xd5, 0x42, 0xc3, 0xff, 0xff, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t hmos_sanc_sc_regular_18_glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 81, .adv_w = 288, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 288, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t hmos_sanc_sc_regular_18_unicode_list_0[] = {
    0x0, 0xf83, 0xfd9
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t hmos_sanc_sc_regular_18_cmaps[] =
{
    {
        .range_start = 24230, .range_length = 4058, .glyph_id_start = 1,
        .unicode_list = hmos_sanc_sc_regular_18_unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t hmos_sanc_sc_regular_18_cache;
static const lv_font_fmt_txt_dsc_t hmos_sanc_sc_regular_18_font_dsc = {
#else
static lv_font_fmt_txt_dsc_t hmos_sanc_sc_regular_18_font_dsc = {
#endif
    .glyph_bitmap = hmos_sanc_sc_regular_18_glyph_bitmap,
    .glyph_dsc = hmos_sanc_sc_regular_18_glyph_dsc,
    .cmaps = hmos_sanc_sc_regular_18_cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &hmos_sanc_sc_regular_18_cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t hmos_sanc_sc_regular_18 = {
#else
static lv_font_t hmos_sanc_sc_regular_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &hmos_sanc_sc_regular_18_font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HMOS_SANC_SC_REGULAR_18*/

