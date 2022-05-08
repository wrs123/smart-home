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


static Preferences prefs; //NVS操作对象
static int nvs_remove_status = 0; //0:未开始  1：进行中 2：结束 3：失败

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
    prefs.end();
    return false;
  }
  for(int i=0; i<arr_len;i++){
    Serial.print(String(names[i])+":");//查询剩余空间
    Serial.println(prefs.getString(names[i]).c_str());
    doc[names[i]] = prefs.getString(names[i]);
  }
  serializeJson(doc, result);
  // Serial.println(result);
  
  Callback(result, true);
  //结束NVS访问
  prefs.end();
  return false;
} 


/**
 * @brief 
 * NVS存储数据
 */
void NVSSet(String data, void (*Callback)(void)){
  Serial.println("开始存储数据...");
  Serial.println(data);
  StaticJsonDocument<200> doc; 
  deserializeJson(doc, data);
  Serial.println((const char*)doc["wifi_ssid"]);
  Serial.println((const char*)doc["wifi_password"]);
  Serial.println((const char*)doc["key"]);
  prefs.begin("userData");
  prefs.putString("wifi_ssid", (const char*)doc["wifi_ssid"]);
  prefs.putString("wifi_password", (const char*)doc["wifi_password"]);
  prefs.putString("key", (const char*)doc["key"]);
  Serial.println("存储完成");
  prefs.end();
  Callback();
}


/**
 * @brief 
 * 删除NVS
 */
void NVSRemove(){
  if(nvs_remove_status == 0){
    nvs_remove_status = 1;
    Serial.println("开始删除数据");
    prefs.begin("userData");
    prefs.remove("wifi_ssid");
    prefs.remove("wifi_password");
    Serial.println("删除完成");
    prefs.end();
    nvs_remove_status = 2;
  }
}

/**
 * @brief Get the nvs remove status object
 * 
 * @return true 
 * @return false 
 */
int get_nvs_remove_status(void){
  return nvs_remove_status;
}
