/**
 * @file init_page.h
 * @author ofg (1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INIT_PAGE_H
#define INIT_PAGE_H
#define LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#include "../lib/lv_lib_qrcode/lv_qrcode.h"

#include "WiFi.h"


void gui_config_init(void);
void init_page(void);
void removeLoading(void);
void show_QR_code(void);
void del_loadingContainer(void);
void tftEndWrite();
lv_obj_t * getScreen(void);

#endif