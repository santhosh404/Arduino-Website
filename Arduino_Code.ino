
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h> 

#define DHTPIN D2  
DHT dht(DHTPIN, DHT11);



const char *ssid = "SSID NAME";       // Your SSID Name
const char *password = "SSID PASSWORD"; // Your SSID Password
String API_KEY = "YOUR_API_KEY";      //Paste your API Key Here


const char *host = "https://temp-arduino.herokuapp.com/";

void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);      
  
  WiFi.begin(ssid, password);     
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
}


void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  String jsonString = "{\"API\":";
  jsonString += '"';
  jsonString += API_KEY;
  jsonString += '"';
  jsonString += ',';
  jsonString += "\"Temperature\":";
  jsonString += t;
  jsonString += ',';
  jsonString += "\"Humidity\":";
  jsonString += h;
  jsonString += "}";
  Serial.print(" Humidity " );

  Serial.print(h);

  Serial.print(" ");

  Serial.print(" Temparature ");

  Serial.println(t);

  HTTPClient http;   
  http.begin("http://temp-arduino.herokuapp.com/");             
  http.addHeader("Content-Type","application/json");
  Serial.println(jsonString);
  int httpCode = http.POST(jsonString); 
  String payload = http.getString();  

  Serial.println(httpCode);   
  Serial.println(payload);  

  http.end();  
  delay(10000);  
}