#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Wire.h>

int YPR[3];                                 //gy953 yaw pitch roll buffer
unsigned char Re_buf[11], counter = 0;      //main buffer of gy953
unsigned char sign = 0;                     //releative
bool EnableP = true;

struct Alpha
{
  int TOTAL;
  int NavDeggree;
  int TPperDEG;
  int defPWMspeed;
  int defTIMspeed;
  int RotateRoborochDeg;
  int RotateRoborochDegTol;
  int RotateRoborochDegDef;
  int PosM;
  int NegM;
  int Code;
  bool defTIMspeedB;
  bool defPWMspeedB;
  bool RotateRoborochProgB;
};


ESP8266WebServer server(80);


const char* ssid = "ESP8266_ROBOROCH_AP";
const char* passphrase = "ed4a7f13";
String st;
String content;
String DevName = "MAHDI NAJI";
String DevAddr = "@TNEGABSU";
int statusCode;
int gy99 = 1;


//////////////////////////////////////////////////Roboroch
int Deggree = 0;
int NavDeggree = 90;
int TPperDEG = 1;///////////////////////Required (Time * PWM) to rotate 1 degree
int defPWMspeed = 1;////////////////////Default PWM to rotate
bool defPWMspeedB = true;///////////////Based on PWM
int defTIMspeed = 1;////////////////////Default TIME to rotate
int defTIMspeedB = false;///////////////Based on TIM
bool RotateRoborochProgB = false;///////indicates Roboroch Rotation progress status
int RotateRoborochDeg = 0;//////////////indicates Roboroch Rotation Default Degree
int RotateRoborochDegTol = 5;///////////Degree tolerance
int RotateRoborochDegDef = 30;//////////in rotation, nav degree will be  this number
//Pinouts
int PosM = 10, NegM = 11;////////////////////////////////////////////////////////////////////////////////////////Driver pins OUTPUT

bool RoboStable = false;
//////////////////////////////////////////////////
int Totall = 0;


