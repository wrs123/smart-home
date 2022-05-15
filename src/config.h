/**
 * @file config.h
 * @author ofg(1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// #include <SPI.h>
#include <TFT_eSPI.h>
// #include <lvgl.h>


#include "./assets/fonts/zcool_kuhei_24.h"
#include "./assets/fonts/HarmonyOS_Sans_SC_Regular_24.h"
// #include "./assets/fonts/dgital_number_32.h"

#include "./assets/fonts/hmos_sanc_sc_regular_number_23.h"
#include "./assets/fonts/hmos_sanc_sc_regular_16.h"
#include "./assets/fonts/icons_23.h"

LV_FONT_DECLARE(zcool_kuhei_24);
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_24);
// LV_FONT_DECLARE(dgital_number_32);
LV_FONT_DECLARE(hmos_sanc_sc_regular_number_23);
// LV_FONT_DECLARE(dgital_number_25);
LV_FONT_DECLARE(hmos_sanc_sc_regular_16);
LV_FONT_DECLARE(icons_23);

/* =============icons define===========*/

#ifndef WIFI_CONNECTED_ICON
    #define WIFI_CONNECTED_ICON "\xEE\xA1\xB7" //wifi连接图标
#endif //WIFI_CONNECTED_ICON

#ifndef WIFI_DISCONNECTED_ICON
    #define WIFI_DISCONNECTED_ICON "\xEE\xA1\xBA" //wifi未连接图标 
#endif //WIFI_CONNECTED_ICON

#ifndef CRICLE_CHECK_FULL_ICON
    #define CRICLE_CHECK_FULL_ICON "\xEE\xA1\x9C" //circle check full
#endif //CRICLE_CHECK_FULL_ICON

#ifndef LOADING_ICON
    #define LOADING_ICON "\xEE\xA1\xA7" //loading_icon
#endif //LOADING_ICON

#ifndef X_CRICLE_ICON
    #define X_CRICLE_ICON "\xEE\xA1\xB8" //x_cricle_icon
#endif //X_CRICLE_ICON

#ifndef CHECK_CRICLE_ICON
    #define CHECK_CRICLE_ICON "\xEE\xA2\x82" //check_cricle_icon
#endif //CHECK_CRICLE_ICON


/*==========const var==========*/

#ifndef AP_SSID
    #define AP_SSID "smart_home_ap"
#endif //AP_SSID

#ifndef AP_PASSWORD
    #define AP_PASSWORD "11111111"
#endif //AP_PASSWORD

static String AP_SSIDD = AP_SSID;
static String AP_PASSWORDD = AP_PASSWORD;

#ifndef WEBSOCKET_SERVER_HOST
    #define WEBSOCKET_SERVER_HOST "192.168.1.103"
#endif //WEBSOCKET_SERVER_HOST

#ifndef WEBSOCKET_SERVER_POST
    #define WEBSOCKET_SERVER_POST 8091
#endif //WEBSOCKET_SERVER_POST

#ifndef WEBSOCKET_SERVER_PATH
    #define WEBSOCKET_SERVER_PATH "/pico"
#endif //WEBSOCKET_SERVER_PATH


#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH TFT_WIDTH
#endif //SCREEN_WIDTH

#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT TFT_HEIGHT
#endif //SCREEN_HEIGHT

#ifndef TOUCH_THRESHOLD
    #define TOUCH_THRESHOLD 30 //电容触摸阈值
#endif //TOUCH_THRESHOLD

#ifndef DEFAULT_BACKGROUND_COLOR
    #define DEFAULT_BACKGROUND_COLOR lv_color_make(238,240,245)
#endif //DEFAULT_BACKGROUND_COLOR  

#ifndef DEFAULT_TITLE_COLOR
    #define DEFAULT_TITLE_COLOR lv_color_make(23,35,61)
#endif //DEFAULT_TITLE_COLOR






/*============pin define============*/
#ifndef DHTTYPE
    #define DHTTYPE DHT11
#endif //DHTTYPE

#ifndef DHT11_PIN
    #define DHT11_PIN 33 //DHT-11数据引脚
#endif //DHT_PIN

#ifndef MQ2_PIN
    #define MQ2_PIN 36 //烟雾传感器引脚
#endif //MQ2_PIN

#ifndef MQ4_PIN
    #define MQ4_PIN 39 //天然气传感器引脚
#endif //MQ4_PIN

#ifndef BUZZER_PIN
    #define BUZZER_PIN 5 //蜂鸣器引脚
#endif //BUZZER_PIN

#ifndef HC_SR505_PIN
    #define HC_SR505_PIN 4 //人体传感器引脚
#endif //HC_SR505_PIN

#ifndef RESET_PIN
    #define RESET_PIN 32 //触控引脚
#endif //RESET_PIN


#endif //CONFIG_H



