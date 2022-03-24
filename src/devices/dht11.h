/**
 * @file dht11.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DHT11_H
#define DHT11_H

void DHT11_init(void);

float get_temp_data(void);

float get_hum_data(void);

#endif