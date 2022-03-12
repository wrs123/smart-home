/**
 * @file wifi.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <WiFi.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ArduinoJson.h>
#include "custom_wifi.h"
#include "data_ctr.h"
#include "config.h"
#include "../page/init_page.h"


/**
 * @brief 
 * 初始化wifi
 * @param name 
 * @param password 
 */
void wifi_init(void){
  Serial.println("开始连接wifi...");
  char *key[] = {"wifi_ssid", "wifi_password"};
  //获取存储的wifi数据
  NVSGet(key, 2, WiFi_connect);
}

/**
 * @brief 
 * 初始化Ap热点
 */
void Ap_init(void){
  Serial.println("开始启动配网");
  WiFi.softAP(AP_SSID, AP_PASSWORD, 1, 1);
  Serial.println("ap启动完成");
  Serial.print("ap_ip:");
  Serial.println(WiFi.softAPIP());
}



//连接wifi
bool WiFi_connect(String data, bool status){
  if(status){
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, data);
    String ssid = doc["wifi_ssid"]; 
    String password =doc["wifi_password"] ;
    WiFi.begin(ssid.c_str(), password.c_str()); 
    while(WiFi.status() != WL_CONNECTED){
      delay(300);
      Serial.print(".");
    }
    Serial.print("wifi ok");
    return true;
  }
  Ap_init();
  removeLoading();
  show_QR_code();
  // delay(300);
  return true;
}

