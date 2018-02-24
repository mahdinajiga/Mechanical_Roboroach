#include <ESP8266WiFi.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

char serialIn = 0;

MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;
float x, y, z;
float total;
float Vall = 0;

int16_t axz = 0, gxz = 0;
float Offsett = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(4, 5);
  accelgyro.initialize();
  /*accelgyro.setXAccelOffset(-1073);
    accelgyro.setYAccelOffset(88);*/
  accelgyro.setZAccelOffset(2025);
  for (int u = 0; u < 200; u++)
  {
    Offsett += accelgyro.getRotationZ();
    delay(50);
  }
  Offsett = Offsett / 200;
  Serial.println("init...");
  Serial.println(Offsett);
  delay(2000);
}

void loop() {
  total += accelgyro.getRotationZ();
  Vall = total - Offsett - .85 * (millis()-12000);
  Serial.println(Vall);
  delay(50);
}
