#ifndef _REMOTEXY_MOD_ESP8266WIFI_H_
#define _REMOTEXY_MOD_ESP8266WIFI_H_

/*
for ESP8266 board;
need include <ESP8266WiFi.h>;
*/

#include "classes/RemoteXY_API.h"

#define REMOTEXY_SEND_BUFFER_LENGTH 256

class CRemoteXY : public CRemoteXY_API {

  protected:
  uint16_t port;
  char * wifiSsid;
  char * wifiPassword;
  
  WiFiServer *server;
  WiFiClient client; 
  
  uint8_t wifiStatus;
  uint32_t serverTimeOut;
  
  uint8_t sendBuffer[REMOTEXY_SEND_BUFFER_LENGTH];
  uint16_t sendBufferCount; 
  uint16_t sendBytesAvailable;  

  public:
  CRemoteXY (const void * _conf, void * _var, const char * _accessPassword, const char * _wifiSsid, const char * _wifiPassword, uint16_t _port) {
    port = _port;
    wifiSsid = (char *) _wifiSsid;
    wifiPassword = (char *) _wifiPassword;
    serverTimeOut = 0;
    init (_conf, _var, _accessPassword);    
  }
  
  uint8_t initModule () {  
    delay(100);
    WiFi.disconnect();
    WiFi.softAPdisconnect(true);
#if defined(REMOTEXY_WIFI__POINT)
    /* access point */
    WiFi.mode(WIFI_AP);
    WiFi.softAP(wifiSsid, wifiPassword);
#if defined(REMOTEXY__DEBUGLOGS)
    REMOTEXY__DEBUGLOGS.println();
    REMOTEXY__DEBUGLOGS.print("IP: ");
    REMOTEXY__DEBUGLOGS.println(WiFi.softAPIP());
#endif
#else    
    /* station */
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSsid, wifiPassword);
    delay(1000);
    
#if defined(REMOTEXY__DEBUGLOGS)
    REMOTEXY__DEBUGLOGS.println();
    REMOTEXY__DEBUGLOGS.println("Start connecting to access point...");
#endif    
#endif
    client.stop();
    server = new WiFiServer (port);
    server->begin();    
    server->setNoDelay(true);
#if defined(REMOTEXY__DEBUGLOGS)
    REMOTEXY__DEBUGLOGS.println("Server started");
#endif
    return 1;
  }

  void handlerModule () {
    uint8_t status = WiFi.status();
    if (status != wifiStatus) {
      wifiStatus = status;
#if defined(REMOTEXY__DEBUGLOGS)
      if (wifiStatus == WL_CONNECTED) {
        REMOTEXY__DEBUGLOGS.println();
        REMOTEXY__DEBUGLOGS.println("Connected to access point");
        REMOTEXY__DEBUGLOGS.print("IP: ");
        REMOTEXY__DEBUGLOGS.println(WiFi.localIP());
        REMOTEXY__DEBUGLOGS.print ("<-");
      }
#endif  
    }
    
    if (!client) {
      client=server->available();
      if (client) {
        resetServerTimeOut ();  // new client
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.println ();
        REMOTEXY__DEBUGLOGS.println ("Client connected");
        REMOTEXY__DEBUGLOGS.print ("<-");
#endif
      }
    }
    if (client) {
      if (client.connected()) {
        if (serverTimeOut<millis ()) {
          client.stop ();
#if defined(REMOTEXY__DEBUGLOGS)
          REMOTEXY__DEBUGLOGS.println ();
          REMOTEXY__DEBUGLOGS.println ("Client stoped by timeout");
          REMOTEXY__DEBUGLOGS.print ("<-");
#endif
        }
      }
      else {
        client.stop ();
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.println ();
        REMOTEXY__DEBUGLOGS.println ("Client stoped");
        REMOTEXY__DEBUGLOGS.print ("<-");
#endif
      }
    }        
  }


  void sendStart (uint16_t len) {
    sendBytesAvailable = len;
    sendBufferCount = 0;
  }

  void sendByte (uint8_t b) {
    if (client) {
      if (client.connected()) {
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.print (b, HEX);
        REMOTEXY__DEBUGLOGS.print (' ');
#endif
        sendBuffer[sendBufferCount++] = b;
        sendBytesAvailable--;       
        if ((sendBufferCount==REMOTEXY_SEND_BUFFER_LENGTH) || (sendBytesAvailable==0)) {
          uint8_t buf[sendBufferCount];
          for (uint16_t i=0; i<sendBufferCount; i++) buf[i]=sendBuffer[i];
          client.write(buf, sendBufferCount);
          sendBufferCount=0;
          resetServerTimeOut ();
        } 
      }
    }
  }  
  
  uint8_t receiveByte () {
    uint8_t b;
    if (client) {
      if (client.connected()) {
        b = client.read();
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.print (b, HEX);
        REMOTEXY__DEBUGLOGS.print (' ');
#endif
        resetServerTimeOut ();
        return b;
      }
    }
  }
  
  uint8_t availableByte () {   
#if !defined(REMOTEXY_WIFI__POINT)
    if (wifiStatus != WL_CONNECTED) return 0;
#endif
    if (client) {
      if (client.connected()) return client.available();
    }
    return 0;
  }  
  
  void resetServerTimeOut () {
    serverTimeOut = millis ()+REMOTEXY_SERVER_TIMEOUT;
  }

};


#define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)



#endif //_REMOTEXY_MOD_ESP8266WIFI_H_