/**
 * @file main_page.c
 * @author ofg (1309870573@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "main_page.h"
#include "../config.h"
#include "init_page.h"
#include "../utils/network/custom_socket.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>


static lv_obj_t * time_label;
lv_obj_t * mainPage;
static lv_obj_t * wifi_icon;
static lv_obj_t * socket_icon;
static long update_time_dealy=0;
static long set_wifi_state_dealy = 0;
lv_obj_t * status_bar;
lv_obj_t * topContainer;



void led_switch_component(lv_obj_t * parent){
    lv_obj_t * led_switch = lv_obj_create(parent);

    lv_obj_set_scrollbar_mode(led_switch, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(led_switch, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(led_switch, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(led_switch, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_size(led_switch, SCREEN_HEIGHT-300, SCREEN_WIDTH-65);
    lv_obj_set_style_bg_color(led_switch,lv_color_make(25,190,107) ,LV_STATE_DEFAULT);
    lv_obj_set_style_radius(led_switch, 10, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(led_switch, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(led_switch,DEFAULT_TITLE_COLOR ,LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(led_switch, 10, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(led_switch, 50, LV_STATE_DEFAULT);
    lv_obj_align(led_switch, LV_ALIGN_TOP_RIGHT,-15,45);
    
    lv_obj_t * icon = lv_img_create(led_switch);
    lv_img_set_src(icon, &led_icon);
    // lv_img_set_zoom(icon, 60);

    lv_obj_t * time_label = lv_label_create(led_switch);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_24, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(time_label, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    lv_label_set_text_fmt(time_label, "%s", "80%");
   

    lv_obj_t * name_label = lv_label_create(led_switch);
    lv_obj_set_style_text_font(name_label, &lv_font_montserrat_20, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(name_label, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    lv_label_set_text(name_label, "LED");
    
    
}



/**
 * @brief 
 * 初始化gui
 */
