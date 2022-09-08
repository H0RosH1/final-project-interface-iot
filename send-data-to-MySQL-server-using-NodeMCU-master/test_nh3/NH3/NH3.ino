#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFiClientSecure.h>
#include <BH1750FVI.h>
#define DHTPIN D3

#define DHTTYPE DHT22
#define MQ_137 A0

DHT dht(D3,DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

float humidityData;
float temperatureData;
float fahrenheitData;

float analysis(int);
float Rs;
int sensorValue;

uint16_t lux;
int ledPin = D0;
const char* ssid = "test"; //"NP-Park-A513";// 
const char* password = "password"; //"33732036";
//WiFiClient client;
char server[] = "cksmartcare.com";   //eg: 192.168.16.61
const char* fringerprint = "30 25 f9 ce 0f 7b fa ae 19 6a c1 af 84 0f 49 bd 26 b4 9b 0b";//b
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
 
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(100);
  Serial.println("connecting...");
  pinMode(LED_BUILTIN, OUTPUT);
 }
void loop() { 
  sensorValue = analogRead(MQ_137);
  digitalWrite(LED_BUILTIN, LOW);
  lux = LightSensor.GetLightIntensity();
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(),1;
  fahrenheitData = dht.readTemperature(true),1;
  client.setFingerprint(fringerprint);
  Sending_To_phpmyadmindatabase();
  digitalWrite(LED_BUILTIN, HIGH);
  //delay(600000); // interval
  delay(100000);
}

float analysis(int adc){
  float slope = -0.4150374993;
  float A = 5.49597909;
  float Rseries = 1000;
  float V_Rseries = ((float)adc*5)/1023;
  Rs = ((5-V_Rseries)/V_Rseries)*Rseries;
  float R0 = 787.172;
  float Y = Rs/R0;
  double Methane_gas = pow(10,(log10(Y/A)/slope));
  return Methane_gas;
}

 void Sending_To_phpmyadmindatabase()  //CONNECTING WITH MYSQL
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
    client.print("&sm_ammonia="); //nh3
    client.print(analysis(sensorValue),3);
    Serial.print("Ammonia : ");
    Serial.print(analysis(sensorValue),3);
    Serial.println(" ppm");
    Serial.println(" ");
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: cksmartcare.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    Serial.print("temperatureData: ");
    Serial.print(temperatureData); //องศาC
    Serial.println("C");
    Serial.print("humidity: ");
    Serial.print(humidityData);
    Serial.println("%");
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lux");
    Serial.print("Ammonia : ");
    Serial.print(analysis(sensorValue),3);
    Serial.println(" ppm");
  }
}
