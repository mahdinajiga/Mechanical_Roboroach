#include <ESP8266WiFi.h>


const char* ssid = "ESP_8266";
const char* password = "eeeeeeee";


WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();
  while (!client.available()) {
    ;
  }


  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  int q = request.length();
  request.remove(q - 9, 9);
  if (request != "favicon.ico")
  {
    if (request != "")
    {
      Serial.println(request);
    }
  }
  client.flush();

  if (Serial.available() > 0)
  {
    String T = Serial.readString();
    client.print(T);
  }
  else
  {
    client.print("EEE");
  }


}
