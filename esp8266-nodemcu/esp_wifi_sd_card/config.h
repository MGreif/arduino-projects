#ifndef _MYINCLUDE
#define _MYINCLUDE

void findInFile(char* out, File* inFileRaw, const char keyToFind[10]);

class WifiConfig {
  public:
    char ssid[50];
    char password[50];
    void getWifiConfig(const char * filename);
};
#endif