#include <ESP8266WebServer.h>

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SD.h>
#include "./config.h"
#include <DHT.h>
#define CONFIG_ITEM_SIZE_BYTES 50

ESP8266WebServer web(80);
 
const int ledPin = D0;
const int DHTPin = D1;

DHT dht(DHTPin, 11);

void handleRoot();
void handleLed();
void handleDHT();

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  delay(10);
 
  // Initializing SD Card
  Serial.print("Initializing SD card...");
  Serial.print(SD.fatType());
  if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  Config c;
  WifiConfig wifiConfig = {0};
  c.getWifiConfig(&wifiConfig, "config.txt");
  Serial.printf("Using ssid: %s \n", wifiConfig.ssid);
  Serial.printf("Using password: %s \n", wifiConfig.password);

  // Connecting to wifi
  Serial.print("Connecting to: "); 
  Serial.println(wifiConfig.ssid);
  WiFi.begin(wifiConfig.ssid, wifiConfig.password);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  web.on("/", handleRoot);
  web.on("/LED",handleLed);
  web.on("/DHT", handleDHT);
  // Start server
  web.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());
} 


void loop() {
  web.handleClient();
}

void handleRoot() {
  web.send(200, "text/html", "ESP8266 Works!");
}

void handleLed() {
  String status = web.arg("status");
  if (status.equals("ON")) {
    web.send(200, "text/html", "Set ON");
    digitalWrite(ledPin, HIGH);
  } else if (status.equals("OFF")) {
    web.send(200, "text/html", "Set OFF");
    digitalWrite(ledPin, LOW);
  } else {
    web.send(400, "text/html", "Unkown path param /LED?param=[ON|OFF]");
  }
}

void handleDHT() {
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  String response = "Humidity ";
  response.concat(humidity);
  response.concat("; Temperature: ");
  response.concat(temperatureC);
  web.send(200, "text/html", response);
}
