String Q = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  Q = "";

  if (Serial.available() > 0)
  {
    Q = Serial.readString();
    if(Q.indexOf("0")!=-1)
    {
      digitalWrite(24,HIGH);
      delay(2000);
      digitalWrite(24,LOW);
    }
    else if(Q.indexOf("1")!=-1)
    {
      digitalWrite(22,HIGH);
      delay(2000);
      digitalWrite(22,LOW);
    }
  }
}
