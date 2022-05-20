#include "custom_socket.h"
#include <ArduinoWebsockets.h>
#include "../../devices/led.h"


enum class SocketConnectStatus{
    CONNECTED,
    UNCONNECT,
    CONNECTING,
    CONNECTERR
};
SocketConnectStatus SOCKET_STATUS = SocketConnectStatus::UNCONNECT;
using namespace websockets;
WebsocketsClient client;
static long wait_dealy=0;
String key = "";
int id = 1;


bool keyInitCallback(String data, bool status){
  if(status){
      DynamicJsonDocument doc(128);
      deserializeJson(doc, data);
      String network_key = doc["key"]; 
      key = network_key;
      Serial.println(network_key);
      return true;
    }
    return false;
}

/**
 * @brief 
 * 获取本地存储key
 * @return String 
 */
void key_init(void){
  char *key[] = {"key"};

  NVSGet(key, 1, keyInitCallback);
}


/**
 * @brief 
 * socket客户端初始化
 */
void socketClientInit(void){
  if(WiFi.status() == WL_CONNECTED){
    key_init();
    Serial.println("连接socket状态");
    SOCKET_STATUS = SocketConnectStatus::CONNECTING;
    String server_path = WEBSOCKET_SERVER_PATH;
    String path = server_path+"?"+key;
    Serial.println(path);
    bool connected = client.connect(WEBSOCKET_SERVER_HOST, WEBSOCKET_SERVER_POST, path);
    if(connected) {
      SOCKET_STATUS = SocketConnectStatus::CONNECTED;
        Serial.println("socket连接成功");
    } else {
      SOCKET_STATUS = SocketConnectStatus::UNCONNECT;
        Serial.println("socket连接失败");
    }
  }
}



/**
 * @brief 
 * socket连接状态判断
 */
void socket_status_check(void){
  // Serial.println("获取socket连接状态");
  client.onEvent([](WebsocketsClient& client, WebsocketsEvent event, String payload){
      switch (event){
        case WebsocketsEvent::ConnectionClosed:  //连接被关闭
          Serial.print("connect close");
          SOCKET_STATUS = SocketConnectStatus::UNCONNECT;
          /* code */
          break; 
        case WebsocketsEvent::ConnectionOpened:  //连接成功
          Serial.print("connect open");
          SOCKET_STATUS = SocketConnectStatus::CONNECTED;
          break;
        default :
          Serial.print("connect 11");
          break;
      }
    });
}


void command_choose(int command, uint32_t value){
  switch (command)
      {
      case 0: //led
        Serial.println(command);
        set_led_value(value);
        setLedValue(String(value));
        break;
      default:
        break;
      }
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
      int type = doc["type"];
      int message_id = doc["id"];
      Serial.println(message_id);

      switch (type)
      {
      case 0:  //data
       
        break;
      case 1: {//commend
        String value = doc["data"]["value"];
        command_choose(doc["data"]["command"], doc["data"]["value"]);
        
        client.send("{'id':"+String(message_id)+",'from': '/pico', 'to': '/app', 'type':3, 'data': {'command':0,'value':"+value+",'code':0}}");
        break;
        }
      default:
        break;
      }
      
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
  return SOCKET_STATUS == SocketConnectStatus::CONNECTED;
}

/**
 * @brief 发送数据
 * 
 */
void send_socket_data(void){
  String param = "{'id':"+String(id)+",'from': '/pico', 'to': '/app', 'type':0, 'data': {}";
  String ouput_param;
  DynamicJsonDocument dataDoc(1024);
  deserializeJson(dataDoc, param);
  JsonObject obj = dataDoc.as<JsonObject>();

  obj[String("data")][String("temp")] = get_temp_data();
  obj[String("data")][String("hum")] = get_hum_data();
  
  serializeJson(dataDoc, ouput_param); 

  id+=1;
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
      if(SOCKET_STATUS != SocketConnectStatus::CONNECTING && SOCKET_STATUS != SocketConnectStatus::CONNECTED){
        socketClientInit(); //连接socket
        return ;
      }
      send_socket_data();
      getMessage();
    }
}
