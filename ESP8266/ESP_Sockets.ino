#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
 

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;


const uint8_t scl = 2; //D5
const uint8_t sda = 0; //D6
 
MPU6050 mpu;
 
int16_t ax[8], ay[8], az[8];
int16_t gx[8], gy[8], gz[8];

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
    Wire.begin(sda, scl);
    USE_SERIAL.begin(9600);
    Serial.print("Initializing.");
    for(int i=1;i<6;++i)
    { 
      mux(i);
      Serial.print("..");
      delay(10);
      mpu.initialize();
    }
    Serial.println("Initialization Successful");
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

void mux(int i)
{
  
  switch(i)
  {
//    case 1:
//    digitalWrite(5,0);
//    digitalWrite(6,0);
//    digitalWrite(7,0);
//    break;
//    case 2:
    case 1:
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(7,0);
    break;
//    case 3:
//    digitalWrite(5,0);
//    digitalWrite(6,1);
//    digitalWrite(7,0);
//    break;
//    case 4:
    case 2:
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,0);
    break;
//    case 5:
//    digitalWrite(5,0);
//    digitalWrite(6,0);
//    digitalWrite(7,1);
//    break;
    case 3:
     digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,1);
    break;
    case 4:
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(7,1);
    break;
    case 5:
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(7,1);
    break;
  }
  
}



//int Gx1 = random(0, 180);
//int Gy1 =random(0, 180);
//int Gz1 =random(0, 180);
//int Ax1 =random(0, 180);
//int Ay1 =random(0, 180);
//int Az1 =random(0, 180);
//
//int Gx2 =random(0, 180);
//int Gy2 =random(0, 180);
//int Gz2 =random(0, 180);
//int Ax2 =random(0, 180);
//int Ay2 =random(0, 180);
//int Az2 =random(0, 180);
//
//int Gx3 =random(0, 180);
//int Gy3 =random(0, 180);
//int Gz3 =random(0, 180);
//int Ax3 =random(0, 180);
//int Ay3 =random(0, 180);
//int Az3 =random(0, 180);
//
//int Gx4 =random(0, 180);
//int Gy4 =random(0, 180);
//int Gz4 =random(0, 180);
//int Ax4 =random(0, 180);
//int Ay4 =random(0, 180);
//int Az4 =random(0, 180);
//
//int Gx5 =random(0, 180);
//int Gy5 =random(0, 180);
//int Gz5 =random(0, 180);
//int Ax5 =random(0, 180);
//int Ay5 =random(0, 180);
//int Az5 =random(0, 180);
//
//int Gx6 =random(0, 180);
//int Gy6 =random(0, 180);
//int Gz6 =random(0, 180);
//int Ax6 =random(0, 180);
//int Ay6 =random(0, 180);
//int Az6 =random(0, 180);
//
//int Gx7 =random(0, 180);
//int Gy7 =random(0, 180);
//int Gz7 =random(0, 180);
//int Ax7 =random(0, 180);
//int Ay7 =random(0, 180);
//int Az7 =random(0, 180);
//
//int Gx8 =random(0, 180);
//int Gy8 =random(0, 180);
//int Gz8 =random(0, 180);
//int Ax8 =random(0, 180);
//int Ay8 =random(0, 180);
//int Az8 =random(0, 180);

String dataObject;


void loop() {
    webSocket.loop();
    if (connected){

 for(int i=1;i<=8;++i)
 { 
  mux(i);
  delay(1);
  mpu.getMotion6(&ax[i], &ay[i], &az[i], &gx[i], &gy[i], &gz[i]);
 }  
    dataObject = "{\"gx1\":\"" + String(gx[1]) + 
    ",\"gy1\":\"" + String(gy[1]) + 
    ",\"gz1\":\"" + String(gz[1]) + 
    ",\"ax1\":\"" + String(ax[1]) + 
    ",\"ay1\":\"" + String(ay[1]) + 
    ",\"az1\":\"" + String(az[1]) + 
    ",\"gx2\":\"" + String(gx[2]) + 
    ",\"gy2\":\"" + String(gy[2]) + 
    ",\"gz2\":\"" + String(gz[2]) + 
    ",\"ax2\":\"" + String(ax[2]) + 
    ",\"ay2\":\"" + String(ay[2]) + 
    ",\"az2\":\"" + String(az[2]) + 
    ",\"gx3\":\"" + String(gx[3]) + 
    ",\"gy3\":\"" + String(gy[3]) + 
    ",\"gz3\":\"" + String(gz[3]) + 
    ",\"ax3\":\"" + String(ax[3]) + 
    ",\"ay3\":\"" + String(ay[3]) + 
    ",\"az3\":\"" + String(az[3]) + 
    ",\"gx4\":\"" + String(gx[4]) + 
    ",\"gy4\":\"" + String(gy[4]) + 
    ",\"gz4\":\"" + String(gz[4]) + 
    ",\"ax4\":\"" + String(ax[4]) + 
    ",\"ay4\":\"" + String(ay[4]) + 
    ",\"az4\":\"" + String(az[4]) + 
    ",\"gx5\":\"" + String(gx[5]) + 
    ",\"gy5\":\"" + String(gy[5]) + 
    ",\"gz5\":\"" + String(gz[5]) + 
    ",\"ax5\":\"" + String(ax[5]) + 
    ",\"ay5\":\"" + String(ay[5]) + 
    ",\"az5\":\"" + String(az[5]) + 
    ",\"gx6\":\"" + String(gx[6]) + 
    ",\"gy6\":\"" + String(gy[6]) + 
    ",\"gz6\":\"" + String(gz[6]) + 
    ",\"ax6\":\"" + String(ax[6]) + 
    ",\"ay6\":\"" + String(ay[6]) + 
    ",\"az6\":\"" + String(az[6]) + 
    ",\"gx7\":\"" + String(gx[7]) + 
    ",\"gy7\":\"" + String(gy[7]) + 
    ",\"gz7\":\"" + String(gz[7]) + 
    ",\"ax7\":\"" + String(ax[7]) + 
    ",\"ay7\":\"" + String(ay[7]) + 
    ",\"az7\":\"" + String(az[7]) + 
    ",\"gx8\":\"" + String(gx[8]) + 
    ",\"gy8\":\"" + String(gy[8]) + 
    ",\"gz8\":\"" + String(gz[8]) + 
    ",\"ax8\":\"" + String(ax[8]) + 
    ",\"ay8\":\"" + String(ay[8]) + 
    ",\"az8\":\"" + String(az[8]) + "\"}";
    
    // plainString is label used to get data on Node end
    webSocket.emit("plainString", dataObject.c_str());
    // Data is taken as data.Gx, data.Ay etc on Node end
//    delay(1000);
    }
}
