#include "waterpump.h"
#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <stdio.h>
#include <cmath>
#include <string>


void WaterPumpConfig::getWaterPumpConfig(const char * configFileName, const char * configKey) {
  File configFile = SD.open(configFileName);
  char waterpumpSecondString[CONFIG_ITEM_SIZE_BYTES] = "0";
  findInFile(waterpumpSecondString, &configFile, configKey);
  this->waterpumpSeconds = (char) std::stoi(waterpumpSecondString);
  configFile.close();
}

void WaterPumpConfig::debug() {
  Serial.println("---------- Waterpump ----------");
  Serial.print("waterpumpSeconds: ");
  Serial.printf("%d \n", (signed char) this->waterpumpSeconds);
  Serial.println("-------------------------------");
  Serial.println("");
}