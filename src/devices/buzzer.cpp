/**
 * @file trigger.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "buzzer.h"
#include "../config.h"
#include <Arduino.h>

long buzzer_previousTime = 0;


/**
 * @brief 
 * 初始化蜂鸣器
 */
void init_buzzer(){
    pinMode(BUZZER_PIN, OUTPUT);
}

/**
 * @brief 
 * 启动蜂鸣器
 */
void start(){
    unsigned long currentTime = millis();
    if(currentTime - buzzer_previousTime > BUZZER_DELAY){
        buzzer_previousTime = currentTime;
        digitalWrite(BUZZER_PIN, HIGH);
    }
}

/**
 * @brief 
 * 关闭蜂鸣器
 */
void over(){
    unsigned long currentTime = millis();
    if(currentTime - buzzer_previousTime > BUZZER_DELAY){
        buzzer_previousTime = currentTime;
        digitalWrite(BUZZER_PIN, LOW);
    }
}


/**
 * @brief 
 * 间断蜜蜂鸣
 */
void open_buzzer(bool status){
    if(status){
        start();
        over();
    }else{
        close_buzzer();
    }
    
    
}

/**
 * @brief 
 * 关闭蜂鸣
 */
void close_buzzer(){
    digitalWrite(BUZZER_PIN, LOW);
}