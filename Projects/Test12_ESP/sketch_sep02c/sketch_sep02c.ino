#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Servo.h>


Servo myservo;

ESP8266WebServer server(80);

const char* ssid = "ESP8266_AP";
const char* passphrase = "ed4a7f13";
String st;
String content;
String DevName = "MAHDI NAJI";
String DevAddr = "@TNEGABSU";
int statusCode;
int Deggree = 90;
int DefDeg = 90;
bool Def = false;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  myservo.attach(14);
  myservo.write(Deggree);
  delay(10);
  // read eeprom for ssid and pass
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
    WiFi.begin(esid.c_str(), epass.c_str());
    if (testWifi()) {
      launchWeb(0);
      return;
    }
  }
  setupAP();
}

bool testWifi(void) {
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) {
      return true;
    }
    delay(500);
    c++;
  }
  return false;
}

void launchWeb(int webtype) {
  createWebServer(webtype);
  // Start the server
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
  WiFi.softAP(ssid, passphrase, 6);///////////////////////////////////////////////////////////////////////////////////////////////////////////WiFi Channel
  launchWeb(1);
}

void createWebServer(int webtype)
{
  if ( webtype == 1 )
  {
    server.on("/", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML><html>Hello from NEW FOLDER grp {ROBOROCH} (Device running on ESP8266-07) ";
      content += ipStr;
      content += "<p>";
      content += st;
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
      server.send(200, "text/html", content);
    });
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
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
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
      }
      server.send(statusCode, "application/json", content);
    });
  }
  else if (webtype == 0)
  {
    server.on("/", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      SetContentRoot(ipStr);
      server.send(200, "text/html", content);
    });




    server.on("/order", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      String qa = server.arg("a");
      String qb = server.arg("b");
      String qc = server.arg("c");
      String qd = server.arg("d");
      String qe = server.arg("e");
      String qf = server.arg("f");
      String qn = server.arg("DvNm");
      String qo = server.arg("DvAd");
      if (qn != "")
        DevName = qn;
      if (qo != "")
        DevAddr = qo;
      if (qa != "")
      {
        myservo.write(qa.toInt());
      }
      else if (qb != "")
      {
        int U = Deggree;
        myservo.write(qb.toInt());
        delay(250);
        myservo.write(U);
      }
      else if (qc != "")
      {
        Def = (qc == "1") ? true : false;
      }
      else if (qd != "")
      {
        DefDeg = qd.toInt();
      }
      else if (qe != "")
      {
        if (qf == "p5")
        {
          myservo.write(Deggree + 5);
        } else if (qf == "p10")
        {
          myservo.write(Deggree + 10);
        } else if (qf == "p20")
        {
          myservo.write(Deggree + 20);
        } else if (qf == "p30")
        {
          myservo.write(Deggree + 30);
        } else if (qf == "n5")
        {
          myservo.write(Deggree - 5);
        } else if (qf == "n10")
        {
          myservo.write(Deggree - 10);
        } else if (qf == "n20")
        {
          myservo.write(Deggree - 20);
        } else if (qf == "n30")
        {
          myservo.write(Deggree - 30);
        }
      }
      else if (qf != "")
      {
        if (qf == "p5")
        {
          int U = Deggree;
          myservo.write(U + 5);
          delay(250);
          myservo.write(U);
        } else if (qf == "p10")
        {
          int U = Deggree;
          myservo.write(U + 10);
          delay(250);
          myservo.write(U);
        } else if (qf == "p20")
        {
          int U = Deggree;
          myservo.write(U + 20);
          delay(250);
          myservo.write(U);
        } else if (qf == "p30")
        {
          int U = Deggree;
          myservo.write(U + 30);
          delay(250);
          myservo.write(U);
        } else if (qf == "n5")
        {
          int U = Deggree;
          myservo.write(U - 5);
          delay(250);
          myservo.write(U);
        } else if (qf == "n10")
        {
          int U = Deggree;
          myservo.write(U - 10);
          delay(250);
          myservo.write(U);
        } else if (qf == "n20")
        {
          int U = Deggree;
          myservo.write(U - 20);
          delay(250);
          myservo.write(U);
        } else if (qf == "n30")
        {
          int U = Deggree;
          myservo.write(U - 30);
          delay(250);
          myservo.write(U);
        }
      }
      SetContentRoot(ipStr);
      server.send(statusCode, "text/html", content);
    });




    server.on(" / cleareeprom", []() {
      content = " <!DOCTYPE HTML> <html>";
      content += "<p>Clearing the EEPROM... </p> </html>";
      server.send(200, "text/html", content);
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
    });
  }
}

void loop() {
  if (Def)
  {
    if (Deggree != DefDeg)
    {
      delay(500);
      myservo.write(DefDeg);
    }
  }
  Deggree = myservo.read();
  server.handleClient();
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
  content += Deggree;
  content += "</p><p>Def:</p><p>";
  content += Def;
  content += "</p><p>DefDeg:</p><p>";
  content += DefDeg;
  content += "</p><p>---------------------------------------------------------------------------</p>";
  content += "<p style='text-align: center;'><em>DEVELOPED BY " + DevName + "<br></em></p><p style=\"text-align: center;\"><em>" + DevAddr + "<br></em></p>";
  content += "</html>";
}

