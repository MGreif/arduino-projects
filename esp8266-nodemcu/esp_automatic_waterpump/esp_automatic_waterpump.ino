
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include <SD.h>
#include <SPI.h>
#include <iostream>
#include <stdio.h>

ESP8266WebServer web(80);

int waterPin = D0;

void handleRoot();
void handleWater();

void setup() {
  delay(1000);
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(waterPin, OUTPUT);
  digitalWrite(waterPin, LOW);
  Serial.println("Starting ESP ....");
  Serial.println("Initializing SD Card ....");
  bool ok = SD.begin(D8);
  if (!ok) {
    Serial.println("Failed SD initialization");
    exit(1);
  }
  Serial.println("Initialized SD Card");
  Serial.println("Reading config ...");
  WifiConfig c;

  Config conf;
  conf.getWifiConfig(&c, "config.txt");
  Serial.print("SSID: ");
  Serial.println(c.ssid);
  Serial.print(" Password: ");
  Serial.println(c.password);
  Serial.println("Connecting to wifi ....");
  WiFi.begin(c.ssid, c.password);

  wl_status_t status;
  while ((status = WiFi.status()) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected :)");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting webserver ...");
  web.on("/", handleRoot);
  web.on("/water", handleWater);
  web.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  web.handleClient();
}

void handleWater() {
  Serial.println("Water");
  digitalWrite(waterPin, HIGH);
  delay(10000);
  digitalWrite(waterPin, LOW);

}

void handleRoot() {
  web.send(200, "text/html", "<em>ESP Works!</em>");
}
