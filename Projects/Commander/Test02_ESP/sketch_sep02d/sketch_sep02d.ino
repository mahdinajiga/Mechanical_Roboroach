#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

ESP8266WebServer server(80);

const char* ssid = "ESP8266_AP";
const char* passphrase = "ed4a7f13";
String st;
String content;
String DevName = "MAHDI NAJI";
String DevAddr = "@TNEGABSU";
int statusCode;
String N01 = "On", N02 = "On", N03 = "On", N04 = "On", N05 = "BothUp", N06 = "Up", N07 = "Up", N08 = "Drop", N09 = "Drop", N10 = "On", N15 = "AllOn", N11 = "On", N12 = "On", N13 = "Spray", N14 = "Spray";
String Maasg = "No Message Recieved...";

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
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
    ssid=esid.c_str();
    passphrase=epass.c_str();
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
      String qf = server.arg("f");
      String qg = server.arg("g");
      String qh = server.arg("h");
      String qi = server.arg("i");
      String qj = server.arg("j");
      String qk = server.arg("k");
      String ql = server.arg("l");
      String qm = server.arg("m");
      String qn = server.arg("DvNm");
      String qo = server.arg("DvAd");
      if (qn != "")
        DevName = qn;
      if (qo != "")
        DevAddr = qo;
      if (qa == "On") {
        Serial.print("a1");
        N01 = "Off";
      } else if (qa == "Off") {
        Serial.print("a0");
        N01 = "On";
      }
      if (qb == "On") {
        Serial.print("b1");
        N02 = "Off";
      } else if (qb == "Off") {
        Serial.print("b0");
        N02 = "On";
      }
      if (qc == "On") {
        Serial.print("c1");
        N03 = "Off";
      } else if (qc == "Off") {
        Serial.print("c0");
        N03 = "On";
      }
      if (qd == "On") {
        Serial.print("d1");
        N04 = "Off";
      } else if (qd == "Off") {
        Serial.print("d0");
        N04 = "On";
      }
      if (qe == "Up") {
        Serial.print("e1");
        N06 = "Down";
      } else if (qe == "Down") {
        Serial.print("e0");
        N06 = "Up";
      } else if (qe == "BothUp") {
        Serial.print("e4");
        N05 = "BothDown";
        N06 = "Down";
        N07 = "Down";
      } else if (qe == "BothDown") {
        Serial.print("e3");
        N05 = "BothUp";
        N06 = "Up";
        N07 = "Up";
      }
      if (qf == "Up") {
        Serial.print("f1");
        N07 = "Down";
      } else if (qf == "Down") {
        Serial.print("f0");
        N07 = "Up";
      }
      if (qg == "Drop") {
        Serial.print("g1");
      }
      if (qh == "Drop") {
        Serial.print("h1");
      }
      if (qi == "On") {
        Serial.print("i1");
        N10 = "Off";
      } else if (qi == "Off") {
        Serial.print("i0");
        N10 = "On";
      } else if (qi == "AllOn")
      {
        Serial.print("i4");
        N15 = "AllOff";
        N10 = "Off";
        N11 = "Off";
        N12 = "Off";
      } else if (qi == "AllOff")
      {
        Serial.print("i3");
        N15 = "AllOn";
        N10 = "On";
        N11 = "On";
        N12 = "On";
      }
      if (qj == "On") {
        Serial.print("j1");
        N11 = "Off";
      } else if (qj == "Off") {
        Serial.print("j0");
        N11 = "On";
      }
      if (qk == "On") {
        Serial.print("k1");
        N12 = "Off";
      } else if (qk == "Off") {
        Serial.print("k0");
        N12 = "On";
      }
      if (ql == "Spray") {
        Serial.print("l1");
      }
      if (qm == "Spray") {
        Serial.print("m1");
      }
      SetContentRoot(ipStr);
      server.send(statusCode, "text/html", content);
    });




    server.on("/cleareeprom", []() {
      content = "<!DOCTYPE HTML><html>";
      content += "<p>Clearing the EEPROM...</p></html>";
      server.send(200, "text/html", content);
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
    });


    
    server.on("/admin", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML><html>Welcome to ADMINISTRATION UNIT... ";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><label>PASS: </label><input name='pass' length=64><input type='submit' value='Set'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      String qC = server.arg("passcode");
      content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
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
          content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi(ADMIN)\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
        }
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

    server.on("/admin", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML><html>Welcome to ADMINISTRATION UNIT... ";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><label>PASS: </label><input name='pass' length=64><input type='submit' value='Set'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      String qC = server.arg("passcode");
      content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
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
          content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi(ADMIN)\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
        }
      }
      server.send(statusCode, "application/json", content);
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
      String qg = server.arg("g");
      String qh = server.arg("h");
      String qi = server.arg("i");
      String qj = server.arg("j");
      String qk = server.arg("k");
      String ql = server.arg("l");
      String qm = server.arg("m");
      String qn = server.arg("DvNm");
      String qo = server.arg("DvAd");
      if (qn != "")
        DevName = qn;
      if (qo != "")
        DevAddr = qo;
      if (qa == "On") {
        Serial.print("a1");
        N01 = "Off";
      } else if (qa == "Off") {
        Serial.print("a0");
        N01 = "On";
      }
      if (qb == "On") {
        Serial.print("b1");
        N02 = "Off";
      } else if (qb == "Off") {
        Serial.print("b0");
        N02 = "On";
      }
      if (qc == "On") {
        Serial.print("c1");
        N03 = "Off";
      } else if (qc == "Off") {
        Serial.print("c0");
        N03 = "On";
      }
      if (qd == "On") {
        Serial.print("d1");
        N04 = "Off";
      } else if (qd == "Off") {
        Serial.print("d0");
        N04 = "On";
      }
      if (qe == "Up") {
        Serial.print("e1");
        N06 = "Down";
      } else if (qe == "Down") {
        Serial.print("e0");
        N06 = "Up";
      } else if (qe == "BothUp") {
        Serial.print("e4");
        N05 = "BothDown";
        N06 = "Down";
        N07 = "Down";
      } else if (qe == "BothDown") {
        Serial.print("e3");
        N05 = "BothUp";
        N06 = "Up";
        N07 = "Up";
      }
      if (qf == "Up") {
        Serial.print("f1");
        N07 = "Down";
      } else if (qf == "Down") {
        Serial.print("f0");
        N07 = "Up";
      }
      if (qg == "Drop") {
        Serial.print("g1");
      }
      if (qh == "Drop") {
        Serial.print("h1");
      }
      if (qi == "On") {
        Serial.print("i1");
        N10 = "Off";
      } else if (qi == "Off") {
        Serial.print("i0");
        N10 = "On";
      } else if (qi == "AllOn")
      {
        Serial.print("i4");
        N15 = "AllOff";
        N10 = "Off";
        N11 = "Off";
        N12 = "Off";
      } else if (qi == "AllOff")
      {
        Serial.print("i3");
        N15 = "AllOn";
        N10 = "On";
        N11 = "On";
        N12 = "On";
      }
      if (qj == "On") {
        Serial.print("j1");
        N11 = "Off";
      } else if (qj == "Off") {
        Serial.print("j0");
        N11 = "On";
      }
      if (qk == "On") {
        Serial.print("k1");
        N12 = "Off";
      } else if (qk == "Off") {
        Serial.print("k0");
        N12 = "On";
      }
      if (ql == "Spray") {
        Serial.print("l1");
      }
      if (qm == "Spray") {
        Serial.print("m1");
      }
      SetContentRoot(ipStr);
      server.send(statusCode, "text/html", content);
    });




    server.on("/cleareeprom", []() {
      content = "<!DOCTYPE HTML><html>";
      content += "<p>Clearing the EEPROM...</p></html>";
      server.send(200, "text/html", content);
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
    });
  }
}

