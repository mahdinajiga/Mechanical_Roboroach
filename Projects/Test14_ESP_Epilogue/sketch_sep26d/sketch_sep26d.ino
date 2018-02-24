#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Wire.h>

int YPR[3];                                 //gy953 yaw pitch roll buffer
unsigned char Re_buf[11], counter = 0;      //main buffer of gy953
unsigned char sign = 0;                     //releative
bool EnableP = true;

int xTOTAL;
int xNavDeggree;
int xTPperDEG;
int xdefPWMspeed;
int xdefTIMspeed;
int xRotateRoborochDeg;
int xRotateRoborochDegTol;
int xRotateRoborochDegDef;
int xPosM;
int xNegM;
int xCode;
bool xdefTIMspeedB;
bool xdefPWMspeedB;
bool xRotateRoborochProgB;



ESP8266WebServer server(80);


const char* ssid = "ESP8266_ROBOROCH_AP";
const char* passphrase = "ed4a7f13";
String st;
String content;
String DevName = "MAHDI NAJI";
String DevAddr = "@TNEGABSU";
int statusCode;
int gy99 = 1;
//    4           5             14           16
bool lc0 = false, lc1 = false, lc2 = false, lc3 = false;


//////////////////////////////////////////////////Roboroch
int Deggree = 0;
int NavDeggree = 90;
int TPperDEG = 5689;///////////////////////Required (Time * PWM) to rotate 1 degree
int defPWMspeed = 512;////////////////////Default PWM to rotate
bool defPWMspeedB = true;///////////////Based on PWM
int defTIMspeed = 1000;////////////////////Default TIME to rotate
bool defTIMspeedB = false;///////////////Based on TIM
bool RotateRoborochProgB = false;///////indicates Roboroch Rotation progress status
int RotateRoborochDeg = 0;//////////////indicates Roboroch Rotation Default Degree
int RotateRoborochDegTol = 5;///////////Degree tolerance
int RotateRoborochDegDef = 30;//////////in rotation, nav degree will be  this number
//Pinouts
int PosM = 12, NegM = 13;////////////////////////////////////////////////////////////////////////////////////////Driver pins OUTPUT
bool RoboStable = false;
//////////////////////////////////////////////////
int Totall = 0;


void setup() {
  for (int FFF = 0; FFF < 4; FFF++)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(16, HIGH);
    delay(250);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(14, LOW);
    digitalWrite(16, LOW);
    delay(250);
  }
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(16, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(14, LOW);
  digitalWrite(16, LOW);

  Serial.begin(115200);
  //EEPROM.begin(4096);
  ///////////////////////////////////// read eeprom for ssid and pass
  EEPROM.begin(512);
  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }

  InitEEPROM();

  if ( esid.length() > 1 ) {
    ssid = esid.c_str();
    passphrase = epass.c_str();
  }
  //////////////////////////////////////initiating GY953
  Serial.write(0XA5);
  Serial.write(0X45);
  Serial.write(0XEA);
  //////////////////////////////////////initiating AccessPoint
  setupAP();
}


void launchWeb() {
  createWebServer();
  server.begin();
}


void setupAP(void) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP(ssid, passphrase, 6);///////////////////////////////////////////////////////////////WiFi Channel (Default set to 6)
  launchWeb();
}


