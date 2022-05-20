#include "led.h"

int freq = 1000;    // 频率
int channel = 1;    // 通道
int resolution = 8;   // 分辨率

/**
 * @brief 初始化led
 * 
 */
void init_led(void){
    // pinMode(LED_PIN, OUTPUT);

    ledcSetup(channel, freq, resolution); // 设置通道
    ledcAttachPin(2, channel);  // 将通道与对应的引脚连接
}

void set_led_value(uint32_t value){
    uint32_t duty = 256 * value / 100;
    Serial.println(duty);
    ledcWrite(channel, value);
    // digitalWrite(LED_PIN, HIGH);
}