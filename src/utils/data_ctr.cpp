/**
 * @file data_ctr.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "data_ctr.h"
#include <Arduino.h>
#include <stdio.h>
#include <Preferences.h>
#include <ArduinoJson.h>


Preferences prefs; //NVS操作对象

/**
 * @brief 
 * 获取NVS数据
 */
bool NVSGet(char *names[], int arr_len, bool (*Callback)(String, bool)){
  Serial.println("开始访问NVS...");
  prefs.begin("userData");
  Serial.print("NVS剩余空间为:");
  Serial.println(prefs.freeEntries());//查询剩余空间

  StaticJsonDocument<200> doc;
  String result = "";

  if(!prefs.isKey(names[0])){
    Serial.printf("无存储信息信息!\n");
    Callback(result, false);
    return false;
  }
  for(int i=0; i<arr_len;i++){
    Serial.println(names[i]);//查询剩余空间
    Serial.println(prefs.getString(names[i]).c_str());
    doc[names[i]] = prefs.getString(names[i]);
  }
  serializeJson(doc, result);
  Serial.println(result);
  
  Callback(result, true);
  //结束NVS访问
  prefs.end();
  return false;
} 


/**
 * @brief 
 * NVS存储数据
 */
void NVSSet(){
  Serial.println("开始存储数据");
  prefs.begin("userData");
  prefs.putString("wifi_ssid", "$_2.4G");
  prefs.putString("wifi_password", "WR-';223sgjm4sd445n/....?=_-096.~6---");
  Serial.println("存储完成");
  prefs.end();
}


/**
 * @brief 
 * 删除NVS
 */
void NVSRemove(){
  Serial.println("开始删除数据");
  prefs.begin("userData");
  prefs.remove("wifi_ssid");
  prefs.remove("wifi_password");
  Serial.println("删除完成");
  prefs.end();
}