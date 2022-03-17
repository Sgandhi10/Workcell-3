#include <WiFiNINA.h>

#define sensorPin A5

char ssid[] = "Test";
char pass[] = "12345678";

int status = WL_IDLE_STATUS;

char server[] = "192.168.139.196";

String postData;
String postVariable = "temp=";

WiFiClient client;

void setup() {

  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  postData = postVariable + temperatureF;
  int counter = 0;
  int soil_moisture = 2;
  int stem_diameter = 3;
  if (client.connect(server, 80)) {
      String message = String(counter) + "/" + soil_moisture + "/" + stem_diameter;

      
      Serial.print("Requesting URL: ");
      Serial.println(server);

      client.println("POST /nodemcu/ HTTP/1.1");
      client.println("Host: 192.168.139.196");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(message.length());
      client.println();
      client.print(message);
      
      delay(10);
  }

  if (client.connected()) {
    client.stop();
  }
  Serial.println(postData);

  delay(3000);
}
