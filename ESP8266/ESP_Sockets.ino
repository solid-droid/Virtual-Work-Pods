#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
//###############################################################
char SSID[] = "";
char password[] = "";
char socketServer[] = "";
int socketPort = 80;
//###############################################################
bool connected = false;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("Got message: %s\n", payload);
}

void onConnect(const char * payload, size_t length){
  webSocket.emit("plainString", "Connected to ESP");
  connected = true;
  delay(1000);
 }

void onDisconnect(const char * payload, size_t length){
  Serial.println("Websocket Connection Lost");
  connected = true;
  delay(1000);
 }

void setup() {
    USE_SERIAL.begin(9600);
    WiFiMulti.addAP(SSID, password);
    while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.println("No wifi");
        delay(1000);
    }
    webSocket.on("event", event);
    webSocket.on("connect", onConnect);
    webSocket.on("disconnect", onDisconnect);
    webSocket.begin(socketServer,socketPort);

}

unsigned long my_time;
String dataObject;


void loop() {
    webSocket.loop();
    if (connected){
      
//  Put the Gyro values here    
//    Gx = ;
//    Gy = ;
//    Gz = ;
//    Ax = ;
//    Ay = ; 
//    Az = ; 

    dataObject = "{\"Gx\":\"" + String(Gx) + ",\"Gy\":\"" + String(Gy) + ",\"Gz\":\"" + String(Gz) + ",\"Ax\":\"" + String(Ax) + ",\"Ay\":\"" + String(Ay) + ",\"Az\":\"" + String(Az) + "\"}";
    
    // plainString is label used to get data on Node end
    webSocket.emit("plainString", dataObject.c_str());
    // Data is taken as data.Gx, data.Ay etc on Node end
//    delay(1000);
    }
}
