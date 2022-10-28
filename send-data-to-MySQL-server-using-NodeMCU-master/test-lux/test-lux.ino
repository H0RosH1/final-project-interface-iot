#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFiClientSecure.h>
#include <BH1750FVI.h>
#define DHTPIN D5

#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

float humidityData;
float temperatureData;
float fahrenheitData;
uint16_t lux;
//int ledPin = D0;
const char* ssid = "AUNON_2.4G"; //"NP-Park-A513";// 
const char* password = "ooy25110"; //"33732036";
//WiFiClient client;
char server[] = "cksmartcare.com";   //eg: 192.168.16.61
const char* fringerprint = "24 CB 69 49 A0 7B 6C F4 22 04 D0 97 00 D6 E0 77 2E fA F2 B7";
WiFiClientSecure client;

void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  LightSensor.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(100);
  Serial.println("connecting...");
  pinMode(LED_BUILTIN, OUTPUT);
 }
void loop()
{ 
  digitalWrite(LED_BUILTIN, LOW);
  lux = LightSensor.GetLightIntensity();
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(),1;
  fahrenheitData = dht.readTemperature(true),1;
  client.setFingerprint(fringerprint);
  Sending_To_phpmyadmindatabase();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(600000); // interval
 }

 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 443)) {
    
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET /send-data-sensor?sm_temperature=");     //YOUR URL
    Serial.print("temperatureData: ");
    Serial.print(temperatureData); //องศาC
    Serial.println("C");
    client.print(temperatureData); //ความชื่น
    client.print("&sm_humudity="); //ความชื่น
    Serial.print("humidity: ");
    client.print(humidityData);
    Serial.print(humidityData);
    Serial.println("%");
    client.print("&sm_light_intensity="); //ความเข้มแสง
    client.print(lux); //ความเข้มแสง
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lux");
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: cksmartcare.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
