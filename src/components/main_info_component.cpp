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
static  lv_obj_t * hum_display; //湿度控件
static  lv_obj_t * air_display; //空气质量控件


String temp = "23";
String hum = "0";
String air = "良";

static long update_info_dealy=0;


/**
 * @brief 
 * 温度显示容器
 * @param parent 
 */
void tempContainer(lv_obj_t * parent){
    //温度显示容器
    temp_container = lv_obj_create(parent);
    lv_obj_set_scrollbar_mode(temp_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(temp_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(temp_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(temp_container, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);


    
    lv_obj_set_size(temp_container,(255/3)-17 ,SCREEN_WIDTH-65);
    lv_obj_set_style_border_width(temp_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(temp_container, 0, LV_STATE_DEFAULT);


    lv_obj_t * vlaue_container = lv_obj_create(temp_container);
    lv_obj_set_flex_grow(vlaue_container, 1);
    lv_obj_set_style_border_width(vlaue_container,0,LV_STATE_DEFAULT);
    lv_obj_set_x(vlaue_container, -10);



    lv_obj_t * sign_display = lv_label_create(vlaue_container);
    lv_label_set_text(sign_display, "℃");
    lv_obj_set_style_text_font(sign_display, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_align(sign_display,LV_ALIGN_BOTTOM_MID,17,-3);

     //温度显示
    temp_display = lv_label_create(vlaue_container);
    lv_label_set_text_fmt(temp_display, "%s", temp);
    lv_obj_set_style_text_font(temp_display, &hmos_sc_28, LV_STATE_DEFAULT);
    lv_obj_align(temp_display, LV_ALIGN_BOTTOM_MID, -6,0);


    
    //温度图标
    lv_obj_t * icon = lv_img_create(temp_container);
    lv_img_set_src(icon, &temperature_icon);

    

    lv_obj_t * tempDisplayTitle = lv_label_create(temp_container);
    lv_label_set_text(tempDisplayTitle, "温度");
    lv_obj_set_style_text_font(tempDisplayTitle, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tempDisplayTitle, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);


}


/**
 * @brief 
 * 湿度显示
 */
void humContainer(lv_obj_t * parent){
     //湿度显示容器
    lv_obj_t * hum_container = lv_obj_create(parent);
    lv_obj_set_scrollbar_mode(hum_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(hum_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(hum_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(hum_container, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);

    
    lv_obj_set_size(hum_container,(255/3)-17 ,SCREEN_WIDTH-65);
    lv_obj_set_style_border_width(hum_container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(hum_container, 0, LV_STATE_DEFAULT);


    lv_obj_t * vlaue_container = lv_obj_create(hum_container);
    lv_obj_set_flex_grow(vlaue_container, 1);
    lv_obj_set_style_border_width(vlaue_container,0,LV_STATE_DEFAULT);
    lv_obj_set_x(vlaue_container, -10);


    lv_obj_t * sign_display = lv_label_create(vlaue_container);
    lv_label_set_text(sign_display, "%");
    lv_obj_set_style_text_font(sign_display, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_align(sign_display,LV_ALIGN_BOTTOM_MID,17,-3);


    //湿度显示
    hum_display = lv_label_create(vlaue_container);
    lv_label_set_text_fmt(hum_display, "%s", hum);
    lv_obj_set_style_text_font(hum_display, &hmos_sc_28, LV_STATE_DEFAULT);
    lv_obj_align(hum_display, LV_ALIGN_BOTTOM_MID, -6,0);



    //湿度图标
    lv_obj_t * icon = lv_img_create(hum_container);
    lv_img_set_src(icon, &humidity_icon);


    lv_obj_t * tempDisplayTitle = lv_label_create(hum_container);
    lv_label_set_text(tempDisplayTitle, "湿度");
    lv_obj_set_style_text_font(tempDisplayTitle, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tempDisplayTitle, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

}

/**
 * @brief 
 * 空气质量显示
 */
void airContainer(lv_obj_t * parent){
     //空气质量显示容器
    lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);

    
    lv_obj_set_size(container,(255/3)-17 ,SCREEN_WIDTH-65);
    lv_obj_set_style_border_width(container, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container, 0, LV_STATE_DEFAULT);


    lv_obj_t * vlaue_container = lv_obj_create(container);
    lv_obj_set_flex_grow(vlaue_container, 1);
    lv_obj_set_style_border_width(vlaue_container,0,LV_STATE_DEFAULT);
    lv_obj_set_x(vlaue_container, -10);


    //空气质量显示
    air_display = lv_label_create(vlaue_container);
    lv_label_set_text_fmt(air_display, "%s", air);
    lv_obj_align(air_display, LV_ALIGN_CENTER, 0,0);
    lv_obj_set_style_text_font(air_display, &hmos_sc_28, LV_STATE_DEFAULT);

    //空气质量图标
    lv_obj_t * icon = lv_img_create(container);
    lv_img_set_src(icon, &air_icon);
    lv_obj_set_height(icon, 35);
    lv_img_set_offset_y(icon, 0);


    lv_obj_t * tempDisplayTitle = lv_label_create(container);
    lv_label_set_text(tempDisplayTitle, "空气");
    lv_obj_set_style_text_font(tempDisplayTitle, &hmos_sc_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tempDisplayTitle, DEFAULT_TITLE_COLOR, LV_STATE_DEFAULT);

}



/**
 * @brief 
 * 主信息组件
 * @param parent 
 */
void mainInfoComponent(lv_obj_t * parent){
    tempContainer(parent);
    humContainer(parent);
    airContainer(parent);
    // humContainer(parent);
}



/**
 * @brief 
 * 更新温度显示
 */
void update_temp(void){
    temp = String(get_temp_data(),0);
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

// /**
//  * @brief 
//  * 更新台灯显示
//  */
// void update_hum(void){
//     hum = String(get_hum_data(),0);
//     // Serial.println(hum);
//     lv_label_set_text_fmt(hum_display, "%s", hum);
// }

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
