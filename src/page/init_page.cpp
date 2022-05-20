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
// #include "main_page.h"

// #include <lvgl.h>
// #include "../assets/fonts/HarmonyOS_Sans_SC_Regular_24.h"

// LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_24);

lv_obj_t * screen;
lv_obj_t * loadingContainer;
lv_obj_t * initText;
lv_anim_t loading_anim; //加载动画
lv_obj_t * loadingIcon;

// lv_obj_t * getScreen(){
//   return screen;
// }


// void opa_exec_cb(lv_obj_t * obj, lv_opa_t t){
//   static lv_style_t style;
//   lv_style_init(&style);
//   lv_style_set_opa_scale(&style, LV_STATE_DEFAULT, t);
//   lv_obj_add_style(obj, &style, LV_STATE_DEFAULT);
// }


// void remove_loading_anim_cb(lv_obj_t * obj, lv_opa_t t, void (*Callback)(void)){
//   opa_exec_cb(obj, t);
//   if(t == LV_OPA_0){
//     anim_remove_status = true;
//     del_loadingContainer();
//     Serial.println("删除loading");
//   }
// }  


/**
 * @brief 
 * 主页面
 */
void init_page(void){
  //初始化屏幕
  screen = lv_obj_create(lv_scr_act());
  lv_obj_set_size(screen, SCREEN_HEIGHT, SCREEN_WIDTH);   
  lv_obj_set_style_radius(screen, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(screen, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(screen, lv_color_make(255,255,255), LV_STATE_DEFAULT);


  initText = lv_label_create(screen);
  lv_label_set_text(initText, "系统加载中");
  lv_obj_align(initText, LV_ALIGN_CENTER, 0, 60);
  // lv_label_set_align(initText, LV_LABEL_ALIGN_CENTER);
  static lv_style_t tempDisplay_style;
	lv_style_init(&tempDisplay_style);
  lv_obj_set_style_text_font(initText, &hmos_sc_22, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(initText, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);
 

  loadingIcon = lv_img_create(screen);
  lv_obj_set_width(loadingIcon, 50);
  LV_IMG_DECLARE(loading_icon);
  lv_obj_align(loadingIcon, LV_ALIGN_CENTER, 0, -20);
  lv_img_set_src(loadingIcon, &loading_icon);
  lv_img_set_antialias(loadingIcon, true);
  // lv_img_set_zoom(loadingIcon, 255);
  // lv_obj_set_style_local_image_recolor(loadingIcon, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);


  lv_anim_init(&loading_anim);
  lv_anim_set_exec_cb(&loading_anim, (lv_anim_exec_xcb_t) lv_img_set_angle); 
  lv_anim_set_var(&loading_anim, loadingIcon);
  lv_anim_set_time(&loading_anim, 1900);
  lv_anim_set_values(&loading_anim, 0, 3600);
  lv_anim_set_repeat_count(&loading_anim, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&loading_anim); 
}



void start_set_network(void){


  LV_IMG_DECLARE(device_icon);
  LV_IMG_DECLARE(network_icon);

  
   //初始化屏幕
  lv_obj_t * connectContainer = lv_obj_create(NULL);
  lv_obj_set_size(connectContainer, SCREEN_HEIGHT, SCREEN_WIDTH);   
  lv_obj_set_style_radius(connectContainer, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(connectContainer, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(connectContainer, lv_color_make(0,0,0), LV_STATE_DEFAULT);

  //设备图标
  lv_obj_t * deviceIcon = lv_img_create(connectContainer);
  lv_obj_set_width(deviceIcon, 60);
  lv_img_set_src(deviceIcon, &device_icon);
  lv_obj_align(deviceIcon, LV_ALIGN_TOP_LEFT, 30, 80);
  // lv_img_set_antialias(deviceIcon, true);

  //网络图标
  lv_obj_t * networkIcon = lv_img_create(connectContainer);
  lv_obj_set_width(networkIcon, 60);
  lv_img_set_src(networkIcon, &network_icon);
  lv_obj_align(networkIcon, LV_ALIGN_TOP_RIGHT, -30, 80);
  // lv_img_set_antialias(networkIcon, true);

  
}


