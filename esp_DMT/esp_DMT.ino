#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>
#ifdef __AVR__
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif
////////////////////////////////////////////////////////////////

#define USE_SERIAL Serial
float time1;
ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
//###############################################################
char SSID[] = "net";
char password[] = "12345678";
char socketServer[] = "192.168.137.74";
int socketPort = 3000;
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


unsigned long my_time;
String myTimeString;
///////////////////////////////////////////////////////////////


int A=16,B=5,C=4;
const uint8_t scl = 2; 
const uint8_t sda = 0; 
 
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;



// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus[10];      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize[10];    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount[10];     // count of all bytes currently in FIFO
uint8_t fifoBuffer[10][64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q[10];           // [w, x, y, z]         quaternion container
//VectorInt16 aa;         // [x, y, z]            accel sensor measurements
//VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
//VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
//VectorFloat gravity;    // [x, y, z]            gravity vector
//float euler[3];         // [psi, theta, phi]    Euler angle container
//float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

void setup()
{
pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
//socket_conn();
  
Wire.begin(sda, scl);
Serial.begin(115200);
 Serial.print("Initializing.");
  for(int i=1;i<9;++i)
  { 
    mux(i);
    Serial.print("..");
    delay(10);
    mpu.initialize();
  }
  Serial.println("Initialization Successful");
  Serial.println(F("Initializing DMP..."));
  for(int i=1;i<9;++i)
  { 
    mux(i);
    devStatus[i] = mpu.dmpInitialize();
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); 
    delay(10);
    if (devStatus == 0)
    { mpu.setDMPEnabled(true);
      packetSize[i] = mpu.dmpGetFIFOPacketSize();
    }
    else 
    Serial.print(F("DMP Initialization failed (code "));
  }
  Serial.println("DMP Successful");




}
 
void loop()
{
int i=1;
while(i<9)
{
   Serial.print(i);
   mux(i);
  dmp_dat(i);
            Serial.print(q[i].w);
            Serial.print("\t");
            Serial.print(q[i].x);
            Serial.print("\t");
            Serial.print(q[i].y);
            Serial.print("\t");
            Serial.println(q[i].z);
    ++i;
}

    Serial.println();
    transmit();
    Serial.println("Data transmitted");
    delay(100);

}
