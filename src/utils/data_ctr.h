/**
 * @file data_ctr.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DATA_CTR_H
#define DATA_CTR_H

#include <Arduino.h>

//设置NVS存储数据
void NVSSet(String data, void (*Callback)(void));
//删除NVS数据
void NVSRemove(void);
//获取NVS存储数据
bool NVSGet(char *names[], int arr_len, bool (*Callback)(String, bool));

#endif