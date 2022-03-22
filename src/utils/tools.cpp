/**
 * @file tools.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "tools.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



/**
 * @brief 
 * 获取网络时间
 */
void getNetworkTime(void){

    DynamicJsonDocument doc(1024);
    HttpClient http;
    String resBuff;

    http.begin(TIME_API_URL);
    int httpCode = http.get();

    if(httpCode > 0){
        if(httpCode == HTTP_CODE_OK){
            resBuff = http.getString();
            Serial.println(resBuff);
        }
    }else{

    }
    http.end();
    
}   