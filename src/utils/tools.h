/**
 * @file tools.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TOOLS_H
#define TOOLS_H

#ifndef TIME_API_URL
    #define TIME_API_URL "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp"
#endif //TIME_API_URL


void getNetworkTime(void);

#endif