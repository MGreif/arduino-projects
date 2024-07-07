
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include <SD.h>
#include <SPI.h>
#include <iostream>
#include <stdio.h>
#include "cron.h"

ESP8266WebServer web(80);
Cron cron;

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

  c.getWifiConfig("config.txt");
  cron.readConfig("config.txt", "cron");

  Serial.printf("Cron config: %d %d %d %d \n", (signed char) cron.seconds, (signed char)cron.minutes, (signed char)cron.hours, (signed char)cron.days);

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
  bool hit = cron.checkScheduleSinceExecutionStart();
  delay(100);
  if (hit) {
    Serial.println("HIT");
    handleWater();
    delay(1000);
  }
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
