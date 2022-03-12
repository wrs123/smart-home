/**
 * @file custom_print.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "custom_print.h"
#include <Arduino.h>



/**
 * @brief 初始化串口
 * 
 */
void print_init(){
  Serial.begin(115200); 
  delay(100);
}


