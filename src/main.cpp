/**
 * @file main.cpp
 * @author ofg (1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Arduino.h>
#include <string.h>

#include <HTTPClient.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ArduinoJson.h>
#include "MQ135.h"

/*==========custom include============= */
#include "config.h"
#include "assets/imgs/loading_icon.c"
#include "assets/fonts/font_Hmos_sans_sc.h"
#include "utils/custom_print.h"
#include "utils/custom_wifi.h"
#include "utils/data_ctr.h"
#include "devices/dht11.h"
#include "devices/hcsr505.h"
#include "devices/buzzer.h"
#include "utils/tools.h"
#include "utils/network/custom_socket.h"
#include "devices/lcd.h"
#include "devices/led.h"

/* page include */
#include "page/init_page.h"
#include "page/qrcode_page.h"
#include "page/main_page.h"


bool connected = false;
bool ledStatus = false;
uint32_t delayMS;
// long previousTime=0;
long wifiLoadTime=0;
float temperature = 21.0; 
float humidity = 25.0; 
bool GUIInit = false;
bool initStatus = false;



//初始化LED
void initLED(void){
  pinMode(2, OUTPUT);
}

void led_close(){digitalWrite(2, LOW);}

void led_open(){digitalWrite(2, HIGH);}


//网络请求
void http_get(String url){
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code
        Serial.println("request ok");
        Serial.println(httpCode);
        if(httpCode == HTTP_CODE_OK){
          Serial.println("code ok");
          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }  
      }
  
    else {
      Serial.printf("HTTP  get error: %s\n ", http.errorToString(httpCode).c_str());
    }
  
    http.end(); //Free the resources
}


void taskOne(void *parameter)
{ 
  wifi_init();
  // while(!get_wifi_connect_status()){
  //   delay(50); 
  // }
  // IPAddress ip = WiFi.localIP();
  // Serial.println(ip);
  // lv_label_set_text_fmt(initText, "ip:%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
  // initStatus = true;
  
  // while(true){
  //   if(WiFi.status() == WL_CONNECTED && !GUIInit && initStatus){
  //     Serial.println("Ending task 1");
  //     vTaskDelete(NULL);
  //   }
  // }
  // delay(10000);
  //初始化网络时间
  initNetworkTime();
  //初始化红外传感器
  init_hcsr505(); 
  //初始化蜂鸣器
  init_buzzer();
  //初始化温湿度传感器
  DHT11_init();
   //初始化led
  init_led();
  //初始化socket
  socketClientInit();
  initStatus = true;
  Serial.println("关闭任务1");
  vTaskDelete(NULL);
}


//开始程序入口
void setup() {
  //初始化控制台输出
  print_init(); 
  // touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V7, TOUCH_HVOLT_ATTEN_1V5);
  // init_reset_pin();
  //初始化GUI配置
  init_lcd();

  // pinMode(T0, INPUT_PULLUP);
  //初始化线程
  xTaskCreate(
  taskOne,   /* Task function. */
  "TaskOne", /* String with name of task. */
  10000,     /* Stack size in bytes. */
  NULL,      /* Parameter passed as input of the task */
  1,         /* Priority of the task. */
  NULL); 
  //初始化加载页面
  init_page();
  init_QRcode_page();
  init_main_page();
  //  NVSRemove();
  //初始化led
  // initLED();
  // set_led_value(50);
  
  
  // digitalWrite(33, LOW);
}


//主循环
void loop() {

  lv_timer_handler(); /* let the GUI do its work */


  //重置监听
  reset_pico();

  if(WiFi.status() != WL_CONNECTED && get_nvswifi_state() == NVSGetWifiInfoState::NONE && !GUIInit){
    set_nvswifi_state_standby();
    start_net_config_server();

    load_qr_code_page(); //切换到配网页面
    // start_set_network(); //
  }

  if((WiFi.status() == WL_CONNECTED) && !GUIInit && initStatus){
    load_main_page();
    GUIInit = true;
  }

  if(GUIInit && initStatus){
    set_icon_status(); //更新状态图标
  }

  if((WiFi.status() == WL_CONNECTED) && GUIInit && initStatus){
    // set_led_value(50);
    socket_loop_function();
    update_time(); //更新时间
    update_main_info_data(); //更新温度
    hcsr505_loop();
  }
}

// #include "Freenove_WS2812_Lib_for_ESP32.h"

// #define LEDS_COUNT  5    //彩灯数目
// #define LEDS_PIN	36    //ESP32控制ws2812的引脚
// #define CHANNEL		0    //控制通道，最多8路

// Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);//申请一个彩灯控制对象

// void setup() {
//   strip.begin();      //初始化彩灯控制引脚
// }

// void loop() {
//   for (int j = 0; j < 255; j += 2) {
//     for (int i = 0; i < LEDS_COUNT; i++) {
//       strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));//设置彩灯颜色数据
//     }
//     strip.show();//显示颜色
//     delay(5);
//   }  
// }


// #define LVGL_TICK_PERIOD 60









