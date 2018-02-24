#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//GY953
#include <Wire.h>
int YPR[3];
unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;
bool EnableP = false;


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
int PosM = 10, NegM = 11;
//////////////////////////////////////////////////



void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
  ///////////////////////////////////// read eeprom for ssid and pass
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
  if ( esid.length() > 1 ) {
    ssid = esid.c_str();
    passphrase = epass.c_str();
    //////////////////////////////////////initiating GY953
    Serial.write(0XA5);
    Serial.write(0X45);
    Serial.write(0XEA);
    //////////////////////////////////////initiating AccessPoint
    setupAP();
  }
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
      String qn = server.arg("DvNm");
      String qo = server.arg("DvAd");
      if (qn != "")
        DevName = qn;
      if (qo != "")
        DevAddr = qo;

      SetContentRoot(ipStr);
      server.send(statusCode, "text/html", content);
    });


    server.on("/DeviceInfo", []() {
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
      content = "{\"Error\":\"404 not found\"}";
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
          content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi{ADMIN}\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
        }
      }
      server.send(statusCode, "application/json", content);
    });


    server.on("/cleareeprom", []() {
      content = " <!DOCTYPE HTML> <html>";
      content += "<p>Clearing the EEPROM... </p> </html>";
      server.send(200, "text/html", content);
      if (EnableP)
      {
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
    if (DeggToRotateRoboroch < 0)
      DeggToRotateRoboroch = DeggToRotateRoboroch * (-1);
    if (DeggToRotateRoboroch > RotateRoborochDegDef)
    {
      SetNavDegree(RotateRoborochDegDef);
    }
    else
    {
      SetNavDegree(QQQQ);
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
    analogWrite(MotorPin, defPWMspeed);
    delay(TimeToRotate);
    analogWrite(MotorPin, 0);
    Deggree = Degg;
    return 101;
  }
  else if (defTIMspeedB)
  {
    int PwmToRotate = ReqTB / defTIMspeed;
    analogWrite(MotorPin, PwmToRotate);
    delay(defTIMspeed);
    analogWrite(MotorPin, 0);
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
  content += "<li><p></p><label>SetDegree: </label><input name='a' length=32><input type='submit' value='Set'><p></p><input type='submit' name='e' value='n30'><input type='submit' name='e' value='n20'><input type='submit' name='e' value='n10'><input type='submit' name='e' value='n5'><input type='submit' name='e' value='p5'><input type='submit' name='e' value='p10'><input type='submit' name='e' value='p20'><input type='submit' name='e' value='p30'></li>";
  content += "<li><p></p><label>SetDegree and return: </label><input name='b' length=32><input type='submit' value='Set'><p></p><input type='submit' name='f' value='n30'><input type='submit' name='f' value='n20'><input type='submit' name='f' value='n10'><input type='submit' name='f' value='n5'><input type='submit' name='f' value='p5'><input type='submit' name='f' value='p10'><input type='submit' name='f' value='p20'><input type='submit' name='f' value='p30'></li>";
  content += "<li><p></p><label>Def: </label><input type='submit' name='c' value='0'><input type='submit' name='c' value='1'><p></p></li>";
  content += "<li><p></p><label>SetDefDeg: </label><input name='d' length=32><input type='submit' value='Set'></li></ol></p><p></p></form>";
  /*
    content += "<li><p></p><label>Fan_Right_Output<p></p></label><input type='submit' name='c' value='" + "'></li>";
    content += "<li><p></p><label>Fan_Right_Input<p></p></label><input type='submit' name='d' value='" + "'></li>";
    content += "<li><p></p><label>Door_Right<p></p></label><input type='submit' name='e' value='" + "'></li>";
    content += "<li><p></p><label>Door_Left<p></p></label><input type='submit' name='f' value='" + "'></li>";*/
  content += "<p>---------------------------------------------------------------------------</p>";
  content += "<p>Current Degree:</p><p>";
  content += "Deggree";
  content += "</p><p>Def:</p><p>";
  content += "Def";
  content += "</p><p>DefDeg:</p><p>";
  content += "DefDeg";
  content += "</p><p>---------------------------------------------------------------------------</p>";
  content += "<p style='text-align: center;'><em>DEVELOPED BY " + DevName + "<br></em></p><p style=\"text-align: center;\"><em>" + DevAddr + "<br></em></p>";
  content += "</html>";
}