void init_main_page(void){
  mainPage = lv_obj_create(NULL);
  lv_obj_set_size(mainPage, SCREEN_HEIGHT, SCREEN_WIDTH);   
  lv_obj_set_style_bg_color(mainPage, DEFAULT_BACKGROUND_COLOR, LV_STATE_DEFAULT);


  //初始化状态栏容器
  status_bar = lv_obj_create(mainPage);
  lv_obj_set_y(status_bar, -40);
  lv_obj_set_scrollbar_mode(status_bar, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(status_bar, SCREEN_HEIGHT, 40);
  lv_obj_set_style_border_width(status_bar, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(status_bar, LV_OPA_TRANSP, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(status_bar, 0, LV_STATE_DEFAULT);
  

  //时间显示
  static lv_style_t time_style;
  lv_style_init(&time_style);
  time_label = lv_label_create(status_bar);
  lv_obj_set_style_text_font(time_label, &lv_font_montserrat_20, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(time_label, lv_color_make(0,0,0), LV_STATE_DEFAULT);
  lv_label_set_text_fmt(time_label, "%s", "null");
  lv_obj_align(time_label, LV_ALIGN_LEFT_MID,0,0);


  //socket连接状态
  socket_icon = lv_label_create(status_bar);
  lv_obj_set_style_text_color(socket_icon, lv_color_make(197,200,206), LV_STATE_DEFAULT);
  lv_label_set_text(socket_icon, LV_SYMBOL_UPLOAD);
  lv_obj_align(socket_icon, LV_ALIGN_RIGHT_MID,-35,0);

  //wifi连接状态
  wifi_icon = lv_label_create(status_bar);
  lv_obj_set_style_text_color(wifi_icon, lv_color_make(197,200,206), LV_STATE_DEFAULT);
  lv_label_set_text(wifi_icon, LV_SYMBOL_WIFI);
  lv_obj_align(wifi_icon, LV_ALIGN_RIGHT_MID,-5,0);


 

  //温湿度显示
  topContainer = lv_obj_create(mainPage);

//   lv_obj_style_set_radius(&topBKStyle, LV_STATE_DEFAULT, 0);
//   lv_obj_set_style_border_width(topContainer, 0, LV_STATE_DEFAULT);
//   lv_style_set_bg_color(&topBKStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
//   lv_style_set_bg_opa(&topBKStyle, LV_STATE_DEFAULT, 50);  //lv_color_hex(0x2d8cf0)
//   lv_style_set_shadow_width(&topBKStyle, LV_STATE_DEFAULT, 25);
//   lv_style_set_shadow_color(&topBKStyle, LV_STATE_DEFAULT, lv_color_hex(0x666666));
//   lv_obj_add_style(topContainer, LV_LABEL_PART_MAIN, &topBKStyle);
  // lv_obj_set_y(topContainer, -200);
    lv_obj_set_size(topContainer, 255, SCREEN_WIDTH-65);
    // lv_obj_set_pos(topContainer, -250, 40);
     lv_obj_set_pos(topContainer, 15, -(SCREEN_WIDTH-55));
    lv_obj_set_scrollbar_mode(topContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(topContainer, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(topContainer, 10, LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(topContainer, LV_OPA_80, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(topContainer, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(topContainer,DEFAULT_TITLE_COLOR ,LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(topContainer, 20, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(topContainer, 70, LV_STATE_DEFAULT);
  
  mainInfoComponent(topContainer);

  led_switch_component(mainPage);

  
//   //按钮1图标
//   lv_obj_t * button1Icon = lv_label_create(button1);
//   static lv_style_t button1Icon_style;
// 	lv_style_init(&button1Icon_style);
//   lv_style_set_text_font(&button1Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
//   lv_style_set_text_color(&button1Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//   lv_obj_add_style(button1Icon, LV_LABEL_PART_MAIN, &button1Icon_style);
//   lv_label_set_text(button1Icon, LV_SYMBOL_CHARGE);
//   lv_obj_align(button1Icon, button1, LV_ALIGN_CENTER, 0, 0);

//   //按钮2
//   lv_obj_t * button2 = lv_obj_create(mainPage);
//   static lv_style_t button2Style;
//   lv_style_init(&button2Style);
//   lv_style_set_radius(&button2Style, LV_STATE_DEFAULT, 30);
//   lv_style_set_bg_color(&button2Style, LV_STATE_DEFAULT, lv_color_hex(0x19be6b));
//   lv_style_set_border_width(&button2Style, LV_STATE_DEFAULT, 0);
//   lv_style_set_shadow_width(&button2Style, LV_STATE_DEFAULT, 15);
//   lv_style_set_shadow_color(&button2Style, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
//   lv_obj_add_style(button2, LV_LABEL_PART_MAIN, &button2Style);
//   lv_obj_set_pos(button2, 90, 280+60);
//   lv_obj_set_width(button2, 50);
//   lv_obj_set_height(button2, 50);
//   //按钮2图标
//   lv_obj_t * button2Icon = lv_label_create(button2);
//   static lv_style_t button2Icon_style;
// 	lv_style_init(&button2Icon_style);
//   lv_style_set_text_font(&button2Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
//   lv_style_set_text_color(&button2Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//   lv_obj_add_style(button2Icon, LV_LABEL_PART_MAIN, &button2Icon_style);
//   lv_label_set_text(button2Icon, LV_SYMBOL_BELL);
//   lv_obj_align(button2Icon, button2, LV_ALIGN_CENTER, 0, 0);

//   //按钮3
//   lv_obj_t * button3 = lv_obj_create(mainPage);
//   static lv_style_t button3Style;
//   lv_style_init(&button3Style);
//   lv_style_set_radius(&button3Style, LV_STATE_DEFAULT, 30);
//   lv_style_set_border_width(&button3Style, LV_STATE_DEFAULT, 0);
//   lv_style_set_bg_color(&button3Style, LV_STATE_DEFAULT, lv_color_hex(0x19be6b));
//   lv_style_set_shadow_width(&button3Style, LV_STATE_DEFAULT, 15);
//   lv_style_set_shadow_color(&button3Style, LV_STATE_DEFAULT, lv_color_hex(0x5b5f6a));
//   lv_obj_add_style(button3, LV_LABEL_PART_MAIN, &button3Style);
//   lv_obj_set_pos(button3, 160, 280+60);
//   lv_obj_set_width(button3, 50);
//   lv_obj_set_height(button3, 50);
//   //按钮3图标
//   lv_obj_t * button3Icon = lv_label_create(button3);
//   static lv_style_t button3Icon_style;
// 	lv_style_init(&button3Icon_style);
//   lv_style_set_text_font(&button3Icon_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
//   lv_style_set_text_color(&button3Icon_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//   lv_obj_add_style(button3Icon, LV_LABEL_PART_MAIN, &button3Icon_style);
//   lv_label_set_text(button3Icon, LV_SYMBOL_EYE_OPEN);
//   lv_obj_align(button3Icon, button3, LV_ALIGN_CENTER, 0, 0);


//   lv_anim_t b;                 
//   lv_anim_init(&b);
//   lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t) lv_obj_set_y);
//   lv_anim_set_var(&b, topContainer);
//   lv_anim_set_time(&b, 300);
//   lv_anim_set_delay(&b, 650);
//   lv_anim_path_t path2;
//   lv_anim_path_init(&path2);
//   lv_anim_path_set_cb(&path2, lv_anim_path_ease_out);
//   lv_anim_set_path(&b, &path2);
//   lv_anim_set_values(&b, -200, 0);
//   lv_anim_start(&b); 


//   lv_anim_t b1anim;
//   lv_anim_init(&b1anim);
//   lv_anim_set_exec_cb(&b1anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
//   lv_anim_set_var(&b1anim, button1);
//   lv_anim_set_time(&b1anim, 350);
//   lv_anim_set_delay(&b1anim, 1300);
//   lv_anim_path_t b1path;
//   lv_anim_path_init(&b1path);
//   lv_anim_path_set_cb(&b1path, lv_anim_path_ease_out);
//   lv_anim_set_path(&b1anim, &b1path);
//   lv_anim_set_values(&b1anim, 280+60, 280-65);
//   lv_anim_start(&b1anim); 

//   lv_anim_t b2anim;
//   lv_anim_init(&b2anim);
//   lv_anim_set_exec_cb(&b2anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
//   lv_anim_set_var(&b2anim, button2);
//   lv_anim_set_time(&b2anim, 350);
//   lv_anim_set_delay(&b2anim, 1600);
//   lv_anim_path_t b2path;
//   lv_anim_path_init(&b2path);
//   lv_anim_path_set_cb(&b2path, lv_anim_path_ease_out);
//   lv_anim_set_path(&b2anim, &b2path);
//   lv_anim_set_values(&b2anim, 280+60, 280-65);
//   lv_anim_start(&b2anim); 


//   lv_anim_t b3anim;
//   lv_anim_init(&b3anim);
//   lv_anim_set_exec_cb(&b3anim, (lv_anim_exec_xcb_t) lv_obj_set_y);
//   lv_anim_set_var(&b3anim, button3);
//   lv_anim_set_time(&b3anim, 350);
//   lv_anim_set_delay(&b3anim, 1900);
//   lv_anim_path_t b3path;
//   lv_anim_path_init(&b3path);
//   lv_anim_path_set_cb(&b3path, lv_anim_path_ease_out);
//   lv_anim_set_path(&b3anim, &b3path);
//   lv_anim_set_values(&b3anim, 280+60, 280-65);
//   lv_anim_start(&b3anim); 

}




/**
 * @brief 
 * 更新时间
 */
void update_time(void){
  unsigned long currentTime=millis();
   if(currentTime - update_time_dealy > 2000){
    update_time_dealy = currentTime;
    String time = getNowTime();
    lv_label_set_text_fmt(time_label, "%s", time);
   }
}

/**
 * @brief Set the wifi icon object
 * 设置状态图标
 */
void set_icon_status(void){
  unsigned long currentTime = millis();
  if(currentTime - set_wifi_state_dealy > 500){
    Serial.println("更新图标");
    set_wifi_state_dealy = currentTime;
    //wifi图标
    bool wifi_status = get_wifi_connect_state();
    lv_obj_set_style_text_color(wifi_icon, wifi_status ? DEFAULT_TITLE_COLOR : lv_color_make(197,200,206), LV_STATE_DEFAULT);
    //socket图标
    bool socket_status = get_socket_connect_status();
    Serial.println(socket_status);
    lv_obj_set_style_text_color(socket_icon, socket_status ? DEFAULT_TITLE_COLOR : lv_color_make(197,200,206), LV_STATE_DEFAULT);
  }
}

void status_bar_anim(uint32_t delay){
    lv_anim_t status_bar_animin_in;
    lv_anim_init(&status_bar_animin_in);
    lv_anim_set_exec_cb(&status_bar_animin_in, (lv_anim_exec_xcb_t) lv_obj_set_y);
    lv_anim_set_var(&status_bar_animin_in, status_bar);
    lv_anim_set_time(&status_bar_animin_in, 300);
    lv_anim_set_delay(&status_bar_animin_in, delay);
    lv_anim_set_path_cb(&status_bar_animin_in, lv_anim_path_ease_out);
    lv_anim_set_values(&status_bar_animin_in, -40, 0);
    lv_anim_start(&status_bar_animin_in); 
}

void set_anim_opa(lv_obj_t * var, lv_opa_t value){
    // Serial.println(value);
    lv_obj_set_style_opa(var, value, LV_STATE_DEFAULT);
    // static lv_style_t style;
    // lv_style_init(&style);
    // lv_style_set_opa(&style, value);
    // lv_obj_add_style(var, &style, LV_STATE_DEFAULT);
}

void main_info_anim(uint32_t delay){
    lv_anim_t anim1;
    lv_anim_init(&anim1);
    lv_anim_set_exec_cb(&anim1, (lv_anim_exec_xcb_t) lv_obj_set_y);
    lv_anim_set_var(&anim1, topContainer);
    lv_anim_set_time(&anim1, 300);
    lv_anim_set_delay(&anim1, delay+300);
    lv_anim_set_path_cb(&anim1, lv_anim_path_ease_out);
    // lv_anim_set_values(&anim1, -250, 15); 
    lv_anim_set_values(&anim1, -(SCREEN_WIDTH-55), 45);
    lv_anim_start(&anim1);
    
}


void set_widget_anim(uint32_t delay){
    status_bar_anim(delay);
    main_info_anim(delay);
}


/**
 * @brief 切换到主界面
 * 
 */
void load_main_page(){
    lv_scr_load_anim(mainPage, LV_SCR_LOAD_ANIM_OUT_TOP, 350, 500, true);
    set_widget_anim(1000);
}
