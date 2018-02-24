#include <RH_NRF24.h>

#include <SPI.h>

RH_NRF24 nrf24(32,33);
int index = 0;
uint8_t cache[28] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0/* , 0 , 0 , 0 , 0*/};

void setup() {
  
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.println("Setting up NRF");
  
  while(!nrf24.init())
  {
    Serial.println("init failed::TRYING Again");
    delay(3000);
  }
  while(!nrf24.setChannel(1))
  {
    Serial.println("Set channel failed::TRYING Again");
    delay(3000);
  }
  while(!nrf24.setRF(RH_NRF24::DataRate2Mbps,RH_NRF24::TransmitPower0dBm))
  {
    Serial.println("SetRF Failed::TRYING Again");
    delay(3000);
  }
    Serial.println("Done");
}

void loop() {

  if(Serial.available()>0)
  {
    char Y = Serial.read();
    cache[index] = Y;
    index++;
  }
  if(index==28)
  {
    index = 0;
    nrf24.send(cache, sizeof(cache));
    nrf24.waitPacketSent();
  }
  
  //                                                                                   Serial Available


  if(nrf24.available())
  {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len=sizeof(buf);
    if(nrf24.recv(buf,&len))
    {
      String str=(char *)buf;
      Serial.println(str);
    }
    else
    {
      Serial.println("Recieve Failed");
    }
  }
}

void Bl()
{
  /* 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(200); */
}
