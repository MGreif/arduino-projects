#ifndef _MYINCLUDE
#define _MYINCLUDE

void findInFile(char* out, File* inFileRaw, const char keyToFind[10]);

struct WifiConfig {
  char ssid[50];
  char password[50];
};

class Config {
  public:
    void getWifiConfig(WifiConfig* out, const char * filename);
};
#endif