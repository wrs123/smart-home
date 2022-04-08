/**
 * @file init_page.c
 * @author ofg (1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "init_page.h"
#include "../config.h"
#include "main_page.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
// #include "../assets/fonts/HarmonyOS_Sans_SC_Regular_24.h"

// LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_24);

TFT_eSPI tft = TFT_eSPI(); //初始化tft对象
lv_obj_t * screen;
static lv_disp_buf_t disp_buf; //初始化屏幕数据缓存
static lv_color_t buf[SCREEN_WIDTH *  120];
// static lv_color_t buf2[SCREEN_WIDTH *  60];
lv_obj_t * loadingContainer;
lv_obj_t * initText;
lv_anim_t loading_anim; //加载动画
lv_obj_t * loadingIcon;
lv_obj_t * QRCodeContainer;
bool anim_remove_status = false;

void tftEndWrite(){
  tft.endWrite();
}

lv_obj_t * getScreen(){
  return screen;
}


void opa_exec_cb(lv_obj_t * obj, lv_opa_t t){
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_opa_scale(&style, LV_STATE_DEFAULT, t);
  lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
}


void remove_loading_anim_cb(lv_obj_t * obj, lv_opa_t t, void (*Callback)(void)){
  opa_exec_cb(obj, t);
  if(t == LV_OPA_0){
    anim_remove_status = true;
    del_loadingContainer();
    Serial.println("删除loading");
  }
}  

/**
 * @brief 
 * lvgl callback
 * @param disp 
 * @param area 
 * @param color_p 
 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  // tft.pushPixelsDMA(&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/**
 * @brief 
 * GUI配置初始化
 */
void gui_config_init(void){
  //屏幕背光采用PWM调光
  ledcSetup(10, 5000,10);
  ledcAttachPin(TFT_BL, 10);
  // analogReadResolution(10); 
  ledcWrite(10,1024);
  

  lv_init();

  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif
  
  //屏幕初始化
  tft.begin(); /* TFT init */
  tft.initDMA();
  lv_disp_buf_init(&disp_buf, buf, NULL,  SCREEN_WIDTH * 120);
  //显示刷新接口
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);
  // ledcSetup(10, 5000,10);
  // ledcAttachPin(TFT_BL, 10);
  // // analogReadResolution(10); 
  // ledcWrite(10,1024);
}

/**
 * @brief 
 * 主页面
 */