void createWebServer()
{
  server.on("/", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    SetContentRoot(ipStr);
    server.send(200, "text/html", content);
  });

  server.on("/TERMINATE", []() {
    SelEEP();
    String NSSID = "ESP_TERMINATED";
    String NPASS = "7re8f511";
    for (int i = 0; i < 96; ++i) {
      EEPROM.write(i, 0);
    }
    for (int i = 0; i < NSSID.length(); ++i)
    {
      EEPROM.write(i, NSSID[i]);
    }
    for (int i = 0; i < NPASS.length(); ++i)
    {
      EEPROM.write(32 + i, NPASS[i]);
    }
    EEPROM.commit();
    server.send(200, "text/html", "Done");
  });

  server.on("/EEPROMConfig", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    SetContentEEP(ipStr);
    server.send(200, "text/html", content);
  });


  server.on("/EEPConfig", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    String qa = server.arg("a");
    String qb = server.arg("b");
    String qc = server.arg("c");
    String qd = server.arg("d");
    String qe = server.arg("e");
    String qf = server.arg("f");
    String qg = server.arg("g");
    String qh = server.arg("h");
    String qi = server.arg("i");
    String qj = server.arg("j");
    String qk = server.arg("k");
    String ql = server.arg("l");
    String qm = server.arg("m");
    String qn = server.arg("n");
    bool Chng = false;
    /*
       a xTOTAL;
      b xNavDeggree;
      c xTPperDEG;
      d xdefPWMspeed;
      e xdefTIMspeed;
      f xRotateRoborochDeg;
      g xRotateRoborochDegTol;
      h xRotateRoborochDegDef;
      i xPosM;
      j xNegM;
      k xCode;
      l xdefTIMspeedB;
      m xdefPWMspeedB;
      n xRotateRoborochProgB;
    */
    if (qa != "")
    {
      Chng = true;
      xTOTAL = qa.toInt();
    }
    if (qb != "")
    {
      Chng = true;
      xNavDeggree = qb.toInt();
    }
    if (qc != "")
    {
      Chng = true;
      xTPperDEG = qc.toInt();
    }
    if (qd != "")
    {
      Chng = true;
      xdefPWMspeed = qd.toInt();
    }
    if (qe != "")
    {
      Chng = true;
      xdefTIMspeed = qe.toInt();
    }
    if (qf != "")
    {
      Chng = true;
      xRotateRoborochDeg = qf.toInt();
    }
    if (qg != "")
    {
      Chng = true;
      xRotateRoborochDegTol = qg.toInt();
    }
    if (qh != "")
    {
      Chng = true;
      xRotateRoborochDegDef = qh.toInt();
    }
    if (qi != "")
    {
      Chng = true;
      xPosM = qi.toInt();
    }
    if (qj != "")
    {
      Chng = true;
      xNegM = qj.toInt();
    }
    if (qk != "")
    {
      Chng = true;
      xCode = qk.toInt();
    }
    if (ql != "")
    {
      Chng = true;
      if (ql == "True")
      {
        xdefTIMspeedB = true;
        xdefPWMspeedB = false;
      }
      else if (ql == "False")
      {
        xdefTIMspeedB = false;
        xdefPWMspeedB = true;
      }
    }
    if (qm != "")
    {
      Chng = true;
      if (ql == "True")
      {
        xdefPWMspeedB = true;
        xdefTIMspeedB = false;
      }
      else if (ql == "False")
      {
        xdefPWMspeedB = false;
        xdefTIMspeedB = true;
      }
    }
    if (qn != "")
    {
      Chng = true;
      if (ql == "True")
      {
        xRotateRoborochProgB = true;
      }
      else if (ql == "False")
      {
        xRotateRoborochProgB = false;
      }
    }
    if (Chng)
    {
      SetEEP();
      UpdEEP();
    }
    SetContentEEP(ipStr);
    server.send(statusCode, "text/html", content);
  });


  server.on("/order", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    String qa = server.arg("a");
    String qb = server.arg("b");
    String qc = server.arg("c");
    String qd = server.arg("d");
    String qe = server.arg("e");
    String qn = server.arg("DvNm");
    String qo = server.arg("DvAd");
    if (qn != "")
      DevName = qn;
    if (qo != "")
      DevAddr = qo;

    if (qa != "")
    {
      int uuu = qa.toInt();
      SetNavDegree(uuu);
    }
    if (qb != "")
    {
      int uuuu = qb.toInt();
      int Cuu = NavDeggree;
      yield();
      SetNavDegree(uuuu);
      yield();
      SetNavDegree(Cuu);
      yield();
    }
    if (qc != "")
    {
      int uu = qc.toInt();
      yield();
      RotateRoboroch(uu, true);
    }
    if (qd != "")
    {
      if (qd == "True")
      {
        RotateRoborochProgB = true;
      }
      else if (qd == "False")
      {
        RotateRoborochProgB = false;
      }
    }
    if (qe != "")
    {
      if (qe == "True")
      {
        RoboStable = true;
      }
      else if (qe == "False")
      {
        RoboStable = false;
      }
    }
    SetContentRoot(ipStr);
    server.send(statusCode, "text/html", content);
  });


  server.on("/GenInfo", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    content = "<!DOCTYPE HTML><html>Hello from NEW FOLDER grp {ROBOROCH} (Device running on ESP8266-07) ";
    content += ipStr;
    content += "<p>";
    content += st;
    content += "</p><p>";
    content += "\tYAW:";
    content += YPR[0];
    content += "\tPITCH:";
    content += YPR[1];
    content += "\tROLL:";
    content += YPR[2];
    content += "</p></html>";
    server.send(200, "text/html", content);
  });


  server.on("/GY", []() {
    content = YPR[0];
    content += ":::";
    content += YPR[1];
    content += ":::";
    content += YPR[2];
    server.send(200, "text/html", content);
  });

  server.on("/EEPROM", []() {
    String DC = "<!DOCTYPE HTML><html>EEPROM information {ROBOROCH} (Device running on ESP8266-07) ";
    DC += "<p></p>";
    GetEEP();
    DC += "<p>ESSID:</p><p>";
    DC += ssid;
    DC += "</p><p></p><p>EPASS:</p><p>";
    DC += passphrase;
    DC += "</p><p></p><p>TOTAL:</p><p>";
    DC += xTOTAL;
    DC += "</p><p></p><p>NavDeggree:</p><p>";
    DC += xNavDeggree;
    DC += "</p><p></p><p>TPperDEG:</p><p>";
    DC += xTPperDEG;
    DC += "</p><p></p><p>defPWMspeed:</p><p>";
    DC += xdefPWMspeed;
    DC += "</p><p></p><p>defPWMspeedB:</p><p>";
    DC += xdefPWMspeedB;
    DC += "</p><p></p><p>defTIMspeed:</p><p>";
    DC += xdefTIMspeed;
    DC += "</p><p></p><p>defTIMspeedB:</p><p>";
    DC += xdefTIMspeedB;
    DC += "</p><p></p><p>RotateRoborochProgB:</p><p>";
    DC += xRotateRoborochProgB;
    DC += "</p><p></p><p>RotateRoborochDeg:</p><p>";
    DC += xRotateRoborochDeg;
    DC += "</p><p></p><p>RotateRoborochDegTol:</p><p>";
    DC += xRotateRoborochDegTol;
    DC += "</p><p></p><p>RotateRoborochDegDef:</p><p>";
    DC += xRotateRoborochDegDef;
    DC += "</p><p></p><p>Code:</p><p>";
    DC += xCode;
    DC += "</p><p></p><p>PosM:</p><p>";
    DC += xPosM;
    DC += "</p><p></p><p>NegM:</p><p>";
    DC += xNegM;
    DC += "</p><p></p><p>End of EEPROM ;)</p>";
    server.send(200, "text/html", DC);
  });

  server.on("/EEPROMd", []() {
    String DC = "<!DOCTYPE HTML><html>EEPROM information {ROBOROCH} (Device running on ESP8266-07) ";
    DC += "<p></p>";
    DC += "<p>ESSID:</p><p>";
    DC += ssid;
    DC += "</p><p></p><p>EPASS:</p><p>";
    DC += passphrase;
    DC += "</p><p></p><p>TOTAL:</p><p>";
    DC += Totall;
    DC += "</p><p></p><p>NavDeggree:</p><p>";
    DC += NavDeggree;
    DC += "</p><p></p><p>TPperDEG:</p><p>";
    DC += TPperDEG;
    DC += "</p><p></p><p>defPWMspeed:</p><p>";
    DC += defPWMspeed;
    DC += "</p><p></p><p>defPWMspeedB:</p><p>";
    DC += defPWMspeedB;
    DC += "</p><p></p><p>defTIMspeed:</p><p>";
    DC += defTIMspeed;
    DC += "</p><p></p><p>defTIMspeedB:</p><p>";
    DC += defTIMspeedB;
    DC += "</p><p></p><p>RotateRoborochProgB:</p><p>";
    DC += RotateRoborochProgB;
    DC += "</p><p></p><p>RotateRoborochDeg:</p><p>";
    DC += RotateRoborochDeg;
    DC += "</p><p></p><p>RotateRoborochDegTol:</p><p>";
    DC += RotateRoborochDegTol;
    DC += "</p><p></p><p>RotateRoborochDegDef:</p><p>";
    DC += RotateRoborochDegDef;
    DC += "</p><p></p><p>PosM:</p><p>";
    DC += PosM;
    DC += "</p><p></p><p>NegM:</p><p>";
    DC += NegM;
    DC += "</p><p></p><p>End of EEPROM ;)</p>";
    server.send(200, "text/html", DC);
  });


  server.on("/admin", []() {
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    content = "<!DOCTYPE HTML><html>Welcome to ADMINISTRATION UNIT... ";
    content += ipStr;
    content += "<p>";
    //content += st;
    content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><label>PASS: </label><input name='pass' length=64><input type='submit' value='Set'></form>";
    content += "</html>";
    EnableP = true;
    server.send(200, "text/html", content);
  });
  server.on("/setting", []() {
    String qsid = server.arg("ssid");
    String qpass = server.arg("pass");
    String qC = server.arg("passcode");
    content = "{\"Error\":\"403 Forbidden\"}";
    statusCode = 403;
    if (qC == "8980")
    {
      if (qsid.length() > 0 && qpass.length() > 0) {
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
        }
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
        }
        EEPROM.commit();
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi{ADMIN}\"}\n\nSSID:\n";
        content += qsid;
        content += "\nPass:\n";
        content += qpass;
        statusCode = 200;
      } else {
        content = "{\"Error\":\"403 Forbidden\"}";
        statusCode = 403;
      }
    }
    server.send(statusCode, "application/json", content);
  });


  server.on("/cleareeprom", []() {
    content = "<!DOCTYPE HTML><html>";
    content += "<p>{\"Error\":\"403 Forbidden\"} </p> </html>";
    if (EnableP)
    {
      SelEEP();
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
      content = " <!DOCTYPE HTML> <html>";
      content += "<p>EEPROM Terminated!!!</p></html>";
    }
    server.send(200, "text/html", content);
  });

  server.on("/ReSendGYReq", []() {
    ReEnableSensor();
    String Ty = "Request Delivered\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\GY-953 Status:\t";
    Ty += gy99;
    server.send(statusCode, "text/html", Ty);
  });
}


