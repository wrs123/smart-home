#include "custom_socket.h"
#include <ArduinoWebsockets.h>


enum class ConnectStatus{
    CONNECTED,
    UNCONNECT,
    CONNECTING,
    CONNECTERR
};
ConnectStatus SOCKET_STATUS = ConnectStatus::UNCONNECT;
using namespace websockets;
WebsocketsClient client;
static long wait_dealy=0;


/**
 * @brief 
 * socket客户端初始化
 */
void socketClientInit(void){
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("连接socket状态");
    SOCKET_STATUS = ConnectStatus::CONNECTING;
    bool connected = client.connect(WEBSOCKET_SERVER_HOST, WEBSOCKET_SERVER_POST, WEBSOCKET_SERVER_PATH);
    if(connected) {
      SOCKET_STATUS = ConnectStatus::CONNECTED;
        Serial.println("socket连接成功");
    } else {
      SOCKET_STATUS = ConnectStatus::UNCONNECT;
        Serial.println("socket连接失败");
    }
  }
}



/**
 * @brief 
 * socket连接状态判断
 */
void socket_status_check(void){
  Serial.println("获取socket连接状态");
  client.onEvent([](WebsocketsClient& client, WebsocketsEvent event, String payload){
      switch (event){
        case WebsocketsEvent::ConnectionClosed:  //连接被关闭
          Serial.print("connect close");
          SOCKET_STATUS = ConnectStatus::UNCONNECT;
          /* code */
          break; 
        case WebsocketsEvent::ConnectionOpened:  //连接成功
          Serial.print("connect open");
          SOCKET_STATUS = ConnectStatus::CONNECTED;
          break;
        default :
          Serial.print("connect 11");
          break;
      }
    });
}



/**
 * @brief 
 *  socket数据接收
 */
void getMessage(void){
  if(client.available()) {
    client.onMessage([&](WebsocketsMessage message){
      DynamicJsonDocument doc(1024);
      String data = message.data();
      deserializeJson(doc, data);
      String type = doc["type"];
      String message_type = doc["data"]["type"];

      // switch (type)
      // {
      // case "normal":
      //   /* code */
      //   break;
      // case "ctr":
      //   /* code */
      //   break;
      // default:
      //   break;
      // }
      bool led_power = doc["data"]["power"];
      
      // if(!ledStatus){
      //   led_open();
      // }else{
      //   led_close();
      // }
      // ledStatus = led_power;
      Serial.print("Got Message: ");
      Serial.print(data);
  });
    client.poll();
  }
}

/**
 * @brief Get the socket status object
 * 获取socket连接状态
 */
bool get_socket_connect_status(void){
  return SOCKET_STATUS == ConnectStatus::CONNECTED;
}

/**
 * @brief 发送数据
 * 
 */
void send_socket_data(void){
  String param = "{'from': '/pico', 'to': '/app', 'type':'normal', data: {}";
  String ouput_param;
  DynamicJsonDocument dataDoc(1024);
  deserializeJson(dataDoc, param);
  JsonObject obj = dataDoc.as<JsonObject>();

  obj[String("data")][String("temp")] = get_temp_data();
  obj[String("data")][String("hum")] = get_hum_data();
  
  serializeJson(dataDoc, ouput_param); 

  client.send(ouput_param);
}


/**
 * @brief 循环方法容器
 * 
 */
void socket_loop_function(void){
   unsigned long currentTime = millis();
    if(currentTime - wait_dealy > 500){
      wait_dealy = currentTime;
      socket_status_check(); //检查socket连接状态
      if(SOCKET_STATUS != ConnectStatus::CONNECTING && SOCKET_STATUS != ConnectStatus::CONNECTED){
        socketClientInit(); //连接socket
        return ;
      }
      send_socket_data();
    }
}
