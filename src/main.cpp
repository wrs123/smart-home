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
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoWebsockets.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <DHT_U.h>
#include "MQ135.h"
#include "page/init_page.h"
#include "page/main_page.h"
#include <Preferences.h>
#include "config.h"
#include "assets/imgs/loading_icon.c"
#include "assets/imgs/ap_QR_code.c"
#include "assets/fonts/font_Hmos_sans_sc.h"
#define DHTPIN 13
#define DHTTYPE DHT11
#define PIN_MQ135 A0

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char * file, uint32_t line, const char * dsc)
{

  Serial.printf("%s@%d->%s\r\n", file, line, dsc);
  delay(100);
}
#endif


MQ135 mq135_sensor = MQ135(PIN_MQ135);
String path = "/pico";
const uint16_t websockets_server_port = 8091;
const char* websockets_server_host = "192.168.1.101"; 
bool connect_status = false;
using namespace websockets;
WebsocketsClient client;//Enter server adress
bool connected = false;
bool ledStatus = false;
DHT_Unified dht(DHTPIN, DHTTYPE);  //DHT11传感器初始化
uint32_t delayMS;
long previousTime=0;
long wifiLoadTime=0;
float temperature = 21.0; 
float humidity = 25.0; 
String temp = "0.0";
String hum = "8.0";
lv_obj_t * tempDisplay; //温度控件
lv_obj_t * humDisplay; //湿度控件
bool GUIInit = false;
bool initStatus = false;
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

void dosth(void){
  Serial.println("动画完成");
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
  Serial.println("开始启动配网");
  WiFi.softAP(AP_SSID, AP_PASSWORD, 1, 1);
  Serial.println("ap启动完成");
  Serial.print("ap_ip:");
  Serial.println(WiFi.softAPIP());
  removeLoading();
  show_QR_code();
  // delay(300);
}



/**
 * @brief 
 * 初始化wifi
 * @param name 
 * @param password 
 */
void wifi_init(){
  Serial.println("connecting...");
  char *key[] = {"wifi_ssid", "wifi_password"};
  //获取存储的wifi数据
  NVSGet(key, 2, WiFi_connect);
}

void WIFI_set(void){

}

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

//socket客户端初始化
void socketClientInit(){
  if(WiFi.status() == WL_CONNECTED){
    connected = client.connect(websockets_server_host, websockets_server_port, path);
    if(connected) {
      connect_status  = true;
        Serial.println("Connected!");
    } else {
      connect_status  = false;
        Serial.println("Not Connected!");
    }
  }
}

//socket连接状态判断
void socket_status_check(){
  client.onEvent([](WebsocketsClient& client, WebsocketsEvent event, String payload){
      switch (event)
      {
      case WebsocketsEvent::ConnectionClosed:  //连接被关闭
        Serial.print("connect close");
        connect_status  = false;
        /* code */
        break; 
      case WebsocketsEvent::ConnectionOpened:  //连接成功
        Serial.print("connect open");
        connect_status  = true;
        break;
      default :
        break;
      }
    });
}

//初始化dht11
void DHT11_init(){
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
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

//随机温度
int radomTemp(void){
   int a;
    srand((unsigned)time(NULL));
    a = rand() % 10+15;
    return a;
}

//初始化串口
void serial_init(){
  Serial.begin(115200); 
  delay(100);
}


/**
 * @brief 
 *  socket数据接收
 */
void getMessage(void){
  if(client.available()) {
    client.onMessage([&](WebsocketsMessage message){
      DynamicJsonDocument doc(1024);
      String data = message.data();
      deserializeJson(doc, data);
      String type = doc["type"];
      String message_type = doc["data"]["type"];

      // switch (type)
      // {
      // case "normal":
      //   /* code */
      //   break;
      // case "ctr":
      //   /* code */
      //   break;
      // default:
      //   break;
      // }
      bool led_power = doc["data"]["power"];
      
      if(!ledStatus){
        led_open();
      }else{
        led_close();
      }
      ledStatus = led_power;
      Serial.print("Got Message: ");
      Serial.print(data);
  });
    client.poll();
  }
}

//socket 数据发送
void sendTHData(void){  
  unsigned long currentTime=millis();
  if(currentTime - previousTime > 2000){
    previousTime=currentTime;
    String param = "{'from': '/pico', 'to': '/app', 'type':'normal', data: {}";
    String ouput_param;
    DynamicJsonDocument dataDoc(1024);
    deserializeJson(dataDoc, param);
    JsonObject obj = dataDoc.as<JsonObject>();

    sensors_event_t event;
    dht.temperature().getEvent(&event);

    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      obj[String("data")][String("temp")] = event.temperature;
      // Serial.print(F("Temperature: "));
      // Serial.print(event.temperature);
      // Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      obj[String("data")][String("hum")] = event.relative_humidity;
      // Serial.print(F("Humidity: "));
      // Serial.print(event.relative_humidity);
      // Serial.println(F("%"));
    }
    serializeJson(dataDoc, ouput_param);

    client.send(ouput_param);
    float rzero = mq135_sensor.getRZero();
    float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
    float resistance = mq135_sensor.getResistance();
    float ppm = mq135_sensor.getPPM();
    float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

    Serial.print("MQ135 RZero: ");
    Serial.println(rzero);
    Serial.print("\t Corrected RZero: ");
    Serial.println(correctedRZero);
    Serial.print("\t Resistance: ");
    Serial.println(resistance);
    Serial.print("\t PPM: ");
    Serial.println(ppm);
    Serial.print("\t Corrected PPM: ");
    Serial.print(correctedPPM);
    Serial.println("ppm");
    }
}


void taskOne(void *parameter)
{ 
  wifi_init();
  // IPAddress ip = WiFi.localIP();
  // Serial.println(ip);
  // lv_label_set_text_fmt(initText, "ip:%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
  // initStatus = true;
  Serial.println("Ending task 1");
  vTaskDelete(NULL);
}




//开始程序入口
void setup() {
  //初始化串口
  serial_init(); 
  //初始化GUI配置
  gui_config_init();

  xTaskCreate(
  taskOne,   /* Task function. */
  "TaskOne", /* String with name of task. */
  10000,     /* Stack size in bytes. */
  NULL,      /* Parameter passed as input of the task */
  1,         /* Priority of the task. */
  NULL); 
  //初始化页面
  init_page();
   
  // //初始化socket
  // socketClientInit();
  //初始化led
  // initLED();
  // //初始化温湿度传感器
  // DHT11_init();
  // pinMode(33, OUTPUT);
  // digitalWrite(33, LOW);
}


//主循环
void loop() {

  // digitalWrite(33, HIGH);
  // delay(500);
  // digitalWrite(33, LOW);
  // delay(500);
  //当前连接状态判断 
  // socket_status_check();
  // if(WiFi.status() == WL_CONNECTED && GUIInit && initStatus){
  lv_task_handler(); /* let the GUI do its work */

  //   // lv_label_set_text_fmt(tempDisplay, "%s°C", temp);
  // }
     
    // //更新时间
     //update_time();

    // if(connect_status){
    //   //发送数据
    //   sendTHData();
    //   //数据接收
    //   getMessage();
    // }else{;.;l/;'?

    //   //重连
    //   socketClientInit();
    //   delay(1500);
    // }
    if(WiFi.status() == WL_CONNECTED && !GUIInit && initStatus){
      delay(300);
      removeLoading();
      main_page();
       Serial.println("IP address:");
        Serial.print(WiFi.localIP());
        GUIInit = true;
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









