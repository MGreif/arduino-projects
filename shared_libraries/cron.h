#ifndef MIKA_CRON
#define MIKA_CRON
#include <stdint.h>

class Cron {

public:
  char cronString[50] = {'\0'};
  char seconds = '\0';
  char minutes = '\0';
  char hours = '\0';
  char days = '\0';
  void readConfig(const char * configFileName, const char * configKey);
  void debug();
  bool checkScheduleSinceExecutionStart();

private:
  int readConfigFromString(char * configString, int size);
  bool hasConfigGuard() {
    return this->seconds != '\0' && this->minutes != '\0' && this->hours != '\0' && this->days != '\0';
  }
};

#endif