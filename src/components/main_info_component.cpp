/**
 * @file main_info_component.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "main_info_component.h"


static lv_obj_t * main_info_container;
static lv_obj_t * temp_container; 
static lv_obj_t * temp_display; //温度控件
static lv_obj_t * hum_display; //湿度控件


String temp = "0.0";
String hum = "0.0";

static long update_info_dealy=0;


/**
 * @brief 
 * 温度显示容器
 * @param parent 
 */
void tempContainer(lv_obj_t * parent){
    //温度显示容器
    temp_container = lv_obj_create(parent);
    lv_obj_set_layout(temp_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(temp_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(temp_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
    
    lv_obj_set_height(temp_container, 50);
    lv_obj_set_y(temp_container, 0);
    lv_obj_set_width(temp_container, (SCREEN_HEIGHT-20));
    lv_obj_set_style_border_width(temp_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(temp_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(temp_container, 0, LV_STATE_DEFAULT);

    lv_obj_t * tempDisplayTitle = lv_label_create(temp_container);
    lv_label_set_text(tempDisplayTitle, "温度");
    // lv_obj_align(tempDisplayTitle, LV_ALIGN_TOP_LEFT, 0,0);
 
    lv_obj_set_style_text_font(tempDisplayTitle, &hmos_sanc_sc_regular_18, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tempDisplayTitle, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);


    //温度显示
    temp_display = lv_label_create(temp_container);
    lv_label_set_text_fmt(temp_display, "%s", temp);
    // lv_obj_align(temp_display, LV_ALIGN_TOP_LEFT, 45, 0);
   
    lv_obj_set_style_text_font(temp_display, &dgital_number_50, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(temp_display, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

    lv_obj_t * tempDisplaySign = lv_label_create(temp_container);
    lv_label_set_text(tempDisplaySign, "°C");
    // lv_obj_align(tempDisplaySign, LV_ALIGN_TOP_LEFT, 130,4);
  
    lv_obj_set_style_text_font(tempDisplaySign, &dgital_number_25, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tempDisplaySign, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

}


/**
 * @brief 
 * 湿度显示
 */
void humContainer(lv_obj_t * parent){

    //湿度显示容器
    lv_obj_t * hum_container = lv_obj_create(parent);
 
    lv_obj_set_y(hum_container, 60);
    lv_obj_set_width(hum_container, (SCREEN_HEIGHT-20));
    lv_obj_set_flex_flow(hum_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(hum_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_style_border_width(hum_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(hum_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(hum_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_height(hum_container, 50);


    lv_obj_t * humDisplayTitle = lv_label_create(hum_container);
    lv_label_set_text(humDisplayTitle, "湿度");

    lv_obj_set_style_text_font(humDisplayTitle, &hmos_sanc_sc_regular_18, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(humDisplayTitle, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

    //湿度显示
    hum_display = lv_label_create(hum_container);
    lv_label_set_text_fmt(hum_display, "%s", hum);

    lv_obj_set_style_text_font(hum_display, &dgital_number_50, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(hum_display, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);
  

    lv_obj_t * humDisplaySign = lv_label_create(hum_container);
    lv_label_set_text(humDisplaySign, "%");
 
    lv_obj_set_style_text_font(humDisplaySign, &dgital_number_25, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(humDisplaySign, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

}


/**
 * @brief 
 * 主信息组件
 * @param parent 
 */
void mainInfoComponent(lv_obj_t * parent){
    tempContainer(parent);
    humContainer(parent);
}



/**
 * @brief 
 * 更新温度显示
 */
void update_temp(void){
    temp = String(get_temp_data(),1);
    // Serial.println(temp);
    lv_label_set_text_fmt(temp_display, "%s", temp);
}

/**
 * @brief 
 * 更新湿度显示
 */
void update_hum(void){
    hum = String(get_hum_data(),0);
    // Serial.println(hum);
    lv_label_set_text_fmt(hum_display, "%s", hum);
}

/**
 * @brief 
 * 更新主页面信息
 */
void update_main_info_data(void){
    unsigned long currentTime = millis();
    if(currentTime - update_info_dealy > 1000){
        update_info_dealy = currentTime;
        update_temp(); //温度
        update_hum(); //湿度
    }
}
