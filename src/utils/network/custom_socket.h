#ifndef CUSTOM_SOCKET_H
#define CUSTOM_SOCKET_H



#include "../../config.h"
#include <ArduinoJson.h>
#include "../../devices/dht11.h"
#include "../data_ctr.h"
#include "../../page/main_page.h"

void socketClientInit(void);
void socket_status_check(void);
void getMessage(void);
bool get_socket_connect_status(void);
void socket_loop_function(void);
void send_socket_data(void);
#endif
