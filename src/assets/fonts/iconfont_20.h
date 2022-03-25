/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/
#include "lvgl.h"


#ifndef ICONFONT_20
#define ICONFONT_20 1
#endif

#if ICONFONT_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t iconfont_20_glyph_bitmap[] = {
    /* U+E83C "" */
    0x0, 0x1b, 0xfe, 0x40, 0x0, 0x7f, 0xa5, 0xaf,
    0x90, 0x2f, 0x40, 0x0, 0x1f, 0x8b, 0x40, 0x15,
    0x40, 0x1e, 0x0, 0x7f, 0xff, 0xd0, 0x0, 0x2f,
    0x40, 0x1b, 0x80, 0x3, 0x40, 0x0, 0x1c, 0x0,
    0x0, 0x6f, 0x90, 0x0, 0x0, 0x3f, 0xab, 0xc0,
    0x0, 0x1, 0x0, 0x4, 0x0, 0x0, 0x0, 0x50,
    0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0,
    0xf0, 0x0, 0x0,

    /* U+E841 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xd0,
    0x0, 0x0, 0xf9, 0xb4, 0xf, 0x3, 0xc0, 0x2c,
    0x3, 0xc3, 0x0, 0xd, 0x0, 0xf0, 0x0, 0xd,
    0x0, 0x3c, 0x0, 0x1d, 0x3, 0x4f, 0x0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0x0, 0xf1, 0xc0,
    0x74, 0x0, 0x3c, 0x0, 0x70, 0x0, 0xf, 0x0,
    0x70, 0x0, 0xd3, 0xc0, 0x38, 0x3, 0xc0, 0xf0,
    0x1e, 0x6f, 0x0, 0x0, 0x7, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t iconfont_20_glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_w = 18, .box_h = 13, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 59, .adv_w = 320, .box_w = 16, .box_h = 17, .ofs_x = 2, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t iconfont_20_unicode_list_0[] = {
    0x0, 0x5
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t iconfont_20_cmaps[] =
{
    {
        .range_start = 59452, .range_length = 6, .glyph_id_start = 1,
        .unicode_list = iconfont_20_unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t iconfont_20_font_dsc = {
#endif
    .glyph_bitmap = iconfont_20_glyph_bitmap,
    .glyph_dsc = iconfont_20_glyph_dsc,
    .cmaps = iconfont_20_cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t iconfont_20 = {
#else
static lv_font_t iconfont_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &iconfont_20_font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ICONFONT_20*/

