#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <SPI.h>
#include <SD.h>
#include "./config.h"
#define CONFIG_ITEM_SIZE_BYTES 50

WiFiServer server(80);

const int ledPin = D8;

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);

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
  
  // Start server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("ESP8266 IP: ");
  Serial.print(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
 WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Warten auf Daten vom Client
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
  
  
 
  // Erste Zeile des Requests lesen
  String request = client.readStringUntil('\r');
  Serial.println(request);

  if (strstr(request.c_str(), "LED") != NULL) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Activating LED");
    
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Deactivating LED");
  }

  client.flush();
}
