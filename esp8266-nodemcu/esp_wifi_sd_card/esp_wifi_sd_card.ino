#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <SPI.h>
#include <SD.h>
#include "./config.h"
#define CONFIG_ITEM_SIZE_BYTES 50

const char* ssid     = "TheRogueOne";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "bnLXFvU1Q5cUy3LlH3Wmgkn87P14LfStZYuZiS29";     // The password of the Wi-Fi network
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
  c.getWifiConfig(&wifiConfig);
  Serial.printf("Using ssid: %s \n", wifiConfig.ssid);
  Serial.printf("Using password: %s \n", wifiConfig.password);

  // Mit Wifi verbinden
  Serial.print("Verbinden mit: "); 
  Serial.println(wifiConfig.ssid);
  WiFi.begin(wifiConfig.ssid, wifiConfig.password);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi verbunden");
  // Start des Servers
  server.begin();
  Serial.println("Server gestartet");
 
  // Print the IP address
  Serial.print("Diese URL zum Verbinden aufrufen: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  


  File myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to file");
    myFile.println("This is the first line");
    myFile.println("This is the second line");
    myFile.close();
  } else {
    Serial.println("Error opening file");
  }

  myFile = SD.open("test.txt", FILE_READ);

  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) { Serial.write(myFile.read()); }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
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
