/**
 * @file trigger.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BUZZER_H
#define BUZZER_H

#ifndef BUZZER_DELAY
    #define BUZZER_DELAY 1000
#endif //BUZZER_DELAY


void init_buzzer(void);

void open_buzzer(bool status);

void close_buzzer(void);

#endif