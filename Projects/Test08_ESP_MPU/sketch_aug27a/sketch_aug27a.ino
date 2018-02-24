#include <ESP8266WiFi.h>
#include "MPU6050.h"
#include <Wire.h>


const int MPU = 0x68; //I2C address of MPU
float GyX, GyY, GyZ;

float pitch = 0;
float roll = 0;
float yaw = 0;

float v_pitch;
float v_roll;
float v_yaw;
float a_pitch;
float a_roll;
float a_yaw;



const char* ssid = "MikroTik";
const char* password = "Rez@1864";


//float temp = 0;
//int  tempPin = 17;


//int ledPin = 16; // GPIO16
WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  Wire.begin(4,5);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); //power management register 1
  Wire.write(0);
  Serial.println(Wire.endTransmission(true));

/*
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("AndroidAP");
*/
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }/*
  Serial.println("");
  Serial.println("WiFi connected");*/

  // Start the server
  server.begin();/*
  Serial.println("Server started");*/
  /*
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");*/

}

void loop() {


    Wire.beginTransmission(MPU);
  Wire.write(0x43);
  //starts with MPU register 43(GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  //requests 6 registers
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  v_pitch = (GyX / 131);
  if (v_pitch == -1)
    //error filtering
  {
    v_pitch = 0;
  }
  v_roll = (GyY / 131);
  if (v_roll == 1)
    //error filtering
  {
    v_roll = 0;
  }
  v_yaw = GyZ / 131;
  a_pitch = (v_pitch * 0.046);
  a_roll = (v_roll * 0.046);
  a_yaw = (v_yaw * 0.045);
  pitch = pitch + v_pitch;
  roll = roll + v_roll;
  yaw = yaw + v_yaw;






  
  // Check if a client has connected


  //temp = analogRead(2);
  //temp = temp * 0.09765625;
  WiFiClient client = server.available();
  /*if (!client) {
    return;
  }*/

  // Wait until the client sends some data
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Serial.println("new client");
  //while (!client.available()) {
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////delay(1);
  //}

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  int q = request.length();
  request.remove(q - 9, 9);/*
  if (request != "favicon.ico")
    Serial.println(request);*/
  client.flush();

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  Serial.println("TEST00_");
  Serial.println("");
  Serial.print(" | pitch = ");
  Serial.print(pitch);
  Serial.print(" | roll = ");
  Serial.print(roll);
  Serial.print(" | yaw = ");
  Serial.println(yaw);
  
}

