#ifndef MIKA_WATERPUMP
#define MIKA_WATERPUMP

class WaterPumpConfig {
  public:
    char waterpumpSeconds = '\0';
    void getWaterPumpConfig(const char * configFileName, const char * configKey);
    void debug();
};

#endif