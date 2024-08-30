#include <DS1307RTC.h>

DS1307RTC rtc;
tmElements_t tm;



void printTime(tmElements_t &tm) {
  char buffer[50];
  sprintf(buffer, "%d.%d.%d %d:%d:%d", tm.Day, tm.Month, tm.Year + 1970, tm.Hour, tm.Minute, tm.Second);
  Serial.println(buffer);
}

void setup() {
    Serial.begin(9600);
}

void loop() {

  // put your main code here, to run repeatedly:
  delay(1000);
  tmElements_t time;
  rtc.read(time);
  printTime(time);
}
