
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include <SD.h>
#include <SPI.h>
#include <iostream>
#include <stdio.h>
#include "cron.h"
#include "waterpump.h"

ESP8266WebServer web(80);
Cron cron;
WaterPumpConfig w;
WifiConfig c;


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

  c.getWifiConfig("config.txt");
  cron.readConfig("config.txt", "cron");
  cron.debug();

  w.getWaterPumpConfig("config.txt", "waterpumpSeconds");
  w.debug();


  // Print wifi config
  c.debug();
  if (!c.setWifiStaticConfig()) {
    Serial.println("Failed setting static wifi config!");
    Serial.println("Fallback to DHCP");
  }

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
  delay(w.waterpumpSeconds*1000);
  digitalWrite(waterPin, LOW);
}

void handleRoot() {
  web.send(200, "text/html", "<em>ESP Works!</em>");
}
