#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void cleanup();
void action();
bool checkScheduleSinceExecutionStart(short day, short hour, short minute, short second);
void go_to_sleep();
void setup_timer();

int waterPin = 4; 
int statusPin = 3;
int lengthModifierPin = A1;
long old_millis = 0;

volatile uint32_t elapsedTime = 0; // Time in milliseconds

void status();

void setup() {
  // put your setup code here, to run once:
  pinMode(waterPin, OUTPUT);
  pinMode(statusPin, OUTPUT);
  pinMode(lengthModifierPin, INPUT);
  status();
  digitalWrite(waterPin, HIGH);
  delay(200);
  digitalWrite(waterPin, LOW);
  cli();
  wdt_reset();
  MCUSR &= ~(1 << WDRF);
  WDTCR = (1 << WDCE) | (1 << WDE);
  WDTCR = (1 << WDP2) | (1 << WDP1);
  WDTCR |= (1 << WDIE); //Watchdog  Mode = Interrupt Mode
  sei();
}


void status() {
  reset_watchdog();
  digitalWrite(statusPin, HIGH);
  delay(200);
  digitalWrite(statusPin, LOW);
  delay(50);
  digitalWrite(statusPin, HIGH);
  delay(200);
  digitalWrite(statusPin, LOW);
  delay(50);
  digitalWrite(statusPin, HIGH);
  delay(200);
  digitalWrite(statusPin, LOW);
  reset_watchdog();
}

ISR(WDT_vect) {
  wdt_reset();
  elapsedTime += 1000;
}

void loop() {
  long c = millis();
  long current_time = elapsedTime + c + old_millis;
  bool shouldWater = checkScheduleSinceExecutionStart(current_time, -1, -1, -1, 5);
  bool shouldShowStatus = checkScheduleSinceExecutionStart(current_time, -1, -1, -1, 10);
  if (shouldWater) {
    pumpWater();
  }

  if (shouldShowStatus) {
    status();
  }

  if (shouldShowStatus || shouldWater) {
    old_millis = millis();
  }

  go_to_sleep();
  
}

void go_to_sleep() {
  reset_watchdog();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();
  power_all_disable();
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();
  power_all_enable();
}

void reset_watchdog() {
  cli();
  MCUSR &= ~(1 << WDRF);
  WDTCR = bit ( WDCE ) | bit ( WDE ) | bit ( WDIF ); // allow changes, disable reset, clear existing interrupt
  WDTCR = bit ( WDIE ) | bit ( WDP2 )| bit ( WDP1 ); // set WDIE ( Interrupt only, no Reset ) and 1 second TimeOut
  sei();
}

void pumpWater() {
    int length = analogRead(lengthModifierPin);
    status();
    digitalWrite(waterPin, HIGH);
    reset_watchdog();
    delay(500); // Min 0.5 seconds
    reset_watchdog();
    int multiplier = 3;
    int full_length = length*multiplier;
    for (int i = 0; i < floor(full_length/500); i++) {
      delay(500);
      reset_watchdog(); 
    }
    delay(full_length % 500);
    reset_watchdog();
    digitalWrite(waterPin, LOW);
};

bool checkScheduleSinceExecutionStart(long time_base, short day, short hour, short minute, short second) {
  long baseMillis = time_base;
  
  // Calculate offsets from baseMillis
  float millisToSecondOffset =  baseMillis / 1000;
  float millisToMinuteOffset =  millisToSecondOffset / 60;
  float millisToHourOffset =  millisToMinuteOffset / 60;
  float millisToDayOffset =  millisToHourOffset / 24;

  // Get full days since execution start
  float dayDelta = millisToDayOffset;
  float dayOfYear = fmod(floor(dayDelta), 365);
  // All following currentXXX variables were used to calculate the actual year from an absolute UNIX timestamp
  float currentDay = dayDelta - dayOfYear;

  // Get full hours since execution start
  float hourDelta = millisToHourOffset;
  float hourOfDay = fmod(floor(hourDelta), 24);
  float currentHour = hourDelta - hourOfDay;

  // Get full minutes since execution start
  float minuteDelta = millisToMinuteOffset;
  float minuteOfHour = fmod(floor(minuteDelta), 60);
  float currentMinute = minuteDelta - minuteOfHour;

  // Get full seconds since execution start
  float secondDelta = millisToSecondOffset;
  float secondOfMinute = fmod(floor(secondDelta), 60);

  // Populating "every" values with the current value
  float dayDefault = day;
  if (day == -1) {
    dayDefault = dayOfYear;
  }

  float hourDefault = hour;
  if (hour == -1) {
    hourDefault = hourOfDay;
  }

  float minuteDefault = minute;
  if (minute == -1) {
    minuteDefault = minuteOfHour;
  }

  float secondDefault = second;
  if (second == -1) {
    secondDefault = secondOfMinute;
  };

  return dayOfYear == dayDefault && hourOfDay == hourDefault && minuteOfHour == minuteDefault && secondOfMinute == secondDefault;
}