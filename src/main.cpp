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
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Preferences.h>
#include "loading_icon.c"
// #include "wifi_icon.c"
#include "font_Hmos_sans_sc.h"
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

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
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
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 45];
int time_h;
int time_m;
lv_obj_t * icon;
lv_obj_t * time_label;
long update_time_dealy=0;
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
bool NVSGet(char *names[], int arr_len, void (*Callback)(String)){
  Serial.println("开始访问NVS...");
  prefs.begin("userData");
  Serial.print("NVS剩余空间为:");
  Serial.println(prefs.freeEntries());//查询剩余空间

  StaticJsonDocument<200> doc;
  String result;

  if(!prefs.isKey(names[0])){
    Serial.printf("无存储信息信息!\n");
    // undo();
    return false;
  }
  for(int i=0; i<arr_len;i++){
    Serial.println(names[i]);//查询剩余空间
    Serial.println(prefs.getString(names[i]).c_str());
    doc[names[i]] = prefs.getString(names[i]);
  }
  serializeJson(doc, result);
  Serial.println(result);
  
  Callback(result);
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

//连接wifi
void WiFi_connect(String data){
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

//lvgl callback
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/**
 * @brief 
 * 初始化gui
 */
void 

gui_init(void){
  //初始化屏幕
  lv_obj_t * screen = lv_obj_create(lv_scr_act(), NULL); //创建屏幕
  static lv_style_t screenStyle;
  lv_style_init(&screenStyle);
  lv_obj_set_width(screen, TFT_WIDTH);
  lv_obj_set_height(screen, TFT_HEIGHT);
  lv_style_set_border_width(&screenStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&screenStyle, LV_STATE_DEFAULT, lv_color_hex(0x808695));
  lv_obj_add_style(screen, LV_LABEL_PART_MAIN, &screenStyle);

  //初始化顶部容器
  lv_obj_t * topContainer = lv_obj_create(screen, NULL);
  static lv_style_t topBKStyle;
  lv_style_init(&topBKStyle);
  lv_style_set_radius(&topBKStyle, LV_STATE_DEFAULT, 35);
  lv_style_set_border_width(&topBKStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&topBKStyle, LV_STATE_DEFAULT, lv_color_hex(0x2d8cf0));
  lv_style_set_shadow_width(&topBKStyle, LV_STATE_DEFAULT, 15);
  lv_style_set_shadow_color(&topBKStyle, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
  lv_obj_add_style(topContainer, LV_LABEL_PART_MAIN, &topBKStyle);
  // lv_obj_set_y(topContainer, -200);
  lv_obj_set_width(topContainer, TFT_WIDTH);
  lv_obj_set_height(topContainer, 200);


  //初始化topLeft容器
  lv_obj_t * topLeftContainer = lv_obj_create(topContainer, NULL);
  static lv_style_t topLeftContainerStyle;
  lv_style_init(&topLeftContainerStyle);
  lv_obj_set_height(topLeftContainer, 150);
  lv_obj_set_width(topLeftContainer, (TFT_WIDTH/2)-20);
  lv_obj_set_pos(topLeftContainer, 20, 40);
   lv_style_set_border_width(&topLeftContainerStyle, LV_STATE_DEFAULT, 0);
   lv_style_set_radius(&topLeftContainerStyle, LV_STATE_DEFAULT, 35);
   lv_style_set_bg_color(&topLeftContainerStyle, LV_STATE_DEFAULT, lv_color_hex(0x2d8cf0));
   lv_obj_add_style(topLeftContainer, LV_LABEL_PART_MAIN, &topLeftContainerStyle);

  //初始化状态栏容器
  lv_obj_t * status_bar = lv_canvas_create(screen, NULL);
  lv_obj_set_y(status_bar, -40);
  static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(TFT_WIDTH, 80)];
  lv_canvas_set_buffer(status_bar, cbuf, TFT_WIDTH, 50, LV_IMG_CF_INDEXED_1BIT);
  lv_canvas_set_palette(status_bar, 1, LV_COLOR_TRANSP);

  //时间显示
  time_h = 00;
  time_m = 00;
  static lv_style_t time_style;
  lv_style_init(&time_style);
  time_label = lv_label_create(status_bar, NULL);
  lv_style_set_text_font(&time_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_obj_add_style(time_label, LV_LABEL_PART_MAIN, &time_style);
  lv_style_set_text_color(&time_style, LV_STATE_DEFAULT, lv_color_hex(0xf8f8f9));
  lv_label_set_text_fmt(time_label, "%d:%d", time_h, time_m);
  lv_obj_align(time_label, status_bar, LV_ALIGN_IN_LEFT_MID,30,0);

  //wifi连接状态
  icon = lv_label_create(status_bar, NULL);
  // LV_IMG_DECLARE(wifi_icon);
  // lv_img_set_src(icon, &wifi_icon);
  // lv_img_set_antialias(icon, true);
  // lv_img_set_zoom(icon, 160);
  static lv_style_t font_style1;
  lv_style_init(&font_style1);
  lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_obj_add_style(icon, LV_LABEL_PART_MAIN, &font_style1);
  lv_style_set_text_color(&font_style1, LV_STATE_DEFAULT, lv_color_hex(0xf8f8f9));
  lv_label_set_text(icon, LV_SYMBOL_WIFI);
  lv_obj_align(icon, status_bar, LV_ALIGN_IN_RIGHT_MID,-30,0);

  //温度显示
  // tempDisplay = lv_label_create(topLeftContainer, NULL);
  // temp = "26.0";
  // lv_label_set_text_fmt(tempDisplay, "%s°C", temp);
  // lv_obj_align(tempDisplay, topLeftContainer, LV_ALIGN_IN_TOP_LEFT, 0, 20);
  // static lv_style_t tempDisplay_style;
	// lv_style_init(&tempDisplay_style);
  // lv_style_set_text_font(&tempDisplay_style, LV_STATE_DEFAULT, &lv_font_montserrat_32);
  // lv_style_set_text_color(&tempDisplay_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  // lv_obj_add_style(tempDisplay, LV_LABEL_PART_MAIN, &tempDisplay_style);
  // //湿度显示
  // humDisplay = lv_label_create(topLeftContainer, NULL);
  // hum = "8.0";
  // lv_label_set_text_fmt(humDisplay, "%s%%", hum);
  // lv_obj_align(humDisplay, topLeftContainer, LV_ALIGN_IN_BOTTOM_LEFT, 0, -50);
  // static lv_style_t humDisplay_style;
	// lv_style_init(&humDisplay_style);
  // lv_style_set_text_font(&humDisplay_style, LV_STATE_DEFAULT, &lv_font_montserrat_32);
  // lv_style_set_text_color(&humDisplay_style, LV_STATE_DEFAULT, lv_color_hex(0xf8f8f9));
  // lv_obj_add_style(humDisplay, LV_LABEL_PART_MAIN, &humDisplay_style);


  //按钮1
  lv_obj_t * button1 = lv_obj_create(screen, NULL);
  static lv_style_t button1Style;
  lv_style_init(&button1Style);
  lv_style_set_radius(&button1Style, LV_STATE_DEFAULT, 30);
  lv_style_set_border_width(&button1Style, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&button1Style, LV_STATE_DEFAULT, lv_color_hex(0x19be6b));
  lv_style_set_shadow_width(&button1Style, LV_STATE_DEFAULT, 15);
  lv_style_set_shadow_color(&button1Style, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
  lv_obj_add_style(button1, LV_LABEL_PART_MAIN, &button1Style);
  lv_obj_set_pos(button1, 20, 280+60);
  lv_obj_set_width(button1, 50);
  lv_obj_set_height(button1, 50);
  //按钮1图标
  lv_obj_t * button1Icon = lv_label_create(button1, NULL);
  static lv_style_t button1Icon_style;
	lv_style_init(&button1Icon_style);
  lv_style_set_text_font(&button1Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_style_set_text_color(&button1Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_add_style(button1Icon, LV_LABEL_PART_MAIN, &button1Icon_style);
  lv_label_set_text(button1Icon, LV_SYMBOL_CHARGE);
  lv_obj_align(button1Icon, button1, LV_ALIGN_CENTER, 0, 0);

  //按钮2
  lv_obj_t * button2 = lv_obj_create(screen, NULL);
  static lv_style_t button2Style;
  lv_style_init(&button2Style);
  lv_style_set_radius(&button2Style, LV_STATE_DEFAULT, 30);
  lv_style_set_bg_color(&button2Style, LV_STATE_DEFAULT, lv_color_hex(0x19be6b));
  lv_style_set_border_width(&button2Style, LV_STATE_DEFAULT, 0);
  lv_style_set_shadow_width(&button2Style, LV_STATE_DEFAULT, 15);
  lv_style_set_shadow_color(&button2Style, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
  lv_obj_add_style(button2, LV_LABEL_PART_MAIN, &button2Style);
  lv_obj_set_pos(button2, 90, 280+60);
  lv_obj_set_width(button2, 50);
  lv_obj_set_height(button2, 50);
  //按钮2图标
  lv_obj_t * button2Icon = lv_label_create(button2, NULL);
  static lv_style_t button2Icon_style;
	lv_style_init(&button2Icon_style);
  lv_style_set_text_font(&button2Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_style_set_text_color(&button2Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_add_style(button2Icon, LV_LABEL_PART_MAIN, &button2Icon_style);
  lv_label_set_text(button2Icon, LV_SYMBOL_BELL);
  lv_obj_align(button2Icon, button2, LV_ALIGN_CENTER, 0, 0);

  //按钮3
  lv_obj_t * button3 = lv_obj_create(screen, NULL);
  static lv_style_t button3Style;
  lv_style_init(&button3Style);
  lv_style_set_radius(&button3Style, LV_STATE_DEFAULT, 30);
  lv_style_set_border_width(&button3Style, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&button3Style, LV_STATE_DEFAULT, lv_color_hex(0x19be6b));
  lv_style_set_shadow_width(&button3Style, LV_STATE_DEFAULT, 15);
  lv_style_set_shadow_color(&button3Style, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
  lv_obj_add_style(button3, LV_LABEL_PART_MAIN, &button3Style);
  lv_obj_set_pos(button3, 160, 280+60);
  lv_obj_set_width(button3, 50);
  lv_obj_set_height(button3, 50);
  //按钮3图标
  lv_obj_t * button3Icon = lv_label_create(button3, NULL);
  static lv_style_t button3Icon_style;
	lv_style_init(&button3Icon_style);
  lv_style_set_text_font(&button3Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_style_set_text_color(&button3Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_add_style(button3Icon, LV_LABEL_PART_MAIN, &button3Icon_style);
  lv_label_set_text(button3Icon, LV_SYMBOL_EYE_OPEN);
  lv_obj_align(button3Icon, button3, LV_ALIGN_CENTER, 0, 0);


  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&a, status_bar);
  lv_anim_set_time(&a, 250);
  lv_anim_set_delay(&a, 350);
  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
  lv_anim_set_path(&a, &path);
  lv_anim_set_values(&a, -40, 0);
  lv_anim_start(&a); 

  lv_anim_t b;                 
  lv_anim_init(&b);
  lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&b, topContainer);
  lv_anim_set_time(&b, 300);
  lv_anim_set_delay(&a, 50);
  lv_anim_path_t path2;
  lv_anim_path_init(&path2);
  lv_anim_path_set_cb(&path2, lv_anim_path_ease_out);
  lv_anim_set_path(&b, &path2);
  lv_anim_set_values(&b, -200, 0);
  lv_anim_start(&b); 


  lv_anim_t b1anim;
  lv_anim_init(&b1anim);
  lv_anim_set_exec_cb(&b1anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&b1anim, button1);
  lv_anim_set_time(&b1anim, 350);
  lv_anim_set_delay(&b1anim, 650);
  lv_anim_path_t b1path;
  lv_anim_path_init(&b1path);
  lv_anim_path_set_cb(&b1path, lv_anim_path_ease_out);
  lv_anim_set_path(&b1anim, &b1path);
  lv_anim_set_values(&b1anim, 280+60, 280-65);
  lv_anim_start(&b1anim); 

  lv_anim_t b2anim;
  lv_anim_init(&b2anim);
  lv_anim_set_exec_cb(&b2anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&b2anim, button2);
  lv_anim_set_time(&b2anim, 350);
  lv_anim_set_delay(&b2anim, 900);
  lv_anim_path_t b2path;
  lv_anim_path_init(&b2path);
  lv_anim_path_set_cb(&b2path, lv_anim_path_ease_out);
  lv_anim_set_path(&b2anim, &b2path);
  lv_anim_set_values(&b2anim, 280+60, 280-65);
  lv_anim_start(&b2anim); 


  lv_anim_t b3anim;
  lv_anim_init(&b3anim);
  lv_anim_set_exec_cb(&b3anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&b3anim, button3);
  lv_anim_set_time(&b3anim, 350);
  lv_anim_set_delay(&b3anim, 1150);
  lv_anim_path_t b3path;
  lv_anim_path_init(&b3path);
  lv_anim_path_set_cb(&b3path, lv_anim_path_ease_out);
  lv_anim_set_path(&b3anim, &b3path);
  lv_anim_set_values(&b3anim, 280+60, 280-65);
  lv_anim_start(&b3anim); 

}
lv_obj_t * initText;
lv_anim_t loading_anim; //加载动画
lv_obj_t * loadingIcon;
lv_obj_t * loadingContainer;

/**
 * @brief 
 * 主页面
 */
void main_page(void){
  //初始化屏幕
  lv_obj_t * screen = lv_obj_create(lv_scr_act(), NULL); //创建屏幕
  static lv_style_t screenStyle;
  lv_style_init(&screenStyle);
  lv_obj_set_width(screen, TFT_WIDTH);
  lv_obj_set_height(screen, TFT_HEIGHT);
  lv_style_set_border_width(&screenStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&screenStyle, LV_STATE_DEFAULT, lv_color_hex(0x808695));
  lv_obj_add_style(screen, LV_LABEL_PART_MAIN, &screenStyle);

  loadingContainer = lv_obj_create(screen, NULL);
  static lv_style_t containerStyle;
  lv_style_init(&containerStyle);
  lv_obj_set_width(loadingContainer, TFT_WIDTH);
  lv_obj_set_height(loadingContainer, TFT_HEIGHT);
  lv_style_set_border_width(&containerStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&containerStyle, LV_STATE_DEFAULT, lv_color_hex(0x808695));
  lv_obj_add_style(loadingContainer, LV_LABEL_PART_MAIN, &containerStyle);

  initText = lv_label_create(loadingContainer, NULL);
  lv_label_set_text(initText, "initializing wifi");
  lv_label_set_long_mode(initText, LV_LABEL_LONG_BREAK);
  lv_obj_set_width(initText, TFT_WIDTH);
  lv_obj_align(initText, loadingContainer, LV_ALIGN_CENTER, 0, 50);
  lv_label_set_align(initText, LV_LABEL_ALIGN_CENTER);
  static lv_style_t tempDisplay_style;
	lv_style_init(&tempDisplay_style);
  lv_style_set_text_font(&tempDisplay_style, LV_STATE_DEFAULT, &lv_font_montserrat_22);
  lv_style_set_text_color(&tempDisplay_style, LV_STATE_DEFAULT, lv_color_hex(0x17233d));
  lv_obj_add_style(initText, LV_LABEL_PART_MAIN, &tempDisplay_style);

  loadingIcon = lv_img_create(loadingContainer, NULL);
  lv_obj_set_width(loadingIcon, 50);
  LV_IMG_DECLARE(loading_icon);
  lv_obj_align(loadingIcon, loadingContainer, LV_ALIGN_CENTER, 0, -20);
  lv_img_set_src(loadingIcon, &loading_icon);
  lv_img_set_antialias(loadingIcon, true);
  // lv_img_set_zoom(loadingIcon, 255);
  // lv_obj_set_style_local_image_recolor(loadingIcon, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);


  lv_anim_init(&loading_anim);
  lv_anim_set_exec_cb(&loading_anim, (lv_anim_exec_xcb_t) lv_img_set_angle);
  lv_anim_set_var(&loading_anim, loadingIcon);
  lv_anim_set_time(&loading_anim, 1900);
  // lv_anim_set_delay(&b1anim, 3000);
  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_linear);
  lv_anim_set_path(&loading_anim, &path);
  lv_anim_set_values(&loading_anim, 0, 3600);
  lv_anim_set_repeat_count(&loading_anim, 0xFFFF);
  lv_anim_start(&loading_anim); 

  // WiFi_connect();
}


/**
 * @brief 
 * GUI配置初始化
 */
void gui_config_init(void){
  //屏幕背光采用PWM调光
  // ledcSetup(10, 5000/*freq*/, 10 /*resolution*/);
  // ledcAttachPin(TFT_BL, 10);
  // analogReadResolution(10); 
  // ledcWrite(10,1024);
  lv_init();

  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif
  
  //屏幕初始化
  tft.begin(); /* TFT init */
  tft.initDMA();
  // tft.fillScreen(TFT_WHITE);
  // tft.setTextColor(TFT_BLACK);
  // tft.loadFont(font_Hmos_sans_sc);
  //  tft.setTextSize(3);
  // tft.drawString("加载中",60,140);
  // tft.unloadFont(); 
  // delay(1000);
  //  tft.setRotation(0);
  //旋转
  // touch.setRotation(3);
  // LV_HOR_RES_MAX
  lv_disp_buf_init(&disp_buf, buf, NULL,  LV_HOR_RES_MAX* 45);
  //显示刷新接口
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = TFT_WIDTH;
  disp_drv.ver_res = TFT_HEIGHT;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}

/**
 * @brief 
 * 更新时间
 */
void update_time(void){
  unsigned long currentTime=millis();
   if(currentTime - update_time_dealy > 1000){
    update_time_dealy=currentTime;
    time_h +=1;
    time_m +=1;
    lv_label_set_text_fmt(time_label, "%d:%d", time_h, time_m);
   }
}


void taskOne(void *parameter)
{ 
  wifi_init();
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  lv_label_set_text_fmt(initText, "ip:%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
  initStatus = true;
  Serial.println("Ending task 1");
  vTaskDelete(NULL);
}
 
void taskTwo(void *parameter)
 
{
 
  for (int i = 0; i < 10; i++)
  {
 
    Serial.println("Hello from task 2");
 
    delay(1000);
  }
  
  Serial.println("Ending task 2");
 
  // vTaskDelete(NULL);
}

void opa_exec_cb(lv_obj_t * obj, lv_opa_t t){
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_opa_scale(&style, LV_STATE_DEFAULT, t);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
  }


void remove_loading_anim_cb(lv_obj_t * obj, lv_opa_t t){
  opa_exec_cb(obj, t);
  if(t == LV_OPA_0){
      // delay(100);
      //初始化GUI
      gui_init();
    }
}  


/**
 * @brief 
 * 移除加载动画
 */
void removeLoading(void){
  lv_anim_del(loadingIcon, (lv_anim_exec_xcb_t)lv_img_set_angle);

  lv_anim_t remove_anim;
  lv_anim_init(&remove_anim);
  lv_anim_set_exec_cb(&remove_anim, (lv_anim_exec_xcb_t)remove_loading_anim_cb);
  lv_anim_set_var(&remove_anim, loadingContainer);
  lv_anim_set_time(&remove_anim, 500);

  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
  lv_anim_set_path(&remove_anim, &path);
  lv_anim_set_values(&remove_anim, LV_OPA_100, LV_OPA_0);
  lv_anim_start(&remove_anim); 
}


//开始程序入口
void setup() {
  //初始化串口
  serial_init(); 
  //初始化GUI配置
  gui_config_init();
  // NVSSet();
  xTaskCreate(
  taskOne,   /* Task function. */
  "TaskOne", /* String with name of task. */
  10000,     /* Stack size in bytes. */
  NULL,      /* Parameter passed as input of the task */
  1,         /* Priority of the task. */
  NULL); 
  //初始化loading
  main_page();
   
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









