/**
 * @file hcsr505.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HCSR505_H
#define HCSR505_H

void init_hcsr505(void);

void hcsr505_get_value(void (*Callback)(bool));

#endif