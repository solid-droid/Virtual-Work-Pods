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
String myTimeString;


void loop() {
    webSocket.loop();
    if (connected){
    my_time = millis();
    
    //Data has to be in {}
    myTimeString = "{\"Time\":\"" + String(my_time) + "\"}";
    //plainString is label
    webSocket.emit("plainString", myTimeString.c_str());
    delay(1000);
    }
}
