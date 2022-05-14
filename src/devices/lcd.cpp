#include "lcd.h"

TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[SCREEN_WIDTH * 100];


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    // tft.pushImageDMA(area->x1, area->y1, w, h, &color_p->full);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}



void init_lcd(void){
    lv_init();

    tft.begin(); /* TFT init */
    tft.setRotation(3); /* Landscape orientation */
    // tft.initDMA(true);

    lv_disp_draw_buf_init(&disp_buf, buf, NULL, SCREEN_WIDTH * 100);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_HEIGHT;
    disp_drv.ver_res = SCREEN_WIDTH;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &disp_buf;
    // disp_drv.full_refresh = 0;
    // disp_drv.direct_mode = 0;

    lv_disp_drv_register(&disp_drv);
}

