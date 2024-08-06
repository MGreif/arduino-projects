#include <string.h>
#include <sstream>
#include "WString.h"
#include <SPI.h>
#include <SD.h>
#include <string>
#include <algorithm>
#include "./config.h"
#include "config.h"
#include <ESP8266WiFi.h>


void SDConfig::get(char* out, const char key[CONFIG_ITEM_SIZE_BYTES]) {
  File configFile = SD.open(this->configFileName);
  findInFile(out, &configFile, key);
  configFile.close();
}

void WifiConfig::getWifiConfig(Config& config, const char * filename)
{
  config.get(this->ssid, "ssid");
  
  config.get(this->password, "password");
  
  config.get(this->useStaticIP, "useStaticIP");
  
  config.get(this->IPv4, "IPv4");

  config.get(this->gateway, "gateway");

  config.get(this->subnet, "subnet");
}

bool WifiConfig::setWifiStaticConfig() {

  if (strncmp(this->useStaticIP, "Y", 1) != 0) {
    Serial.println("Skipping static IP config");
    return true;
  }

  IPAddress ip;
  if (!ip.fromString(this->IPv4)) {
    Serial.print("Could not parse ipv4: ");
    Serial.println(this->IPv4);
    return false;
  }

  IPAddress subnet;
  if (!subnet.fromString(this->subnet)) {
    Serial.print("Could not parse subnet: ");
    Serial.println(this->subnet);
    return false;
  }

  IPAddress gateway;
  if (!gateway.fromString(this->gateway)) {
    Serial.print("Could not parse gateway: ");
    Serial.println(this->gateway);
    return false;
  }

  return WiFi.config(ip, gateway, subnet);
}

void WifiConfig::debug() {
  Serial.println("---------- WiFi ----------");
  Serial.print("ssid: ");
  Serial.println(this->ssid);
  Serial.print("password: ");
  Serial.println(this->password);
  Serial.print("useStaticIP: ");
  Serial.println(this->useStaticIP);
  Serial.print("IPv4: ");
  Serial.println(this->IPv4);
  Serial.print("gateway: ");
  Serial.println(this->gateway);
  Serial.print("subnet: ");
  Serial.println(this->subnet);
  Serial.println("--------------------------");
  Serial.println("");

}



void findInFile(char *out, File *inFileRaw, const char keyToFind[CONFIG_ITEM_SIZE_BYTES])
{
  while ((*inFileRaw).available())
  {

    char line[100] = {'\0'};
    (*inFileRaw).readBytesUntil('\n', line, sizeof(line));

    char *delimiter = strchr(line, '=');
    if (delimiter != NULL)
    {
      // Split line at the first '='
      *delimiter = '\0'; // Replace '=' with '\0' to separate key and value
      char key[CONFIG_ITEM_SIZE_BYTES] = {'\0'};
      strcpy(key, line);
      char value[CONFIG_ITEM_SIZE_BYTES];
      strcpy(value, delimiter + 1);

      if (strcmp(key, keyToFind) == 0)
      {
        strcpy(out, value); // Copy the part after '=' to 'value'
        continue;
      }
    }
  }
};
