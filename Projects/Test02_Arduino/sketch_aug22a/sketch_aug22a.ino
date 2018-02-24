#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

//RF24 radio(33, 32);//                 Reciever
RF24 radio(33, 32);//                Station

  char DefTTT[14] = "Hello World";

////////////////////////////////////////////////////////////////////////////////////////////////Reciever


  
void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Serial.begin(9600);
  //radio.begin();
  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
  //radio2.setPALevel(RF24_PA_LOW);
  //radio.setRetries(15,15);
  radio.setRetries(15,15);
  //radio.openReadingPipe(1, 00141);
  radio.openWritingPipe(00001);
  //radio.startListening();

  Serial.println("NRF initialized");
    delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
/*
  if(radio.available())
  {
    char TRT[64];
    radio.read(TRT, sizeof(TRT));
    Serial.println(TRT);
  } */
  
/*
  if(Serial.available())
  {
    Serial.read();
    Serial.println("0");*/
    //char IB = Serial.read();
    //unsigned long Ty = micros();
    //char SIB = IB;
    char SSIB[15] = "HelloMahdii";
    //SSIB[0] = SIB;
    Serial.println("1");
    radio.write("Test",4);
    Serial.println("2");
  }

