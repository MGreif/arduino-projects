#include <DS1307RTC.h>

DS1307RTC rtc;

tmElements_t tm;
#define SHOULD_SET_TIME true

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3)
    return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3)
    return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++)
  {
    if (strcmp(Month, monthName[monthIndex]) == 0)
      break;
  }
  if (monthIndex >= 12)
    return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void printTime(tmElements_t &tm)
{
  char buffer[50];
  sprintf(buffer, "%d.%d.%d %d:%d:%d", tm.Day, tm.Month, tm.Year + 1970, tm.Hour, tm.Minute, tm.Second);
  Serial.println(buffer);
}

void setRTCTime()
{
  if (!SHOULD_SET_TIME)
    return;
  Serial.print("compiled: ");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  if (getDate(__DATE__) && getTime(__TIME__))
  {
    Serial.println("AVR Macro strings converted to tmElements.");
    printTime(tm);
  }

  tmElements_t time;
  rtc.write(tm);
  delay(100);
  rtc.read(time);
}

void setup()
{
  Serial.begin(9600);
  setRTCTime();
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);
  tmElements_t time;
  rtc.read(time);
  printTime(time);
}
