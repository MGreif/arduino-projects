#include <cmath>
#include "core_esp8266_features.h"
#include <ctime>
#include <string>
#include <cstring>
#include "cron.h"
#include <stdio.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SD.h>
#include <SPI.h>
#include "config.h"


void Cron::readConfig(const char * configFileName, const char * configKey) {
  File configFile = SD.open(configFileName);
  findInFile(this->cronString, &configFile, configKey);
  configFile.close();
  this->readConfigFromString(this->cronString, 50);
}

// Parsing: '10 10 10 10' or '0 0 0 0 0'
int Cron::readConfigFromString(char *configString, int size) {
  char configClone[size] = {'\0'};

  strncpy(configClone, configString, size);
  char * section = configClone;

  int delimeter = '\x20';
  // Seconds
  char * delimeterPtr = strchr(section, delimeter);

  *delimeterPtr = '\0';

  char integer = (char) std::stoi(section);

  this->seconds = integer;

  // Minutes
  section = delimeterPtr + 1;
  delimeterPtr = strchr(section, delimeter);
  *delimeterPtr = '\0';
  integer = (char) std::stoi(section);
  this->minutes = integer;


  // Hours
  section = delimeterPtr + 1;
  delimeterPtr = strchr(section, delimeter);
  *delimeterPtr = '\0';
  integer = (char) std::stoi(section);
  this->hours = integer;


  // Days
  section = delimeterPtr + 1;
   integer = (char) std::stoi(section);
  this->days = integer;

  return true;
}

bool Cron::checkScheduleSinceExecutionStart() {
  long baseMillis = millis();
  
  // Calculate offsets from baseMillis
  float millisToSecondOffset =  baseMillis / 1000;
  float millisToMinuteOffset =  millisToSecondOffset / 60;
  float millisToHourOffset =  millisToMinuteOffset / 60;
  float millisToDayOffset =  millisToHourOffset / 24;

  // Get full days since execution start
  float dayDelta = millisToDayOffset;
  float dayOfYear = fmod(floor(dayDelta), 365);

  // Get full hours since execution start
  float hourDelta = millisToHourOffset;
  float hourOfDay = fmod(floor(hourDelta), 24);

  // Get full minutes since execution start
  float minuteDelta = millisToMinuteOffset;
  float minuteOfHour = fmod(floor(minuteDelta), 60);

  // Get full seconds since execution start
  float secondDelta = millisToSecondOffset;
  float secondOfMinute = fmod(floor(secondDelta), 60);

  // Populating "every" values with the current value
  float dayDefault = (int) this->days;
  if (this->days == (unsigned char)-1) {
    dayDefault = dayOfYear;
  }

  float hourDefault = (int) this->hours;
  if (this->hours == (unsigned char)-1) {
    hourDefault = hourOfDay;
  }

  float minuteDefault = (int) this->minutes;
  if (this->minutes == (unsigned char)-1) {
    minuteDefault = minuteOfHour;
  }

  float secondDefault = (int) this->seconds;
  if (this->seconds == (unsigned char)-1) {
    secondDefault = secondOfMinute;
  };

  return dayOfYear == dayDefault && hourOfDay == hourDefault && minuteOfHour == minuteDefault && secondOfMinute == secondDefault;
}
