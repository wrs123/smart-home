/**
 * @file dht11.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "dht11.h"
#include "../config.h"
#include "DHT.h"
#include <DHT_U.h>
#include <Adafruit_Sensor.h>


static DHT_Unified dht(DHT11_PIN, DHTTYPE);  //DHT11传感器初始化
static sensors_event_t  event;


/**
 * @brief 
 * 初始化dht11
 */
void DHT11_init(void){
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("℃"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("℃"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("℃"));
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    
    Serial.println("初始化dht11完成");
}

/**
 * @brief Get the temp object
 * 获取温度数据
 * @return String 
 */
float get_temp_data(void){
    dht.temperature().getEvent(&event);
    return event.temperature;
}

/**
 * @brief Get the temp object
 * 获取温度数据
 * @return String 
 */
float get_hum_data(void){
    dht.humidity().getEvent(&event);
    return event.relative_humidity;
}