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


int Gx1 = random(0, 180);
int Gy1 =random(0, 180);
int Gz1 =random(0, 180);
int Ax1 =random(0, 180);
int Ay1 =random(0, 180);
int Az1 =random(0, 180);

int Gx2 =random(0, 180);
int Gy2 =random(0, 180);
int Gz2 =random(0, 180);
int Ax2 =random(0, 180);
int Ay2 =random(0, 180);
int Az2 =random(0, 180);

int Gx3 =random(0, 180);
int Gy3 =random(0, 180);
int Gz3 =random(0, 180);
int Ax3 =random(0, 180);
int Ay3 =random(0, 180);
int Az3 =random(0, 180);

int Gx4 =random(0, 180);
int Gy4 =random(0, 180);
int Gz4 =random(0, 180);
int Ax4 =random(0, 180);
int Ay4 =random(0, 180);
int Az4 =random(0, 180);

int Gx5 =random(0, 180);
int Gy5 =random(0, 180);
int Gz5 =random(0, 180);
int Ax5 =random(0, 180);
int Ay5 =random(0, 180);
int Az5 =random(0, 180);

int Gx6 =random(0, 180);
int Gy6 =random(0, 180);
int Gz6 =random(0, 180);
int Ax6 =random(0, 180);
int Ay6 =random(0, 180);
int Az6 =random(0, 180);

int Gx7 =random(0, 180);
int Gy7 =random(0, 180);
int Gz7 =random(0, 180);
int Ax7 =random(0, 180);
int Ay7 =random(0, 180);
int Az7 =random(0, 180);

int Gx8 =random(0, 180);
int Gy8 =random(0, 180);
int Gz8 =random(0, 180);
int Ax8 =random(0, 180);
int Ay8 =random(0, 180);
int Az8 =random(0, 180);

String dataObject;


void loop() {
    webSocket.loop();
    if (connected){
      
    dataObject = "{\"gx1\":\"" + String(Gx1) + 
    ",\"gy1\":\"" + String(Gy1) + 
    ",\"gz1\":\"" + String(Gz1) + 
    ",\"ax1\":\"" + String(Ax1) + 
    ",\"ay1\":\"" + String(Ay1) + 
    ",\"az1\":\"" + String(Az1) + 
    ",\"gx2\":\"" + String(Gx2) + 
    ",\"gy2\":\"" + String(Gy2) + 
    ",\"gz2\":\"" + String(Gz2) + 
    ",\"ax2\":\"" + String(Ax2) + 
    ",\"ay2\":\"" + String(Ay2) + 
    ",\"az2\":\"" + String(Az2) + 
    ",\"gx3\":\"" + String(Gx3) + 
    ",\"gy3\":\"" + String(Gy3) + 
    ",\"gz3\":\"" + String(Gz3) + 
    ",\"ax3\":\"" + String(Ax3) + 
    ",\"ay3\":\"" + String(Ay3) + 
    ",\"az3\":\"" + String(Az3) + 
    ",\"gx4\":\"" + String(Gx4) + 
    ",\"gy4\":\"" + String(Gy4) + 
    ",\"gz4\":\"" + String(Gz4) + 
    ",\"ax4\":\"" + String(Ax4) + 
    ",\"ay4\":\"" + String(Ay4) + 
    ",\"az4\":\"" + String(Az4) + 
    ",\"gx5\":\"" + String(Gx5) + 
    ",\"gy5\":\"" + String(Gy5) + 
    ",\"gz5\":\"" + String(Gz5) + 
    ",\"ax5\":\"" + String(Ax5) + 
    ",\"ay5\":\"" + String(Ay5) + 
    ",\"az5\":\"" + String(Az5) + 
    ",\"gx6\":\"" + String(Gx6) + 
    ",\"gy6\":\"" + String(Gy6) + 
    ",\"gz6\":\"" + String(Gz6) + 
    ",\"ax6\":\"" + String(Ax6) + 
    ",\"ay6\":\"" + String(Ay6) + 
    ",\"az6\":\"" + String(Az6) + 
    ",\"gx7\":\"" + String(Gx7) + 
    ",\"gy7\":\"" + String(Gy7) + 
    ",\"gz7\":\"" + String(Gz7) + 
    ",\"ax7\":\"" + String(Ax7) + 
    ",\"ay7\":\"" + String(Ay7) + 
    ",\"az7\":\"" + String(Az7) + 
    ",\"gx8\":\"" + String(Gx8) + 
    ",\"gy8\":\"" + String(Gy8) + 
    ",\"gz8\":\"" + String(Gz8) + 
    ",\"ax8\":\"" + String(Ax8) + 
    ",\"ay8\":\"" + String(Ay8) + 
    ",\"az8\":\"" + String(Az8) + "\"}";
    
    // plainString is label used to get data on Node end
    webSocket.emit("plainString", dataObject.c_str());
    // Data is taken as data.Gx, data.Ay etc on Node end
//    delay(1000);
    }
}
