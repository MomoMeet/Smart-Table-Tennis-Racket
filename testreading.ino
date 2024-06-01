
#include "Wire.h"          
#include "MPU6050.h"    

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte aX;
  byte aY;
  byte aZ;
  byte gX;
  byte gY;
  byte gZ;
};

MyData data;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.aX = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.aY = map(ay, -17000, 17000, 0, 255);  // Y axis data
  data.aZ = map(az, -17000, 17000, 0, 255);  // Z axis data
  data.gX = map(gx, -17000, 17000, 0, 255 ); // X axis data
  data.gY = map(gy, -17000, 17000, 0, 255);  // Y axis data
  data.gZ = map(gz, -17000, 17000, 0, 255);  // Z axis data
  Serial.print(data.aX);Serial.print(",");Serial.print(data.aY);Serial.print(",");Serial.print(data.aZ);Serial.print(",");Serial.print(data.gX);Serial.print(",");Serial.print(data.gY);Serial.print(",");Serial.println(data.gZ);
  delay(500);
}