void setup() {
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


void launchWeb(int webtype) {
  createWebServer(webtype);
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
  launchWeb(1);
}


void createWebServer(int webtype)
{
  if ( webtype == 1 )
  { server.on("/", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      SetContentRoot(ipStr);
      server.send(200, "text/html", content);
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
        //yield();
        SetNavDegree(uuuu);
        //yield();
        SetNavDegree(Cuu);
        //yield();
      }
      if (qc != "")
      {
        int uu = qc.toInt();
        //yield();
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


    server.on("/GYInfo", []() {
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

    server.on("/Inf", []() {
      String Q = "";
      Q += ssid;
      Q += "{{}}";
      Q += passphrase;
      server.send(200, "text/html", Q);
    });

    server.on("/s", []() {
      server.send(200, "text/html", ssid);
    });

    server.on("/p", []() {
      server.send(200, "text/html", passphrase);
    });

    server.on("/EEPROM", []() {
      String DC = "<!DOCTYPE HTML><html>EEPROM information {ROBOROCH} (Device running on ESP8266-07) ";
      DC += "<p></p>";
      Alpha SetingEEPROM5;
      EEPROM.get(100, SetingEEPROM5);
      DC += "<p>ESSID:</p><p>";
      DC += ssid;
      DC += "</p><p></p><p>EPASS:</p><p>";
      DC += passphrase;
      DC += "</p><p></p><p>TOTAL:</p><p>";
      DC += SetingEEPROM5.TOTAL;
      DC += "</p><p></p><p>NavDeggree:</p><p>";
      DC += SetingEEPROM5.NavDeggree;
      DC += "</p><p></p><p>TPperDEG:</p><p>";
      DC += SetingEEPROM5.TPperDEG;
      DC += "</p><p></p><p>defPWMspeed:</p><p>";
      DC += SetingEEPROM5.defPWMspeed;
      DC += "</p><p></p><p>defPWMspeedB:</p><p>";
      DC += SetingEEPROM5.defPWMspeedB;
      DC += "</p><p></p><p>defTIMspeed:</p><p>";
      DC += SetingEEPROM5.defTIMspeed;
      DC += "</p><p></p><p>defTIMspeedB:</p><p>";
      DC += SetingEEPROM5.defTIMspeedB;
      DC += "</p><p></p><p>RotateRoborochProgB:</p><p>";
      DC += SetingEEPROM5.RotateRoborochProgB;
      DC += "</p><p></p><p>RotateRoborochDeg:</p><p>";
      DC += SetingEEPROM5.RotateRoborochDeg;
      DC += "</p><p></p><p>RotateRoborochDegTol:</p><p>";
      DC += SetingEEPROM5.RotateRoborochDegTol;
      DC += "</p><p></p><p>RotateRoborochDegDef:</p><p>";
      DC += SetingEEPROM5.RotateRoborochDegDef;
      DC += "</p><p></p><p>Code:</p><p>";
      DC += SetingEEPROM5.Code;
      DC += "</p><p></p><p>PosM:</p><p>";
      DC += SetingEEPROM5.PosM;
      DC += "</p><p></p><p>NegM:</p><p>";
      DC += SetingEEPROM5.NegM;
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
      { /*
          Alpha Y;
          EEPROM.put(100, Y);*/
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
      String Ty = "Request Delivered\n\nGY-953 Status:\t";
      Ty += gy99;
      server.send(statusCode, "text/html", Ty);
    });
  }
  else if (webtype == 0)
  {
    server.on("/", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      server.send(200, "text/html", ipStr);
    });
  }
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
    ////Codes:
    int DeggToRotateRoboroch = Deggree - RotateRoborochDeg;
    int QQQQ = DeggToRotateRoboroch;
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
      if (QQQQ < RotateRoborochDegTol)
      {
        if (!RoboStable)
          RotateRoborochProgB = false;
      }
      else
      {
        SetNavDegree(QQQQ);
      }
    }
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
/*
   100 no diffrence between degg and navdeg
   101 successful
   102 error on pwm or time default bool
   103 degg < 0
   104 degg > 180
*/
{
  if (Degg < 0)
    return 103;
  if (Degg > 180)
    return 104;
  int DiffDeg = Degg - NavDeggree;
  if (DiffDeg == 0)
    return 100;
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
    //yield();
    analogWrite(MotorPin, defPWMspeed);
    delay(TimeToRotate);
    analogWrite(MotorPin, 0);
    //yield();
    NavDeggree = Degg;
    return 101;
  }
  else if (defTIMspeedB)
  {
    int PwmToRotate = ReqTB / defTIMspeed;
    //yield();
    analogWrite(MotorPin, PwmToRotate);
    delay(defTIMspeed);
    analogWrite(MotorPin, 0);
    //yield();
    NavDeggree = Degg;
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


void InitEEPROM()
{
  yield();
  Alpha SetingEEPROMq;
  EEPROM.get(100, SetingEEPROMq);
  int Totall = SetingEEPROMq.TOTAL;
  int YYY = SetingEEPROMq.Code;
  if (YYY != 127)
  {
    Alpha SetingEEPROMq;
    Totall++;
    SetingEEPROMq.TOTAL = Totall;
    NavDeggree = SetingEEPROMq.NavDeggree;
    TPperDEG = SetingEEPROMq.TPperDEG;
    defPWMspeed = SetingEEPROMq.defPWMspeed;
    defPWMspeedB = SetingEEPROMq.defPWMspeedB;
    defTIMspeed = SetingEEPROMq.defTIMspeed;
    defTIMspeedB = SetingEEPROMq.defTIMspeedB;
    RotateRoborochProgB = SetingEEPROMq.RotateRoborochProgB;
    RotateRoborochDeg = SetingEEPROMq.RotateRoborochDeg;
    RotateRoborochDegTol = SetingEEPROMq.RotateRoborochDegTol;
    RotateRoborochDegDef = SetingEEPROMq.RotateRoborochDegDef;
    PosM = SetingEEPROMq.PosM;
    NegM = SetingEEPROMq.NegM;
    EEPROM.put(100, SetingEEPROMq);
    EEPROM.commit();
  }
  else if (YYY != 127)
  {
    Alpha SetingEEPROM;
    SetingEEPROM.TOTAL = 1;
    SetingEEPROM.Code = 127;
    SetingEEPROM.NavDeggree = NavDeggree;
    SetingEEPROM.TPperDEG = TPperDEG;///////////////////////Required (Time * PWM) to rotate 1 degree
    SetingEEPROM.defPWMspeed = defPWMspeed;////////////////////Default PWM to rotate
    SetingEEPROM.defPWMspeedB = defPWMspeedB;////////////////Based on PWM
    SetingEEPROM.defTIMspeed = defTIMspeed;////////////////////Default TIME to rotate
    SetingEEPROM.defTIMspeedB = defTIMspeedB;///////////////Based on TIM
    SetingEEPROM.RotateRoborochProgB = RotateRoborochProgB;////////indicates Roboroch Rotation progress status
    SetingEEPROM.RotateRoborochDeg = RotateRoborochDeg;//////////////indicates Roboroch Rotation Default Degree
    SetingEEPROM.RotateRoborochDegTol = RotateRoborochDegTol;///////////Degree tolerance
    SetingEEPROM.RotateRoborochDegDef = RotateRoborochDegDef;//////////in rotation, nav degree will be  this number
    SetingEEPROM.PosM = PosM;
    SetingEEPROM.NegM = NegM;
    EEPROM.put(100, SetingEEPROM);
    EEPROM.commit();
  }
}
