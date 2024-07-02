#include <string.h>
#include <sstream>
#include "WString.h"
#include <SPI.h>
#include <SD.h>
#include <string>
#include <algorithm>
#include "./config.h"

#define CONFIG_ITEM_SIZE_BYTES 50

void Config::getWifiConfig(WifiConfig *out, const char * filename)
{
  File configFile = SD.open(filename);
  findInFile(out->ssid, &configFile, "ssid");
  configFile.close();
  configFile = SD.open(filename);
  findInFile(out->password, &configFile, "password");
}

void findInFile(char *out, File *inFileRaw, const char keyToFind[10])
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
      char key[50] = {'\0'};
      strcpy(key, line);
      char value[50];
      strcpy(value, delimiter + 1);

      if (strcmp(key, keyToFind) == 0)
      {
        strcpy(out, value); // Copy the part after '=' to 'value'
        continue;
      }
      Serial.printf("Did not find key %s \n", key);
    }
  }
};
