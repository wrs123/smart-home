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
lv_obj_t * led_switch;
lv_obj_t * led_switch_value_bg;
lv_obj_t * led_switch_bg;
lv_obj_t * led_label;
String led_value = "关";
lv_anim_t switch_anim;
int16_t led_value_opa = 0;



void led_switch_component(lv_obj_t * parent){
    led_switch_bg = lv_obj_create(parent);
    // lv_obj_remove_style_all(led_switch_bg);
    lv_obj_set_scrollbar_mode(led_switch_bg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_size(led_switch_bg, SCREEN_HEIGHT-300, SCREEN_WIDTH-65);
    lv_obj_set_style_bg_color(led_switch_bg,lv_color_make(134,134,134) ,LV_STATE_DEFAULT);
    lv_obj_set_style_radius(led_switch_bg, 10, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(led_switch_bg, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(led_switch_bg,DEFAULT_TITLE_COLOR ,LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(led_switch_bg, 8, LV_STATE_DEFAULT); 
    lv_obj_align(led_switch_bg, LV_ALIGN_TOP_LEFT,285,45);


    // led_switch_value_bg = lv_obj_create(led_switch_bg);
    // lv_obj_set_scrollbar_mode(led_switch_value_bg, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_size(led_switch_value_bg, SCREEN_HEIGHT-300, led_value_height);
    // lv_obj_set_style_bg_color(led_switch_value_bg,lv_color_make(235,168,17) ,LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(led_switch_value_bg, 10, LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(led_switch_value_bg, 0, LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(led_switch_value_bg, 0, LV_STATE_DEFAULT); 
    // lv_obj_align(led_switch_value_bg, LV_ALIGN_BOTTOM_MID,0,16);


    led_switch = lv_obj_create(led_switch_bg);
    lv_obj_set_scrollbar_mode(led_switch, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(led_switch, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(led_switch, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(led_switch, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(led_switch, SCREEN_HEIGHT-300, SCREEN_WIDTH-65);
    lv_obj_set_style_bg_opa(led_switch,led_value_opa,LV_STATE_DEFAULT);
    lv_obj_set_style_radius(led_switch, 10, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(led_switch, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(led_switch, lv_color_make(235,168,17),LV_STATE_DEFAULT);
     lv_obj_set_style_shadow_width(led_switch, 0, LV_STATE_DEFAULT); 
    lv_obj_set_align(led_switch, LV_ALIGN_CENTER);

    // lv_obj_align(led_switch, LV_ALIGN_TOP_LEFT,285,45);

    
    
    lv_obj_t * icon = lv_img_create(led_switch);
    lv_img_set_src(icon, &led_icon);
    // lv_img_set_zoom(icon, 60);

    lv_obj_t * percent_container = lv_obj_create(led_switch);
    lv_obj_set_height(percent_container, 50);
    lv_obj_set_style_radius(percent_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(percent_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(percent_container,0 ,LV_STATE_DEFAULT);
    // lv_obj_set_layout(percent_container, LV_LAYOUT_FLEX);
    // lv_obj_set_flex_flow(percent_container, LV_FLEX_FLOW_ROW);
    // lv_obj_set_flex_align(percent_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);


    led_label = lv_label_create(percent_container);
    lv_obj_set_style_text_font(led_label, &hmos_sc_28, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(led_label, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    lv_label_set_text_fmt(led_label, "%s", led_value);
    lv_obj_align(led_label, LV_ALIGN_BOTTOM_MID, 0,0);

    
    // lv_obj_t * time_label2 = lv_label_create(percent_container);
    // lv_obj_set_style_text_font(time_label2, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(time_label2, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    // lv_label_set_text(time_label2,"%");
    // lv_obj_align(time_label2, LV_ALIGN_BOTTOM_MID, 24, -2);
    

    lv_obj_t * name_label = lv_label_create(led_switch);
    lv_obj_set_style_text_font(name_label, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(name_label, lv_color_make(255,255,255), LV_STATE_DEFAULT);

    
    lv_label_set_text(name_label, "台灯");   
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
  lv_obj_set_style_text_font(time_label, &hmos_sc_16, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(time_label, lv_color_make(0,0,0), LV_STATE_DEFAULT);
  lv_label_set_text_fmt(time_label, "%s", "00:00");
  // lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    // lv_style_set_text_color(&style_shadow, lv_color_black());
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


  led_switch_component(mainPage);

  //温湿度显示
  topContainer = lv_obj_create(mainPage);
  lv_obj_remove_style_all(topContainer);

    lv_obj_set_size(topContainer, 255, SCREEN_WIDTH-65);
    lv_obj_set_pos(topContainer, -260, 45);
    lv_obj_set_scrollbar_mode(topContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(topContainer, 10, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(topContainer, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(topContainer, lv_color_make(255,255,255), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(topContainer,DEFAULT_TITLE_COLOR ,LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(topContainer, 8, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(topContainer, 30, LV_STATE_DEFAULT);

    lv_obj_set_layout(topContainer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(topContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(topContainer, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
  

    mainInfoComponent(topContainer);
}




/**
 * @brief 
 * 更新时间
 */
void update_time(void){
  unsigned long currentTime = millis();
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
    // Serial.println("更新图标");
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
    lv_anim_set_time(&status_bar_animin_in, 350);
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
    lv_anim_set_exec_cb(&anim1, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&anim1, topContainer);
    lv_anim_set_time(&anim1, 300);
    lv_anim_set_delay(&anim1, delay+350);
    lv_anim_set_path_cb(&anim1, lv_anim_path_ease_in_out);
    // lv_anim_set_values(&anim1, -250, 15); 
    lv_anim_set_values(&anim1, -260, 15);
    lv_anim_start(&anim1);  
}

void led_switch_anim(uint32_t delay){
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_var(&anim, led_switch_bg);
    lv_anim_set_time(&anim, 300);
    lv_anim_set_delay(&anim, delay+400);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
    lv_anim_set_values(&anim, -285, 285);
    lv_anim_start(&anim);  
}


void set_widget_anim(uint32_t delay){
    status_bar_anim(delay);
    led_switch_anim(delay);
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

void set_bg_opa_anim(lv_obj_t * obj, lv_opa_t value){
  lv_obj_set_style_bg_opa(obj, value, LV_STATE_DEFAULT);
}

/**
 * @brief 设置台灯亮度值
 * 
 * @param value 
 */
void setLedValue(String value){
  value = value == "0" ? "关" : value;
  led_value = value;
  
  lv_anim_t anim;
  lv_anim_init(&anim);
  lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t) set_bg_opa_anim);
  lv_anim_set_var(&anim, led_switch);
  lv_anim_set_time(&anim, 250);
  // lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
  // lv_anim_set_values(led_switch,(SCREEN_WIDTH-65)*value.toInt()/100,LV_STATE_DEFAULT);
  Serial.println(value.toInt());
  lv_anim_set_values(&anim, led_value_opa, value.toInt()*2.55);
  lv_anim_start(&anim);  

  led_value_opa = value.toInt()*2.55;
  lv_label_set_text_fmt(led_label, "%s", led_value);
}
