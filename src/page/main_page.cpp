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

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

static lv_obj_t * time_label;
static lv_obj_t * icon;
static long update_time_dealy=0;
static long set_wifi_state_dealy = 0;



/**
 * @brief 
 * 初始化gui
 */
void main_page(void){
  lv_obj_t * screen = getScreen(); //获取屏幕对象
 

  //初始化顶部容器
  lv_obj_t * topContainer = lv_obj_create(screen, NULL);
  static lv_style_t topBKStyle;
  lv_style_init(&topBKStyle);
  lv_style_set_radius(&topBKStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_border_width(&topBKStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&topBKStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_style_set_bg_opa(&topBKStyle, LV_STATE_DEFAULT, 50);  //lv_color_hex(0x2d8cf0)
  lv_style_set_shadow_width(&topBKStyle, LV_STATE_DEFAULT, 25);
  lv_style_set_shadow_color(&topBKStyle, LV_STATE_DEFAULT, lv_color_hex(0x666666));
  lv_obj_add_style(topContainer, LV_LABEL_PART_MAIN, &topBKStyle);
  // lv_obj_set_y(topContainer, -200);
  lv_obj_set_width(topContainer, SCREEN_WIDTH);
  lv_obj_set_height(topContainer, 200);

  mainInfoComponent(topContainer);

  //初始化状态栏容器
  lv_obj_t * status_bar = lv_obj_create(screen, NULL);
  lv_obj_set_y(status_bar, -50);
  static lv_style_t status_bar_style;
  lv_style_init(&status_bar_style);
  lv_obj_set_size(status_bar, SCREEN_WIDTH, 50);
  lv_style_set_border_width(&status_bar_style, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_opa(&status_bar_style, LV_STATE_DEFAULT, LV_OPA_TRANSP); 
  lv_style_set_radius(&status_bar_style, LV_STATE_DEFAULT, 0);
  lv_style_set_shadow_width(&status_bar_style, LV_STATE_DEFAULT, 0);
  lv_obj_add_style(status_bar, LV_LABEL_PART_MAIN, &status_bar_style);
  

  //时间显示
  static lv_style_t time_style;
  lv_style_init(&time_style);
  time_label = lv_label_create(status_bar, NULL);
  lv_style_set_text_font(&time_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
  lv_obj_add_style(time_label, LV_LABEL_PART_MAIN, &time_style);
  lv_style_set_text_color(&time_style, LV_STATE_DEFAULT, lv_color_hex(0xf8f8f9));
  lv_label_set_text_fmt(time_label, "%s", "null");
  lv_obj_align(time_label, status_bar, LV_ALIGN_IN_LEFT_MID,30,0);

  //wifi连接状态
  icon = lv_label_create(status_bar, NULL);
  // LV_IMG_DECLARE(wifi_icon);
  // lv_img_set_src(icon, &wifi_icon);
  // lv_img_set_antialias(icon, true);
  // lv_img_set_zoom(icon, 160);
  static lv_style_t font_style1;
  lv_style_init(&font_style1);
  lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &icons_23);
  lv_obj_add_style(icon, LV_LABEL_PART_MAIN, &font_style1);
  lv_style_set_text_color(&font_style1, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_label_set_text(icon, WIFI_DISCONNECTED_ICON);
  lv_obj_align(icon, status_bar, LV_ALIGN_IN_RIGHT_MID,-30,0);


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
  lv_anim_set_time(&a, 300);
  lv_anim_set_delay(&a, 1000);
  lv_anim_path_t path;
  lv_anim_path_init(&path);
  lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
  lv_anim_set_path(&a, &path);
  lv_anim_set_values(&a, -50, 0);
  lv_anim_start(&a); 

  lv_anim_t b;                 
  lv_anim_init(&b);
  lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t) lv_obj_set_y);
  lv_anim_set_var(&b, topContainer);
  lv_anim_set_time(&b, 300);
  lv_anim_set_delay(&b, 650);
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
  lv_anim_set_delay(&b1anim, 1300);
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
  lv_anim_set_delay(&b2anim, 1600);
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
  lv_anim_set_delay(&b3anim, 1900);
  lv_anim_path_t b3path;
  lv_anim_path_init(&b3path);
  lv_anim_path_set_cb(&b3path, lv_anim_path_ease_out);
  lv_anim_set_path(&b3anim, &b3path);
  lv_anim_set_values(&b3anim, 280+60, 280-65);
  lv_anim_start(&b3anim); 

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
 * 设置wifi状态图标
 */
void set_wifi_icon(void){
  unsigned long currentTime = millis();
  if(currentTime - set_wifi_state_dealy > 300){
    set_wifi_state_dealy = currentTime;
    bool status = get_wifi_connect_state();
    lv_label_set_text(icon, status ? WIFI_CONNECTED_ICON : WIFI_DISCONNECTED_ICON); 
  }
}



