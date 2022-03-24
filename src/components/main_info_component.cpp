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

static lv_style_t main_info_container_style;
static lv_style_t temp_container_style;


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
    temp_container = lv_obj_create(parent, NULL);
    
    lv_style_init(&temp_container_style);
    // lv_obj_set_height(tempContainer, 50);
    lv_obj_set_y(temp_container, 20);
    lv_obj_set_width(temp_container, (SCREEN_WIDTH-20));
    lv_style_set_border_width(&temp_container_style, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&temp_container_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&temp_container_style, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(temp_container, LV_LABEL_PART_MAIN, &temp_container_style);

    lv_obj_t * tempDisplayTitle = lv_label_create(temp_container, NULL);
    lv_label_set_text(tempDisplayTitle, "温度");
    lv_obj_align(tempDisplayTitle, temp_container, LV_ALIGN_IN_BOTTOM_LEFT, 0,0);
    static lv_style_t tempDisplayTitle_style;
    lv_style_init(&tempDisplayTitle_style);
    lv_style_set_text_font(&tempDisplayTitle_style, LV_STATE_DEFAULT, &hmos_sanc_sc_regular_18);
    lv_style_set_text_color(&tempDisplayTitle_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(tempDisplayTitle, LV_LABEL_PART_MAIN, &tempDisplayTitle_style);

    //温度显示
    temp_display = lv_label_create(temp_container, NULL);
    lv_label_set_text_fmt(temp_display, "%s", temp);
    lv_obj_align(temp_display, temp_container, LV_ALIGN_IN_TOP_LEFT, 45, 0);
    static lv_style_t temp_display_style;
    lv_style_init(&temp_display_style);
    lv_style_set_text_font(&temp_display_style, LV_STATE_DEFAULT, &dgital_number_50);
    lv_style_set_text_color(&temp_display_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(temp_display, LV_LABEL_PART_MAIN, &temp_display_style);

    lv_obj_t * tempDisplaySign = lv_label_create(temp_container, NULL);
    lv_label_set_text(tempDisplaySign, "°C");
    lv_obj_align(tempDisplaySign, temp_container, LV_ALIGN_IN_BOTTOM_LEFT, 130,-4);
    static lv_style_t tempDisplaySign_style;
    lv_style_init(&tempDisplaySign_style);
    lv_style_set_text_font(&tempDisplaySign_style, LV_STATE_DEFAULT, &dgital_number_25);
    lv_style_set_text_color(&tempDisplaySign_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(tempDisplaySign, LV_LABEL_PART_MAIN, &tempDisplaySign_style);
}


/**
 * @brief 
 * 湿度显示
 */
void humContainer(lv_obj_t * parent){
    //湿度显示容器
    lv_obj_t * hum_container = lv_obj_create(parent, NULL);
    static lv_style_t hum_container_tyle;
    lv_style_init(&hum_container_tyle);
    // lv_obj_set_height(humContainer, 50);
    lv_obj_set_y(hum_container, 70);
    lv_obj_set_width(hum_container, (SCREEN_WIDTH-20));
    lv_style_set_border_width(&hum_container_tyle, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&hum_container_tyle, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&hum_container_tyle, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(hum_container, LV_LABEL_PART_MAIN, &hum_container_tyle);

    //湿度显示
    hum_display = lv_label_create(hum_container, NULL);
    lv_label_set_text_fmt(hum_display, "%s", hum);
    lv_obj_align(hum_display, hum_container, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    static lv_style_t hum_display_style;
    lv_style_init(&hum_display_style);
    lv_style_set_text_font(&hum_display_style, LV_STATE_DEFAULT, &dgital_number_50);
    lv_style_set_text_color(&hum_display_style, LV_STATE_DEFAULT, lv_color_hex(0xf8f8f9));
    lv_obj_add_style(hum_display, LV_LABEL_PART_MAIN, &hum_display_style);

    lv_obj_t * humDisplaySign = lv_label_create(hum_container, NULL);
    lv_label_set_text(humDisplaySign, "%");
    lv_obj_align(humDisplaySign, hum_container, LV_ALIGN_IN_BOTTOM_LEFT, 82,-4);
    static lv_style_t humDisplaySign_style;
    lv_style_init(&humDisplaySign_style);
    lv_style_set_text_font(&humDisplaySign_style, LV_STATE_DEFAULT, &dgital_number_25);
    lv_style_set_text_color(&humDisplaySign_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(humDisplaySign, LV_LABEL_PART_MAIN, &humDisplaySign_style);

}


/**
 * @brief 
 * 主信息组件
 * @param parent 
 */
void mainInfoComponent(lv_obj_t * parent){
    //初始化容器
    main_info_container = lv_obj_create(parent, NULL);

    lv_style_init(&main_info_container_style);
    lv_obj_set_height(main_info_container, 150);
    lv_obj_set_width(main_info_container, (SCREEN_WIDTH-20));
    lv_obj_set_pos(main_info_container, 20, 40);
    lv_style_set_border_width(&main_info_container_style, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&main_info_container_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&main_info_container_style, LV_STATE_DEFAULT, 0);
    //  lv_style_set_bg_color(&topLeftContainerStyle, LV_STATE_DEFAULT, lv_color_hex(0x2d8cf0));
    lv_obj_add_style(main_info_container, LV_LABEL_PART_MAIN, &main_info_container_style);

    tempContainer(main_info_container);
    humContainer(main_info_container);
}



/**
 * @brief 
 * 更新温度显示
 */
void update_temp(void){
    temp = String(get_temp_data(),1);
    Serial.println(temp);
    lv_label_set_text_fmt(temp_display, "%s", temp);
}

/**
 * @brief 
 * 更新湿度显示
 */
void update_hum(void){
    hum = String(get_hum_data(),1);
    Serial.println(hum);
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
