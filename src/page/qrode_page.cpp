#include "qrcode_page.h"

lv_obj_t * QRCodePage;


/**
 * @brief 显示ap二维码
 * 
 */
void init_QRcode_page(void){
  Serial.println("显示二维码");
  // del_loadingContainer();

  QRCodePage = lv_obj_create(NULL);
  lv_obj_set_size(QRCodePage, SCREEN_HEIGHT, SCREEN_WIDTH);   
  lv_obj_set_style_bg_color(QRCodePage, lv_color_make(0,0,0), LV_STATE_DEFAULT);

 
  //二维码显示
  lv_obj_t * codeContainer = lv_obj_create(QRCodePage);
  lv_obj_set_width(codeContainer, 165);
  lv_obj_set_height(codeContainer, 165);
  lv_obj_set_scrollbar_mode(codeContainer, LV_SCROLLBAR_MODE_OFF );
  lv_obj_align(codeContainer, LV_ALIGN_LEFT_MID, 25, 0); 
  lv_obj_set_style_border_width(codeContainer,0 ,LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(codeContainer,  lv_color_make(255,255,255), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(codeContainer, 18, LV_STATE_DEFAULT);

  String ap_bssid = WiFi.softAPmacAddress();
  String qr_data = "{\"ap_ssid\":\""+AP_SSIDD+"\",\"ap_password\":\""+AP_PASSWORDD+"\",\"ap_bssid\":\""+ap_bssid+"\"}";
  lv_obj_t * QR_code = lv_qrcode_create(codeContainer, 140, lv_color_make(0,0,0), lv_color_make(255,255,255));
  lv_qrcode_update(QR_code, qr_data.c_str(), strlen(qr_data.c_str()));
  lv_obj_align(QR_code, LV_ALIGN_CENTER, 0, 0);
   
  //提示信息显示
  lv_obj_t * labels = lv_label_create(QRCodePage);
  lv_label_set_text(labels, "请使用APP扫描");
   static lv_style_t labels_style;
	lv_style_init(&labels_style);
  lv_obj_set_style_text_font(labels, &HarmonyOS_Sans_SC_Regular_24, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(labels, lv_color_make(255,255,255), LV_STATE_DEFAULT);

  lv_label_set_long_mode(labels, LV_LABEL_LONG_WRAP);
  lv_obj_align(labels, LV_ALIGN_RIGHT_MID, -25, 0);
 
}

/**
 * @brief 切换到二维码页面
 * 
 */
void load_qr_code_page(){
  lv_scr_load_anim(QRCodePage, LV_SCR_LOAD_ANIM_MOVE_TOP, 350, 500, true);
}
