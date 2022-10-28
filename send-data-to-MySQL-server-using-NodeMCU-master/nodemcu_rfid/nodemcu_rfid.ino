/* This arduino code is sending data to mysql server every 30 seconds.

Created By Embedotronics Technologies*/

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFiClientSecure.h>
#define DHTPIN D5

#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;
float fahrenheitData;

const char* ssid = "AUNON_2.4G";// 
const char* password = "ooy25110";
//WiFiClient client;
char server[] = "cksmartcare.com";   //eg: 192.168.16.61
const char* fringerprint = "24 CB 69 49 A0 7B 6C F4 22 04 D0 97 00 D6 E0 77 2E fA F2 B7";
WiFiClientSecure client;

void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
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
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(),1;
  fahrenheitData = dht.readTemperature(true),1;
  client.setFingerprint(fringerprint);
  Sending_To_phpmyadmindatabase();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10000); // interval
 }

 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 443)) {
    
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET /send-data-sensor?temperature=");     //YOUR URL
    Serial.print("temperatureData: ");
    Serial.print(temperatureData);
    Serial.println("C");
    client.print(temperatureData);
    client.print("&humidity=");
    Serial.print("humidity: ");
    client.print(humidityData);
    Serial.print(humidityData);
    Serial.println("%");
    client.print("&fahrenheit=");
    Serial.print("fahrenheit: ");
    client.print(fahrenheitData);
    Serial.print(fahrenheitData);
    Serial.println("F");
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
