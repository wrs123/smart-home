/**
 * @file hcsr505.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "hcsr505.h"
#include "../config.h"
#include <Arduino.h>


long previousTime = 0;
bool state = false;



/**
 * @brief 
 * 初始化红外人体传感器
 */
void init_hcsr505(void){
    pinMode(HC_SR505_PIN, INPUT);
}

/**
 * @brief 
 * 获取检测状态
 */
void hcsr505_loop(void){
    unsigned long currentTime = millis();
    if(currentTime - previousTime > 1000){
        previousTime = currentTime;

        if(digitalRead(HC_SR505_PIN) == HIGH) {
            // Serial.println("检测到人体");
            state = true;
        } else {
            // Serial.println("未检测到人体");
            state = false;
        }
    }
}

bool hcsr505_get_value(void){
    return state;
}

