/**
 * @file wifi.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CUSTOM_WIFI_H
#define CUSTOM_WIFI_H


bool WiFi_connect(String data, bool status);

void wifi_init(void);

bool get_wifi_connect_state(void);

#endif