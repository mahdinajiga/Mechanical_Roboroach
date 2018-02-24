int Y = 0;
String Q = "";
int spray_r_S = 1000, spray_l_S = 2000;//time of cycling motor
int delaydropr = 100, delaydropl = 100;//delay time of drop
bool sprayr = false, sprayl = false;
int sprayir = 0, sprayil = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  //////////////////////////////////////PIN MODE
  pinMode(22, OUTPUT);//////////////////a
  pinMode(23, OUTPUT);//                b
  pinMode(24, OUTPUT);//////////////////c
  pinMode(25, OUTPUT);//                d
  pinMode(26, OUTPUT);//////////////////e0
  pinMode(27, OUTPUT);//                e1
  pinMode(30, OUTPUT);//////////////////f0
  pinMode(31, OUTPUT);//                f1
  pinMode(34, OUTPUT);//////////////////g0
  pinMode(35, OUTPUT);//                g1
  pinMode(38, OUTPUT);//////////////////h0
  pinMode(39, OUTPUT);//                h1
  pinMode(42, OUTPUT);//////////////////i
  pinMode(43, OUTPUT);//                j
  pinMode(44, OUTPUT);//////////////////k
  pinMode(45, OUTPUT);//                l0                                              Random
  pinMode(46, OUTPUT);//////////////////l1
  pinMode(47, OUTPUT);//                m0
  pinMode(48, OUTPUT);//////////////////m1


  pinMode(28, INPUT_PULLUP);///////////////////e0MS
  pinMode(29, INPUT_PULLUP);///////////////////e1MS
  pinMode(32, INPUT_PULLUP);///////////////////f0MS
  pinMode(33, INPUT_PULLUP);///////////////////f1MS
  pinMode(36, INPUT_PULLUP);///////////////////g0MS
  pinMode(37, INPUT_PULLUP);///////////////////g1MS
  pinMode(40, INPUT_PULLUP);///////////////////h0MS
  pinMode(41, INPUT_PULLUP);///////////////////h1MS

  digitalWrite(22, LOW);//////////////////a
  digitalWrite(23, LOW);//                b
  digitalWrite(24, LOW);//////////////////c
  digitalWrite(25, LOW);//                d
  digitalWrite(26, LOW);//////////////////e0
  digitalWrite(27, LOW);//                e1
  digitalWrite(30, LOW);//////////////////f0
  digitalWrite(31, LOW);//                f1

  digitalWrite(34, LOW);//////////////////g0
  digitalWrite(35, LOW);//                g1
  digitalWrite(38, LOW);//////////////////h0
  digitalWrite(39, LOW);//                h1
  digitalWrite(42, LOW);//////////////////i
  digitalWrite(43, LOW);//                j
  digitalWrite(44, LOW);//////////////////k
  digitalWrite(45, LOW);//                l0                                              Random
  digitalWrite(46, LOW);//////////////////l1
  digitalWrite(47, LOW);//                m0
  digitalWrite(48, LOW);//////////////////m1
}

