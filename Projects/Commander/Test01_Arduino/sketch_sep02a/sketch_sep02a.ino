int Y = 0;
String Q = "";

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Q = "";


  //Serial1.print(digitalRead(13));


  if (Serial1.available() > 0)
  {
    Q = Serial1.readString();

    if (Q == "a1")
    {
      digitalWrite(13, LOW);
    }
    else if (Q == "a0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "b1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "b0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "c1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "c0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "d1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "d0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "e1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "e0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "f1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "f0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "g1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "g0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "h1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "h0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "i1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "i0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "j1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "j0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "k1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "k0")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "l1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "m1")
    {
      digitalWrite(13, HIGH);
    }
    else if (Q == "")
    {

    }
    else
    {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      Serial.println(Q);
    }


    Serial1.print(digitalRead(13));
  }

}