void loop() {
  if (Serial.available()) {
    Re_buf[counter] = (unsigned char)Serial.read();
    if (counter == 0 && Re_buf[0] != 0x5A) return;
    counter++;
    if (counter == 11)
    {
      counter = 0;
      sign = 1;
    }
  }
  if (sign)
  {
    LEDC(0, 2);
    sign = 0;
    if (Re_buf[0] == 0x5A && Re_buf[1] == 0x5A )
    {
      YPR[0] = (Re_buf[8] << 8 | Re_buf[9]) / 100;
      YPR[1] = (Re_buf[6] << 8 | Re_buf[7]) / 100;
      YPR[2] = (Re_buf[4] << 8 | Re_buf[5]) / 100;
      if (YPR[0] > 180)
        YPR[0] -= 295;
      if (YPR[1] > 180)
        YPR[1] -= 295;
      if (YPR[2] > 180)
        YPR[2] -= 295;
      Deggree = YPR[0];
      /*
        Serial.print(YPR[0], DEC);
      */
      delay(10);
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Looooooooooooooooooooooooooooooooooop

  //////////////////////////////////////////////////////////////////////////RotateRoboroch
  if (RotateRoborochProgB)
  {
    LEDC(3, 1);
    LEDC(1, 2);
    int DeggToRotateRoboroch = Deggree - RotateRoborochDeg;
    int Tr = 1;
    if (DeggToRotateRoboroch < 0)
    {
      DeggToRotateRoboroch = DeggToRotateRoboroch * (-1);
      Tr = -1;
    }
    if (DeggToRotateRoboroch > RotateRoborochDegDef)
    {
      int Deggg = 90 + (RotateRoborochDegDef * Tr);
      SetNavDegree(Deggg);
    }
    else
    {
      if (DeggToRotateRoboroch < RotateRoborochDegTol)
      {
        if (!RoboStable)
          RotateRoborochProgB = false;
      }
      else
      {
        SetNavDegree(90 + (DeggToRotateRoboroch * Tr));
      }
    }
  }
  else
  {
    LEDC(3, 0);
  }
  //////////////////////////////////////////////////////////////////////////
  server.handleClient();
}


void ReEnableSensor()
{
  if (EnableP)
  {
    if (gy99 == 1)
    {
      gy99 = 0;
    }
    else if (gy99 == 0)
    {
      gy99 = 1;
    }
    Serial.write(0XA5);
    Serial.write(0X45);
    Serial.write(0XEA);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////RotateRoboroch
int RotateRoboroch(int Degg, bool Statuss)
{
  if (Statuss)
  {
    RotateRoborochDeg = Degg;
  }
  else if (!Statuss)
  {
    RotateRoborochDeg = 0;
  }
  RotateRoborochProgB = Statuss;
}


//////////////////////////////////////////////////////////////////////////////////////////////SetNavDegree
int SetNavDegree(int Degg)
{
  LEDC(2, 1);
  /*
    100 no diffrence between degg and navdeg
    101 successful
    102 error on pwm or time default bool
    103 degg < 0
    104 degg > 180
  */
  if (Degg < 0)
    return 103;
  if (Degg > 180)
    return 104;
  int DiffDeg = Degg - NavDeggree;
  if (DiffDeg == 0)
  {
    LEDC(2, 0);
    return 100;
  }
  int MotorPin = PosM;
  if (DiffDeg < 0)
  {
    MotorPin = NegM;
    DiffDeg = DiffDeg * (-1);
  }
  int ReqTB = DiffDeg * TPperDEG;
  if (defPWMspeedB)
  {
    int TimeToRotate = ReqTB / defPWMspeed;
    yield();
    analogWrite(MotorPin, defPWMspeed);
    delay(TimeToRotate);
    analogWrite(NegM, 1);
    analogWrite(PosM, 1);
    yield();
    NavDeggree = Degg;
    xNavDeggree = NavDeggree;
    SetEEP();
    LEDC(2, 0);
    return 101;
  }
  else if (defTIMspeedB)
  {
    int PwmToRotate = ReqTB / defTIMspeed;
    yield();
    analogWrite(MotorPin, PwmToRotate);
    delay(defTIMspeed);
    analogWrite(NegM, 1);
    analogWrite(PosM, 1);
    yield();
    NavDeggree = Degg;
    xNavDeggree = NavDeggree;
    SetEEP();
    LEDC(2, 0);
    return 101;
  }
  else {
    return 102;
  }
}


void SetContentRoot(String ipStrr)
{
  content = " <!DOCTYPE HTML> <html>Hello from NEW FOLDER grp {ROBOROCH}(Device running on ESP8266 - 07 at ";
  content += ipStrr;
  content += ")<form method = 'get' action = 'order'><p><ol>";
  content += "<li><p></p><label>Set Navigator Degree (0-180): </label><input name='a' length=32><input type='submit' value='Set'><p></p>Current Navigator Degree: ";
  content += NavDeggree;
  content += "</li><li><p></p><label>Set Navigator Degree and return: </label><input name='b' length=32><input type='submit' value='Set'><p></p></li>";
  content += "<li><p></p><label>Set Roboroch Heading: </label><input name='c' length=32><input type='submit' value='Set'><p></p>Confirmed Roboroch Heading is: ";
  content += RotateRoborochDeg;
  String qwe = "";
  if (RotateRoborochProgB)
  {
    qwe = "IN_PROGRESS";
  }
  else
  {
    qwe = "NOT IN_PROGRESS";
  }
  content += " and " + qwe + "</li>";
  content += "<li><p></p><label>Set Roboroch Rotation PROGRESS: </label><input name='d' type='submit' value='False'><input name='d' type='submit' value='True'><p></p></li>";
  qwe = "";
  if (RoboStable)
  {
    qwe = "STABLE";
  }
  else
  {
    qwe = "NOT_STABLE";
  }
  content += "<li><p></p><label>Set Roboroch Stable: </label><input name='e' type='submit' value='False'><input name='e' type='submit' value='True'><p></p>Current: " + qwe + "</li>";
  content += "</ol></p><p></p></form>";
  content += "<p>---------------------------------------------------------------------------</p>";
  content += "<p>Current Degree:</p><p>";
  content += Deggree;
  content += "<p>Current Navigator Degree:</p><p>";
  content += NavDeggree;
  content += "<p>Roboroch Rotation PROGRESS:</p><p>";
  content += ((RotateRoborochProgB) ? "IN_PROGRESS" : "NOT IN_PROGRESS");
  content += "<p>Confirmed Roboroch Heading:</p><p>";
  content += RotateRoborochDeg;
  content += "</p><p>---------------------------------------------------------------------------</p>";
  content += "<p style='text-align: center;'><em>DEVELOPED BY " + DevName + "<br></em></p><p style=\"text-align: center;\"><em>" + DevAddr + "<br></em></p>";
  content += "</html>";
}


void SetContentEEP(String ipStrr)
{
  content = " <!DOCTYPE HTML> <html>Hello from NEW FOLDER grp {ROBOROCH}(Device running on ESP8266 - 07 at ";
  content += ipStrr;
  content += ")<form method = 'get' action = 'EEPConfig'><p><ol>";
  content += "<li><p></p><label>xTOTAL: </label><input name='a' length=32><input type='submit' value='Set'><p></p>Current xTOTAL: ";
  content += xTOTAL;
  content += "</li><li><p></p><label>xNavDeggree: </label><input name='b' length=32><input type='submit' value='Set'><p></p>Current xNavDeggree: ";
  content += xNavDeggree;
  content += "</li><li><p></p><label>xTPperDEG: </label><input name='c' length=32><input type='submit' value='Set'><p></p>Current xTPperDEG: ";
  content += xTPperDEG;
  content += "</li><li><p></p><label>xdefPWMspeed: </label><input name='d' length=32><input type='submit' value='Set'><p></p>Current xdefPWMspeed: ";
  content += xdefPWMspeed;
  content += "</li><li><p></p><label>xdefTIMspeed: </label><input name='e' length=32><input type='submit' value='Set'><p></p>Current xdefTIMspeed: ";
  content += xdefTIMspeed;
  content += "</li><li><p></p><label>xRotateRoborochDeg: </label><input name='f' length=32><input type='submit' value='Set'><p></p>Current xRotateRoborochDeg: ";
  content += xRotateRoborochDeg;
  content += "</li><li><p></p><label>xRotateRoborochDegTol: </label><input name='g' length=32><input type='submit' value='Set'><p></p>Current xRotateRoborochDegTol: ";
  content += xRotateRoborochDegTol;
  content += "</li><li><p></p><label>xRotateRoborochDegDef: </label><input name='h' length=32><input type='submit' value='Set'><p></p>Current xRotateRoborochDegDef: ";
  content += xRotateRoborochDegDef;
  content += "</li><li><p></p><label>xPosM: </label><input name='i' length=32><input type='submit' value='Set'><p></p>Current xPosM: ";
  content += xPosM;
  content += "</li><li><p></p><label>xNegM: </label><input name='j' length=32><input type='submit' value='Set'><p></p>Current xNegM: ";
  content += xNegM;
  content += "</li><li><p></p><label>xCode: </label><input name='k' length=32><input type='submit' value='Set'><p></p>Current xCode: ";
  content += xCode;
  content += "</li><li><p></p><label>xdefTIMspeedB: </label><input name='l' type='submit' value='True'><input name='l' type='submit' value='False'><p></p>Current xdefTIMspeedB: ";
  content += xdefTIMspeedB;
  content += "</li><li><p></p><label>xdefPWMspeedB: </label><input name='m' type='submit' value='True'><input name='m' type='submit' value='False'><p></p>Current xdefPWMspeedB: ";
  content += xdefPWMspeedB;
  content += "</li><li><p></p><label>xRotateRoborochProgB: </label><input name='n' type='submit' value='True'><input name='n' type='submit' value='False'><p></p>Current xRotateRoborochProgB: ";
  content += xRotateRoborochProgB;
  content += "</li></ol></p><p></p></form>";
  content += "<p style='text-align: center;'><em>DEVELOPED BY " + DevName + "<br></em></p><p style=\"text-align: center;\"><em>" + DevAddr + "<br></em></p>";
  content += "</html>";
}


void InitEEPROM()
{
  yield();
  GetEEP();
  int Totall = xTOTAL;
  int YYY = xCode;
  if (YYY == 127)
  {
    Totall++;
    xTOTAL = Totall;
    NavDeggree = xNavDeggree;
    TPperDEG = xTPperDEG;
    defPWMspeed = xdefPWMspeed;
    defPWMspeedB = xdefPWMspeedB;
    defTIMspeed = xdefTIMspeed;
    defTIMspeedB = xdefTIMspeedB;
    RotateRoborochProgB = xRotateRoborochProgB;
    RotateRoborochDeg = xRotateRoborochDeg;
    RotateRoborochDegTol = xRotateRoborochDegTol;
    RotateRoborochDegDef = xRotateRoborochDegDef;
    PosM = xPosM;
    NegM = xNegM;
    EEPROM.put(100, xTOTAL);
    EEPROM.commit();
  }
  else if (YYY != 127)
  {
    xTOTAL = 1;
    xCode = 127;
    xNavDeggree = NavDeggree;
    xTPperDEG = TPperDEG;///////////////////////Required (Time * PWM) to rotate 1 degree
    xdefPWMspeed = defPWMspeed;////////////////////Default PWM to rotate
    xdefPWMspeedB = defPWMspeedB;////////////////Based on PWM
    xdefTIMspeed = defTIMspeed;////////////////////Default TIME to rotate
    xdefTIMspeedB = defTIMspeedB;///////////////Based on TIM
    xRotateRoborochProgB = RotateRoborochProgB;////////indicates Roboroch Rotation progress status
    xRotateRoborochDeg = RotateRoborochDeg;//////////////indicates Roboroch Rotation Default Degree
    xRotateRoborochDegTol = RotateRoborochDegTol;///////////Degree tolerance
    xRotateRoborochDegDef = RotateRoborochDegDef;//////////in rotation, nav degree will be  this number
    xPosM = PosM;
    xNegM = NegM;
    SetEEP();
  }
}


void GetEEP()
{
  int SS = sizeof(int);
  int BB = sizeof(bool);
  EEPROM.get(100, xTOTAL);
  EEPROM.get(100 + (1 * SS), xNavDeggree);
  EEPROM.get(100 + (2 * SS), xTPperDEG);
  EEPROM.get(100 + (3 * SS), xdefPWMspeed);
  EEPROM.get(100 + (4 * SS), xdefTIMspeed);
  EEPROM.get(100 + (5 * SS), xRotateRoborochDeg);
  EEPROM.get(100 + (6 * SS), xRotateRoborochDegTol);
  EEPROM.get(100 + (7 * SS), xRotateRoborochDegDef);
  EEPROM.get(100 + (8 * SS), xPosM);
  EEPROM.get(100 + (9 * SS), xNegM);
  EEPROM.get(100 + (10 * SS), xCode);
  EEPROM.get(100 + (11 * SS), xdefTIMspeedB);
  EEPROM.get(100 + (11 * SS) + BB, xdefPWMspeedB);
  EEPROM.get(100 + (11 * SS) + BB + BB, xRotateRoborochProgB);
}


void SetEEP()
{
  int SS = sizeof(int);
  int BB = sizeof(bool);
  EEPROM.put(100, xTOTAL);
  EEPROM.put(100 + (1 * SS), xNavDeggree);
  EEPROM.put(100 + (2 * SS), xTPperDEG);
  EEPROM.put(100 + (3 * SS), xdefPWMspeed);
  EEPROM.put(100 + (4 * SS), xdefTIMspeed);
  EEPROM.put(100 + (5 * SS), xRotateRoborochDeg);
  EEPROM.put(100 + (6 * SS), xRotateRoborochDegTol);
  EEPROM.put(100 + (7 * SS), xRotateRoborochDegDef);
  EEPROM.put(100 + (8 * SS), xPosM);
  EEPROM.put(100 + (9 * SS), xNegM);
  EEPROM.put(100 + (10 * SS), xCode);
  EEPROM.put(100 + (11 * SS), xdefTIMspeedB);
  EEPROM.put(100 + (11 * SS) + BB, xdefPWMspeedB);
  EEPROM.put(100 + (11 * SS) + BB + BB, xRotateRoborochProgB);
  EEPROM.commit();
}


void SelEEP()
{
  int SS = sizeof(int);
  int BB = sizeof(bool);
  EEPROM.put(100, 0);
  EEPROM.put(100 + (1 * SS), 0);
  EEPROM.put(100 + (2 * SS), 0);
  EEPROM.put(100 + (3 * SS), 0);
  EEPROM.put(100 + (4 * SS), 0);
  EEPROM.put(100 + (5 * SS), 0);
  EEPROM.put(100 + (6 * SS), 0);
  EEPROM.put(100 + (7 * SS), 0);
  EEPROM.put(100 + (8 * SS), 0);
  EEPROM.put(100 + (9 * SS), 0);
  EEPROM.put(100 + (10 * SS), 127);
  EEPROM.put(100 + (11 * SS), 0);
  EEPROM.put(100 + (11 * SS) + BB, 0);
  EEPROM.put(100 + (11 * SS) + BB + BB, 0);
  EEPROM.commit();
}


void LEDC(int PINnum, int Con)
{
  switch (PINnum)
  {
    case 0:
      if (Con == 0)
      {
        digitalWrite(4, HIGH); lc0 = false;
      }
      else if (Con == 1)
      {
        digitalWrite(4, LOW); lc0 = true;
      }
      else if (Con == 2)
      {
        if (lc0)
        {
          digitalWrite(4, HIGH); lc0 = false;
        }
        else
        {
          digitalWrite(4, LOW); lc0 = true;
        }
      }
      break;
    case 1:
      if (Con == 0)
      {
        digitalWrite(5, HIGH); lc1 = false;
      }
      else if (Con == 1)
      {
        digitalWrite(5, LOW); lc1 = true;
      }
      else if (Con == 2)
      {
        if (lc1)
        {
          digitalWrite(5, HIGH); lc1 = false;
        }
        else
        {
          digitalWrite(5, LOW); lc1 = true;
        }
      }
      break;
    case 2:
      if (Con == 0)
      {
        digitalWrite(14, HIGH); lc2 = false;
      }
      else if (Con == 1)
      {
        digitalWrite(14, LOW); lc2 = true;
      }
      else if (Con == 2)
      {
        if (lc2)
        {
          digitalWrite(14, HIGH); lc2 = false;
        }
        else
        {
          digitalWrite(14, LOW); lc2 = true;
        }
      }
      break;
    case 3:
      if (Con == 0)
      {
        digitalWrite(16, HIGH); lc3 = false;
      }
      else if (Con == 1)
      {
        digitalWrite(16, LOW); lc3 = true;
      }
      else if (Con == 2)
      {
        if (lc3)
        {
          digitalWrite(16, HIGH); lc3 = false;
        }
        else
        {
          digitalWrite(16, LOW); lc3 = true;
        }
      }
      break;
  }
}


void UpdEEP()
{
  NavDeggree = xNavDeggree;
  TPperDEG = xTPperDEG;
  defPWMspeed = xdefPWMspeed;
  defPWMspeedB = xdefPWMspeedB;
  defTIMspeed = xdefTIMspeed;
  defTIMspeedB = xdefTIMspeedB;
  RotateRoborochProgB = xRotateRoborochProgB;
  RotateRoborochDeg = xRotateRoborochDeg;
  RotateRoborochDegTol = xRotateRoborochDegTol;
  RotateRoborochDegDef = xRotateRoborochDegDef;
  PosM = xPosM;
  NegM = xNegM;
}