void loop() {
  if (Serial.available() > 0)
  {
    if (Maasg == "No Message Recieved...")
      Maasg = "";
    Maasg += Serial.readString();
    Maasg += "/////";
  }
  server.handleClient();
}

void SetContentRoot(String ipStrr)
{
  content = "<!DOCTYPE HTML><html>Hello from NEW FOLDER grp (Device running on ESP8266 - 07 at ";
  content += ipStrr;
  content += ")<form method = 'get' action = 'order'><p><ol>";
  content += "<li><p></p><label>Fan_Left_Output<p></p></label><input type='submit' name='a' value='" + N01 + "'></li>";
  content += "<li><p></p><label>Fan_Left_Input<p></p></label><input type='submit' name='b' value='" + N02 + "'></li>";
  content += "<li><p></p><label>Fan_Right_Output<p></p></label><input type='submit' name='c' value='" + N03 + "'></li>";
  content += "<li><p></p><label>Fan_Right_Input<p></p></label><input type='submit' name='d' value='" + N04 + "'></li>";
  content += "<li><p></p><label>Door_Both<p></p></label><input type='submit' name='e' value='" + N05 + "'></li>";
  content += "<li><p></p><label>Door_Right<p></p></label><input type='submit' name='e' value='" + N06 + "'></li>";
  content += "<li><p></p><label>Door_Left<p></p></label><input type='submit' name='f' value='" + N07 + "'></li>";
  content += "<li><p></p><label>Drop_Right<p></p></label><input type='submit' name='g' value='" + N08 + "'></li>";
  content += "<li><p></p><label>Drop_Left<p></p></label><input type='submit' name='h' value='" + N09 + "'></li>";
  content += "<li><p></p><label>Light_Right<p></p></label><input type='submit' name='i' value='" + N10 + "'><input type='submit' name='i' value='" + N15 + "'></li>";
  content += "<li><p></p><label>Light_Middle<p></p></label><input type='submit' name='j' value='" + N11 + "'></li>";
  content += "<li><p></p><label>Light_Left<p></p></label><input type='submit' name='k' value='" + N12 + "'></li>";
  content += "<li><p></p><label>Spray_Right<p></p></label><input type='submit' name='l' value='" + N13 + "'></li>";
  content += "<li><p></p><label>Spray_Left<p></p></label><input type='submit' name='m' value='" + N14 + "'></li>";
  content += "</ol></p></form><p>--------------------------------------------------------------------------</p><p>Arduino Message: </p>";
  content += Maasg;
  content += "<p>--------------------------------------------------------------------------</p><p>PNIOUTS:</p><p><ol>";
  content += "<li>A :::::::::::: Fan_Left_Output :::::::::::: 0/1:::PIN22</li>";
  content += "<li>B :::::::::::: Fan_Left_Input :::::::::::: 0/1:::PIN23</li>";
  content += "<li>C :::::::::::: Fan_Right_Output :::::::::::: 0/1:::PIN24</li>";
  content += "<li>D :::::::::::: Fan_Right_Input :::::::::::: 0/1::: PIN25</li>";
  content += "<li>E :::::::::::: Door_Both :::::::::::: ***</li>";
  content += "<li>E :::::::::::: Door_Right :::::::::::: e0:::PIN26  |  e1:::PIN27  |  e0MS:::PIN28  |  e1MS:::PIN29</li>";
  content += "<li>F :::::::::::: Door_Left :::::::::::: f0:::PIN30  |  f1:::PIN31  |  f0MS:::PIN32  |  f1MS:::PIN33</li>";
  content += "<li>G :::::::::::: Drop_Right :::::::::::: g0:::PIN34  |  g1:::PIN35  |  g0MS:::PIN36  |  g1MS:::PIN37</li>";
  content += "<li>H :::::::::::: Drop_Left :::::::::::: h0:::PIN38  |  h1:::PIN39  |  h0MS:::PIN40  |  h1MS:::PIN41</li>";
  content += "<li>I :::::::::::: Light_Right :::::::::::: 0/1:::PIN42</li>";
  content += "<li>J :::::::::::: Light_Middle :::::::::::: 0/1:::PIN43</li>";
  content += "<li>K :::::::::::: Light_Left :::::::::::: 0/1:::PIN44 < / li > ";
  content += "<li>L :::::::::::: Spray_Right :::::::::::: l0:::PIN45  |  l1:::PIN46</li>";
  content += "<li>M :::::::::::: Spray_Left :::::::::::: m0:::PIN47  |  m1:::PIN48</li></ol></p>";
  content += "<p style='text-align: center;'><em>DEVELOPED BY " + DevName + "<br></em></p><p style=\"text-align: center;\"><em>" + DevAddr + "<br></em></p>";
  content += "</html>";
}

