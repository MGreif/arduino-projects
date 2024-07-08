#ifndef _MYINCLUDE
#define _MYINCLUDE
#define CONFIG_ITEM_SIZE_BYTES 50

#include <SD.h>
void findInFile(char* out, File* inFileRaw, const char keyToFind[10]);

class WifiConfig {
  public:
    char ssid[50] = { '\0' };
    char password[50] = { '\0' };
    char useStaticIP[2] = "N"; //Y or N
    char IPv4[16] = { '\0' };
    char gateway[16] = { '\0' };
    char subnet[16] = { '\0' };
    void getWifiConfig(const char * filename);
    void debug();
    bool setWifiStaticConfig();
};

#endif