void init_page(void){
  //初始化屏幕
  screen = lv_obj_create(lv_scr_act(), NULL);
  static lv_style_t screenStyle;
  lv_style_init(&screenStyle);
  lv_obj_set_width(screen, SCREEN_WIDTH);
  lv_obj_set_height(screen, SCREEN_HEIGHT);
  lv_style_set_border_width(&screenStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&screenStyle, LV_STATE_DEFAULT, DEFAULT_BACKGROUND_COLOR);
  lv_obj_add_style(screen, LV_LABEL_PART_MAIN, &screenStyle);

  loadingContainer = lv_obj_create(screen, NULL);
  static lv_style_t containerStyle;
  lv_style_init(&containerStyle);
  lv_obj_set_width(loadingContainer, TFT_WIDTH);
  lv_obj_set_height(loadingContainer, TFT_HEIGHT);
  lv_style_set_border_width(&containerStyle, LV_STATE_DEFAULT, 0);
  
    lv_style_set_bg_opa(&containerStyle, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  // lv_style_set_bg_color(&containerStyle, LV_STATE_DEFAULT, lv_color_hex(0xa7b6cd));
  lv_obj_add_style(loadingContainer, LV_LABEL_PART_MAIN, &containerStyle);

  initText = lv_label_create(loadingContainer, NULL);
  lv_label_set_text(initText, "系统初始化中");
  lv_label_set_long_mode(initText, LV_LABEL_LONG_BREAK);
  lv_obj_set_width(initText, TFT_WIDTH);
  lv_obj_align(initText, loadingContainer, LV_ALIGN_CENTER, 0, 50);
  lv_label_set_align(initText, LV_LABEL_ALIGN_CENTER);
  static lv_style_t tempDisplay_style;
	lv_style_init(&tempDisplay_style);
  lv_style_set_text_font(&tempDisplay_style, LV_STATE_DEFAULT, &zcool_kuhei_24);
  lv_style_set_text_color(&tempDisplay_style, LV_STATE_DEFAULT, lv_color_hex(0x33414c));
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
  lv_anim_set_time(&remove_anim, 600);
  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
  lv_anim_set_path(&remove_anim, &path);
  lv_anim_set_values(&remove_anim, LV_OPA_100, LV_OPA_0);
  lv_anim_start(&remove_anim); 
}

void del_loadingContainer(void){
  lv_obj_del(loadingContainer);
}

/**
 * @brief 显示ap二维码
 * 
 */
void show_QR_code(void){
  delay(600);
  Serial.println("显示二维码");
  // del_loadingContainer();

  QRCodeContainer = lv_obj_create(screen, NULL);
  static lv_style_t containerStyle;
  lv_style_init(&containerStyle);
  lv_obj_set_width(QRCodeContainer, SCREEN_WIDTH);
  lv_obj_set_height(QRCodeContainer, SCREEN_HEIGHT);
  lv_style_set_border_width(&containerStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_opa_scale(&containerStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_bg_color(&containerStyle, LV_STATE_DEFAULT, DEFAULT_BACKGROUND_COLOR); 
  lv_obj_add_style(QRCodeContainer, LV_LABEL_PART_MAIN, &containerStyle);

  lv_obj_t * codeContainer = lv_obj_create(QRCodeContainer, NULL);
  lv_obj_set_width(codeContainer, 170);
  lv_obj_set_height(codeContainer, 170);
  lv_obj_align(codeContainer, QRCodeContainer, LV_ALIGN_IN_TOP_MID, 0, (SCREEN_WIDTH-180)/2); 
  static lv_style_t codeContainerStyle;
  lv_style_init(&codeContainerStyle); 
  lv_style_set_border_width(&codeContainerStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&codeContainerStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE); 
  lv_style_set_radius(&codeContainerStyle, LV_STATE_DEFAULT, 18);
  lv_obj_add_style(codeContainer, LV_LABEL_PART_MAIN, &codeContainerStyle);

  String ap_bssid = WiFi.softAPmacAddress();
  String qr_data = "{\"ap_ssid\":\""+AP_SSIDD+"\",\"ap_password\":\""+AP_PASSWORDD+"\",\"ap_bssid\":\""+ap_bssid+"\"}";

  lv_obj_t * QR_code = lv_qrcode_create(codeContainer, 150, LV_COLOR_BLACK, LV_COLOR_TRANSP);
  lv_qrcode_update(QR_code, qr_data.c_str(), strlen(qr_data.c_str()));
  lv_obj_align(QR_code, codeContainer, LV_ALIGN_CENTER, 0, 0);
   

  lv_obj_t * labels = lv_label_create(QRCodeContainer, NULL);
  lv_label_set_text(labels, "请使用APP扫描");
   static lv_style_t labels_style;
	lv_style_init(&labels_style);
  lv_style_set_text_font(&labels_style, LV_STATE_DEFAULT, &HarmonyOS_Sans_SC_Regular_24);
  lv_style_set_text_color(&labels_style, LV_STATE_DEFAULT, lv_color_hex(0x0d171e));
  lv_obj_add_style(labels, LV_LABEL_PART_MAIN, &labels_style);

  lv_label_set_long_mode(labels, LV_LABEL_LONG_BREAK);
  lv_obj_set_width(labels, SCREEN_WIDTH);
  lv_obj_align(labels, QRCodeContainer, LV_ALIGN_IN_BOTTOM_MID, 0, -(SCREEN_WIDTH-180)/2);
  lv_label_set_align(labels, LV_LABEL_ALIGN_CENTER);

  lv_anim_t anim;
  lv_anim_init(&anim);
  lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)opa_exec_cb);
  lv_anim_set_var(&anim, QRCodeContainer);
  lv_anim_set_time(&anim, 400);

  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_linear);
  lv_anim_set_path(&anim, &path);
  lv_anim_set_values(&anim, LV_OPA_0, LV_OPA_100);
  lv_anim_start(&anim); 

  // lv_obj_del(loadingContainer);
}


