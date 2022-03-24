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
#include "time.h"

 static bool GET_TIME_STATUS = false;

/**
 * @brief 
 * 初始化网络时间
 */
void initNetworkTime(void){
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 8 * 3600;
    const int daylightOffset_sec = 0;
    struct tm timeinfo;

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    while(!getLocalTime(&timeinfo)){
        delay(50);
    }
    Serial.println("获取时间完成");
}   

/**
 * @brief Get the Now Time object
 *  获取当前时间
 * @return String 
 */
String getNowTime(void){  
    String now_time;
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }else{
        now_time = (String(timeinfo.tm_hour)+":"+String(timeinfo.tm_min));
        Serial.println("当前时间:"+now_time); // 格式化输出
    }
    return now_time;
   
}


 char* dtostr(char *str, float d)
    {
        sprintf(str, "%f", d);
        return str;
    }