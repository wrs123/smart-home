/**
 * @file main_info_component.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MAIN_INFO_COMPONENT_H
#define MAIN_INFO_COMPONENT_H

#include <lvgl.h>
#include "../config.h"
#include "../devices/dht11.h"
#include "../utils/tools.h"
#include "../assets/imgs/temperature_icon.c"  
#include "../assets/imgs/humidity_icon.c"
#include "../assets/imgs/air_icon.c"


void mainInfoComponent(lv_obj_t * parent);

void update_main_info_data(void);

#endif