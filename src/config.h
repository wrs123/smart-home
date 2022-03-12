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


#ifndef LOADING_ICON
    #define LOADING_ICON 
#endif //loading_icon

#ifndef AP_SSID
    #define AP_SSID "smart_home_ap"
#endif //AP_SSID


#ifndef AP_PASSWORD
    #define AP_PASSWORD ""
#endif //AP_PASSWORD


#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH TFT_WIDTH
#endif //SCREEN_WIDTH

#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT TFT_HEIGHT
#endif //SCREEN_HEIGHT

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
    #define BUZZER_PIN 39 //蜂鸣器引脚
#endif //BUZZER_PIN

#ifndef HC_SR505_PIN
    #define HC_SR505_PIN 2 //人体传感器引脚
#endif //HC_SR505_PIN



#endif //CONFIG_H



