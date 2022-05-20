/**
 * @file main_page.h
 * @author ofg (1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <Arduino.h>
#include "../components/main_info_component.h"
#include "../utils/tools.h"
#include "../utils/custom_wifi.h"
#include "../assets/imgs/led_icon.c"

void init_main_page(void);

void update_time(void);

void update_temp(void);

void set_icon_status(void);

void load_main_page();

void setLedValue(String value);

#endif