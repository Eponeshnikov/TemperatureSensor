#include <WebSocketsServer.h>

WebSocketsServer webSocket=WebSocketsServer(81);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    if(payload[0] == '#'){
        Serial.println();
    }

    else
    {
      for(int i = 0; i < length; i++)
        Serial.print((char) payload[i]);
        Serial.println();
    }
  }
}