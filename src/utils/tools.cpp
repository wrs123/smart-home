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


/**
 * @brief 
 * 获取网络时间=
 */
String getNetworkTime(void){


   
        
        const char *ntpServer = "pool.ntp.org";
        const long gmtOffset_sec = 8 * 3600;
        const int daylightOffset_sec = 0;
        String time = "err";

        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return time;
        }

        time = (String(timeinfo.tm_hour)+":"+String(timeinfo.tm_min));
        // Serial.println(time); // 格式化输出
        return time;
    
}   