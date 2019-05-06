#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
 

const uint8_t scl = 2; //D5
const uint8_t sda = 0; //D6
 
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
void setup()
{
Wire.begin(sda, scl);
Serial.begin(115200);
 Serial.print("Initializing.");
  for(int i=1;i<6;++i)
  { 
    mux(i);
    Serial.print("..");
    delay(10);
    mpu.initialize();
  }
  Serial.println("Initialization Successful");

}
 
void loop()
{

 for(int i=1;i<9;++i)
 { 
  mux(i);
  delay(1);
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(i);
  Serial.print(" = ");
  Serial.print(ay);
  Serial.print(" || ");
  if(i==8)
{
    Serial.println();
    delay(10);
}

}}
