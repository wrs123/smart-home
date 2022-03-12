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



int time_h;
int time_m;
lv_obj_t * time_label;
lv_obj_t * icon;
long update_time_dealy=0;



/**
 * @brief 
 * 初始化gui
 */
void main_page(void){
  delay(600);
  del_loadingContainer();
  //初始化屏幕
  lv_obj_t * screen = lv_obj_create(lv_scr_act(), NULL); //创建屏幕
  static lv_style_t screenStyle;
  lv_style_init(&screenStyle);
  lv_obj_set_width(screen, SCREEN_WIDTH);
  lv_obj_set_height(screen, SCREEN_HEIGHT);
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
  lv_obj_set_width(topContainer, SCREEN_WIDTH);
  lv_obj_set_height(topContainer, 200);


  //初始化topLeft容器
  lv_obj_t * topLeftContainer = lv_obj_create(topContainer, NULL);
  static lv_style_t topLeftContainerStyle;
  lv_style_init(&topLeftContainerStyle);
  lv_obj_set_height(topLeftContainer, 150);
  lv_obj_set_width(topLeftContainer, (SCREEN_WIDTH/2)-20);
  lv_obj_set_pos(topLeftContainer, 20, 40);
   lv_style_set_border_width(&topLeftContainerStyle, LV_STATE_DEFAULT, 0);
   lv_style_set_radius(&topLeftContainerStyle, LV_STATE_DEFAULT, 35);
   lv_style_set_bg_color(&topLeftContainerStyle, LV_STATE_DEFAULT, lv_color_hex(0x2d8cf0));
   lv_obj_add_style(topLeftContainer, LV_LABEL_PART_MAIN, &topLeftContainerStyle);

  //初始化状态栏容器
  lv_obj_t * status_bar = lv_canvas_create(screen, NULL);
  lv_obj_set_y(status_bar, -40);
  static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(SCREEN_WIDTH, 80)];
  lv_canvas_set_buffer(status_bar, cbuf, SCREEN_WIDTH, 50, LV_IMG_CF_INDEXED_1BIT);
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
  lv_anim_set_time(&a, 300);
  // lv_anim_set_delay(&a, 600);
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
