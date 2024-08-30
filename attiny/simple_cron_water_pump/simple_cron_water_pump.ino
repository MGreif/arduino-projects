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

void cleanup();
void action();
bool checkScheduleSinceExecutionStart(tmElements_t current_time, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void go_to_sleep();
void setup_timer();

int waterPin = 4; 
int statusPin = 3;
int lengthModifierPin = A1;

volatile uint32_t elapsedTime = 0; // Time in milliseconds

USI_TWI tw;

DS1307RTC rtc(tw);

void status();

void setup() {
  // put your setup code here, to run once:
  pinMode(waterPin, OUTPUT);
  pinMode(statusPin, OUTPUT);
  pinMode(lengthModifierPin, INPUT);
  status();
  cli();
  wdt_reset();
  MCUSR &= ~(1 << WDRF);
  WDTCR = (1 << WDCE) | (1 << WDE);
  WDTCR = (1 << WDP2) | (1 << WDP1);
  WDTCR |= (1 << WDIE); //Watchdog  Mode = Interrupt Mode
  sei();
  tw.begin();

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
}

void loop() {

  tmElements_t current_time;
  reset_watchdog();

  rtc.read(current_time);
  
  reset_watchdog();
  bool shouldWater = checkScheduleSinceExecutionStart(current_time, 255, 12, 0, 0);
  bool shouldShowStatus = checkScheduleSinceExecutionStart(current_time, 255, 255, 255, 10);
  if (shouldWater) {
    pumpWater();
  }

  if (shouldShowStatus) {
    status();
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

bool checkScheduleSinceExecutionStart(tmElements_t current_time, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {

  // Populating "every" values with the current value
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