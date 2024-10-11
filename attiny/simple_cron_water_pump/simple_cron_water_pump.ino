#include </home/mika/Arduino/libraries/DS1307_RTC_ATTINY/DS1307RTC.h>

#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <TinyWireM.h>


#ifndef CONFIG_H_
#define CONFIG_H_
 
// CPU frequency in Hz
#define F_CPU 1000000   // 1 MHz
 
#endif /* CONFIG_H_ */


#define DEBUG false
#define SHOULD_SET_TIME false

void cleanup();
void action();
bool checkScheduleSinceExecutionStart(tmElements_t current_time, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void go_to_sleep();
void setup_timer();
void reset_watchdog();

int waterPin = 1; 
int statusPin = 3;
int lengthModifierPin = A2;

USI_TWI tw;

DS1307RTC rtc(tw);

void status(bool special);

tmElements_t t;

void debug_blink(uint8_t amount) {
  for (uint8_t i = 0; i < amount ; i++) {
    digitalWrite(statusPin, HIGH);
    delay(50);
    digitalWrite(statusPin, LOW);
    reset_watchdog();

    if (i < amount-1) {
      delay(100);
    }
  }

}

void setup() {
  pinMode(waterPin, OUTPUT);
  pinMode(statusPin, OUTPUT);
  pinMode(lengthModifierPin, INPUT);
  cli();
  wdt_reset();
  MCUSR &= ~(1 << WDRF);
  WDTCR |= (1 << WDCE);
  WDTCR |= (1 << WDP2) | (1 << WDP1);
  WDTCR |= (1 << WDIE); //Watchdog  Mode = Interrupt Mode
  sei();

  status(true);

  tw.begin();
  rtc.sqw(0);
  // Following code sets the time
  if (SHOULD_SET_TIME) {
    t.Second = 0;
    t.Minute = 40;
    t.Hour = 18;
    t.Day = 11;
    t.Month = 9;
    t.Wday = 5;
    t.Year = 124;
    rtc.write(t);
  }
}


void status(bool special) {
  reset_watchdog();
  digitalWrite(statusPin, HIGH);
  delay(500);
  reset_watchdog();
  digitalWrite(statusPin, LOW);
  delay(50);
  reset_watchdog();
  digitalWrite(statusPin, HIGH);
  delay(500);
  reset_watchdog();
  digitalWrite(statusPin, LOW);
  delay(50);

  reset_watchdog();
  digitalWrite(statusPin, HIGH);
  delay(500);
  reset_watchdog();

  digitalWrite(statusPin, LOW);
    reset_watchdog();
  if(special) {
    delay(50);
  digitalWrite(statusPin, HIGH);
  reset_watchdog();

  delay(800);
    reset_watchdog();
  digitalWrite(statusPin, LOW);
  delay(50);
    reset_watchdog();

  digitalWrite(statusPin, HIGH);
  delay(800);
    reset_watchdog();
  digitalWrite(statusPin, LOW);
  }
  reset_watchdog();
}

ISR(WDT_vect) {
  wdt_reset();
}

void loop() {
  if (DEBUG) {
    debug_blink(1);
  }
  tmElements_t current_time;

  reset_watchdog();

  rtc.read(current_time);
  
  reset_watchdog();
  bool shouldWater = checkScheduleSinceExecutionStart(current_time, 255, 19, 0, 0);
  bool shouldShowStatus1 = checkScheduleSinceExecutionStart(current_time, 255, 255, 0, 0);

  if (shouldWater) {
    pumpWater();
  }

  if (shouldShowStatus1) {
    status(false);
  }
  go_to_sleep();
}

void go_to_sleep() {
    reset_watchdog();
    if (DEBUG) {
        debug_blink(2);
    }
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    power_all_disable();
    sleep_enable();
    sei();

    sleep_cpu();

    sleep_disable();
    power_all_enable();
}

void reset_watchdog() {
  wdt_reset();
}

void pumpWater() {
    int length = analogRead(lengthModifierPin);
    status(false);
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

bool checkScheduleSinceExecutionStart(tmElements_t current_time, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
  uint8_t dayDefault = day;
  if (day == 255) {
    dayDefault = current_time.Day;
  }

  uint8_t hourDefault = hour;
  if (hour == 255) {
    hourDefault = current_time.Hour;
  }

  uint8_t minuteDefault = minute;
  if (minute == 255) {
    minuteDefault = current_time.Minute;
  }

  uint8_t secondDefault = second;
  if (second == 255) {
    secondDefault = current_time.Second;
  };

  return current_time.Day == dayDefault && current_time.Hour == hourDefault && current_time.Minute == minuteDefault && current_time.Second == secondDefault;
}