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
#include <Arduino.h>
// #include <SPI.h>
#include <TFT_eSPI.h>
#include "../lib/lv_lib_qrcode/lv_qrcode.h"

#include "../assets/imgs/device_icon.c"
#include "../assets/imgs/network_icon.c"



void init_page(void);
void load_qr_code_page();
void show_QR_code();
// void removeLoading(void);
// void show_QR_code(void);
// void tftEndWrite();
// lv_obj_t * getScreen(void);
void start_set_network(void);

#endif