void loop() {
  // put your main code here, to run repeatedly:
  Q = "";


  //Serial.print(digitalRead(13));


  if (Serial.available() > 0)
  {
    Q = Serial.readString();
    if (Q == "a1")
    {
      digitalWrite(22, HIGH);
      Serial.print("a1");
    }
    else if (Q == "a0")
    {
      digitalWrite(22, LOW);
      Serial.print("a0");
    }
    else if (Q == "b1")
    {
      digitalWrite(23, HIGH);
      Serial.print("b1");
    }
    else if (Q == "b0")
    {
      digitalWrite(23, LOW);
      Serial.print("b0");
    }
    else if (Q == "c1")
    {
      digitalWrite(24, HIGH);
      Serial.print("c1");
    }
    else if (Q == "c0")
    {
      digitalWrite(24, LOW);
      Serial.print("c0");
    }
    else if (Q == "d1")
    {
      digitalWrite(25, HIGH);
      Serial.print("d1");
    }
    else if (Q == "d0")
    {
      digitalWrite(25, LOW);
      Serial.print("d0");
    }
    else if (Q == "e1")/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      digitalWrite(27, HIGH);
      while (digitalRead(29) == HIGH)
      {
        delay(1);
      }
      digitalWrite(27, LOW);
      Serial.print("e1");
    }
    else if (Q == "e0")
    {
      digitalWrite(26, HIGH);
      while (digitalRead(28) == HIGH)
      {
        delay(1);
      }
      digitalWrite(26, LOW);
      Serial.print("e0");
    }
    else if (Q == "e4")
    {
      bool DDD = true;
      bool DDDr = true;
      bool DDDl = true;
      digitalWrite(27, HIGH);
      digitalWrite(31, HIGH);
      while (DDD)
      {
        delay(1);
        if (digitalRead(29) != HIGH)
        {
          DDDr = false; digitalWrite(27, LOW);
        }
        if (digitalRead(33) != HIGH)
        {
          DDDl = false; digitalWrite(31, LOW);
        }
        if (!DDDr)
        {
          if (!DDDl)
          {
            DDD = false;
          }
        }
      }
      Serial.print("e4");
    }
    else if (Q == "e3")
    {
      bool DUD = true;
      bool DUDr = true;
      bool DUDl = true;
      digitalWrite(26, HIGH);
      digitalWrite(30, HIGH);
      while (DUD)
      {
        delay(1);
        if (digitalRead(28) != HIGH)
        {
          DUDr = false; digitalWrite(26, LOW);
        }
        if (digitalRead(32) != HIGH)
        {
          DUDl = false; digitalWrite(30, LOW);
        }
        if (!DUDr)
        {
          if (!DUDl)
          {
            DUD = false;
          }
        }
      }
      Serial.print("e3");
    }//                                                                                                                         Motor
    else if (Q == "f1")
    {
      digitalWrite(31, HIGH);
      while (digitalRead(33) == HIGH)
      {
        delay(1);
      }
      digitalWrite(31, LOW);
      Serial.print("f1");
    }
    else if (Q == "f0")
    {
      digitalWrite(30, HIGH);
      while (digitalRead(32) == HIGH)
      {
        delay(1);
      }
      digitalWrite(30, LOW);
      Serial.print("f0");
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (Q == "g1")
    {
      digitalWrite(34, HIGH);
      while (digitalRead(36) == HIGH)
      {
        delay(1);
      }
      digitalWrite(34, LOW);
      delay(delaydropr);
      digitalWrite(35, HIGH);
      while (digitalRead(37) == HIGH)
      {
        delay(1);
      }
      digitalWrite(35, LOW);
    }
    //                                                                                                                                 drop
    else if (Q == "h1")
    {
      digitalWrite(38, HIGH);
      while (digitalRead(40) == HIGH)
      {
        delay(1);
      }
      digitalWrite(38, LOW);
      delay(delaydropl);
      digitalWrite(39, HIGH);
      while (digitalRead(41) == HIGH)
      {
        delay(1);
      }
      digitalWrite(39, LOW);
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (Q == "i1")
    {
      digitalWrite(42, HIGH);
      Serial.print("i1");
    }
    else if (Q == "i0")
    {
      digitalWrite(42, LOW);
      Serial.print("i0");
    }
    else if (Q == "i4")
    {
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, HIGH);
      Serial.print("i4");
    }
    else if (Q == "i3")
    {
      digitalWrite(42, LOW);
      digitalWrite(43, LOW);
      digitalWrite(44, LOW);
      Serial.print("i3");
    }
    else if (Q == "j1")
    {
      digitalWrite(43, HIGH);
      Serial.print("j1");
    }
    else if (Q == "j0")
    {
      digitalWrite(43, LOW);
      Serial.print("j0");
    }
    else if (Q == "k1")
    {
      digitalWrite(44, HIGH);
      Serial.print("k1");
    }
    else if (Q == "k0")
    {
      digitalWrite(44, LOW);
      Serial.print("k0");
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (Q == "l1")
    {
      if (sprayr)
      {
        digitalWrite(45, HIGH);
        delay(spray_r_S);
        digitalWrite(45, LOW);
        sprayir++;
        if (sprayir > 4)
        {
          sprayir = 0;
          sprayr = false;
        }
      }
      else
      {
        digitalWrite(46, HIGH);
        delay(spray_r_S);
        digitalWrite(46, LOW);
        sprayir++;
        if (sprayir > 4)
        {
          sprayir = 0;
          sprayr = true;
        }
      }
    }
    else if (Q == "m1")
    {
      if (sprayl)
      {
        digitalWrite(47, HIGH);
        delay(spray_l_S);
        digitalWrite(47, LOW);
        sprayil++;
        if (sprayil > 4)
        {
          sprayil = 0;
          sprayl = false;
        }
      }
      else
      {
        digitalWrite(48, HIGH);
        delay(spray_l_S);
        digitalWrite(48, LOW);
        sprayil++;
        if (sprayil > 4)
        {
          sprayil = 0;
          sprayl = true;
        }
      }
    }
    else if (Q == "")
    {

    }
    else
    { /*
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
        Serial.println(Q);*/
    }

    //Serial.print(digitalRead(13));
  }
}
