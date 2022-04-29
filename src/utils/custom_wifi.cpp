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
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

/*==========custom include============= */
#include "custom_wifi.h"
#include "data_ctr.h"
#include "config.h"
#include "../page/init_page.h"
#include "../page/main_page.h"

AsyncWebServer server(8091);  
bool wifi_connect_status = false;

/**
 * @brief Get the connect status object
 * 获取wifi连接状态
 */
bool get_wifi_connect_state(void){
  wifi_connect_status  = WiFi.status() != WL_CONNECTED ? false : true;
  return wifi_connect_status;
}

/**
 * @brief 
 * 初始化wifi
 */
void wifi_init(void){
  Serial.println("开始连接wifi...");
  char *key[] = {"wifi_ssid", "wifi_password"};
  //获取存储的wifi数据
  NVSGet(key, 2, WiFi_connect);

  while(!wifi_connect_status){
    delay(50); 
  }
}

/**
 * @brief 
 * 初始化Ap热点
 */
void Ap_init(void){
  Serial.println("开始启动配网");
  WiFi.softAP(AP_SSID, AP_PASSWORD, 1, 0);
  Serial.println("ap启动完成");
  Serial.print("ap_ip:");
  Serial.println(WiFi.softAPIP());
}


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void main_callback(){
  removeLoading();
  main_page();
}

/**
 * @brief 
 * 开启http服务，配网
 */
void Http_server(void){
  Serial.println("启动服务器");
  
  
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
    String wifi_ssid="",wifi_password="";
    if (request->hasParam("wifi_ssid", true) && request->hasParam("wifi_password", true)) {
        wifi_ssid = request->getParam("wifi_ssid", true)->value();
        wifi_password = request->getParam("wifi_password", true)->value();
        Serial.println(wifi_ssid);
        Serial.println(wifi_password);
        String wifi_data = "{\"wifi_ssid\":\""+wifi_ssid+"\",\"wifi_password\":\""+wifi_password+"\"}";
        start_set_network();
        WiFi_connect(wifi_data, true);
        if(wifi_connect_status){
          NVSSet(wifi_data, main_callback);
          request->send(200, "multipart/form-data", "0");
          server.end(); //结束服务
          WiFi.disconnect(); //关闭ap热点
          delay(300);
          ESP.restart();
        }
        
    } else {
        wifi_ssid = "No message sent";
        request->send(200, "multipart/form-data", "1");
    }
    
  });
  server.onNotFound(notFound);
  server.begin();
  Serial.println("服务器已启动");
}

/**
 * @brief 
 * 连接wifi 
 * @param data 
 * @param status 
 * @return true 
 * @return false 
 */
bool WiFi_connect(String data, bool status){
  if(status){
    DynamicJsonDocument doc(512);
    deserializeJson(doc, data);
    String ssid = doc["wifi_ssid"]; 
    String password =doc["wifi_password"] ;
    WiFi.begin(ssid.c_str(), password.c_str()); 
    while(WiFi.status() != WL_CONNECTED){
      delay(300);
      Serial.print(".");
    }
    Serial.println("wifi连接完成");
    wifi_connect_status = true;
    return true;
  }
    Ap_init();
    Http_server();
    removeLoading();
    show_QR_code();
  // start_set_network();
  // delay(300);
  return true;
}




