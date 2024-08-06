#ifndef _MYINCLUDE
#define _MYINCLUDE
#define CONFIG_ITEM_SIZE_BYTES 50

#include <SD.h>
void findInFile(char* out, File* inFileRaw, const char keyToFind[CONFIG_ITEM_SIZE_BYTES]);

class Config {
public:
  virtual void get(char* out, const char key[CONFIG_ITEM_SIZE_BYTES]) = 0;
};

class SDConfig: public Config {
public:
  char configFileName[50] = { '\0' };
  SDConfig(const char configFileName[50]) {
    strncpy(this->configFileName, configFileName, 50);
  }
  virtual void get(char* out, const char key[CONFIG_ITEM_SIZE_BYTES]);
};


class WifiConfig {
  public:
    char ssid[50] = { '\0' };
    char password[50] = { '\0' };
    char useStaticIP[2] = "N"; //Y or N
    char IPv4[16] = { '\0' };
    char gateway[16] = { '\0' };
    char subnet[16] = { '\0' };
    void getWifiConfig(Config& config, const char * filename);
    void debug();
    bool setWifiStaticConfig();
};

#endif