#include <Servo.h>
Servo myservo;

char cache[3] = {0, 0, 0};
int indexx = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  while (Serial.available() == 0)
  {
    delay(1);
  }
  String y = Serial.readString();
  myservo.attach(14);
  myservo.write(0);
  delay(3000);


}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0)
  {
    String ttt = Serial.readString();
    myservo.write(ttt.toInt());
    Serial.println(ttt);
  }/*
  myservo.write(indexx);
  delay(3000);
  if (indexx > 150)
    indexx = 0;
  indexx += 18;
  if (myservo.read() != 90)
  {
    delay(200);
    myservo.write(90);
  }*/
}
