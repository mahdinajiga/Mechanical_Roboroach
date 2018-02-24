#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(9, 8);
//RF24 radio2(9, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
  char DefTTT[14] = "Hello World";

////////////////////////////////////////////////////////////////////////////////////////////////Roboroch


  
void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Serial.begin(9600);
  radio.begin();
  //radio2.begin();
  //radio.setPALevel(RF24_PA_LOW);
  //radio2.setPALevel(RF24_PA_LOW);
  radio.setRetries(15,15);
  //radio2.setRetries(15,15);
  radio.openReadingPipe(1, 00001);
  //radio2.openWritingPipe(00141);
  radio.startListening();
  
  char SSIB[12] = "HelloMahdii";
  
  Serial.println("NRF initialized");
    delay(100);
    
  
  //Serial.println(radio2.write(SSIB,sizeof(SSIB)));
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  if(radio.available()>0)
  {
    char TRT[20];
    radio.read(TRT, sizeof(TRT));
    Serial.write(TRT);
  } 
  
/*
  if(Serial.available())
  {
    Serial.println("0");
    char IB = Serial.read();
    //char SIB = IB;
    char SSIB[12] = "HelloMahdii";
    //SSIB[0] = SIB;
    Serial.println("1");
    radio2.write(&SSIB,sizeof(SSIB));
    Serial.println("2");
  }*/
}
