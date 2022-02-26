#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid     = "Gandhi Personal";
const char* password = "Gandhiji";
boolean watering = false;
int duration = 0;
int watering_duration = 0;
int w_duration = 8;
double bottom_threshold = 0;
double water = .1;
double soil_moisture = .1;
double stem_diameter = 5.0;
int count = 0;
int water_duration = 4;
int water_count = 2;
// dy/dx = (-(x)^2)/4


int wifiStatus;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);
  
  Serial.println();
  Serial.println();
  Serial.print("You are connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  wifiStatus = WiFi.status();

  if(count == 24){
    count = 0;
  }

  if(count == water_count){
    watering = true;
  }
  if(watering == true){
    soil_moisture = soil_moisture + .1;
  }
  else{
    soil_moisture = soil_moisture - .25*soil_moisture*soil_moisture;
  }
  if(count == (water_count + water_duration)){
    watering = false;
  }
  soil_moisture = soil_moisture + soil_moisture*((random(100000)/100000)-.5)/10;

  stem_diameter = stem_diameter + (random(10000000)/10000000000);
  
  if(wifiStatus == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Your ESP is connected!");
    Serial.println("Your IP address is: ");
    Serial.println(WiFi.localIP());

    HTTPClient http;
    
    String url = "http://192.168.0.134:5000/nodemcu/";
    for (int counter = 1; counter <= 30; counter++){
      // id + moisture + plant growth
      String message = String(counter) + "/" + soil_moisture + "/" + stem_diameter;
      Serial.print("Requesting URL: ");
      Serial.println(url);
      http.begin(url);
    //    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //    int httpCode = http.GET();
      int httpCode = http.POST(message);
      Serial.println(httpCode);
      http.end();
      delay(10);
    }
    // This will send the request to the server
    delay(30000);
//    Serial.println("Goodnight");
//    ESP.deepSleep(30e6);
  }
  else{
    Serial.println("");
    Serial.println("WiFi not connected");
  }
  delay(60000);
}
