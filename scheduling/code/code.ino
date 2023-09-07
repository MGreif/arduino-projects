uint8_t ledPin = 8;
uint8_t activeBuzzerPin = A0;
uint8_t buttonPin = 3;

void cleanup();
void action();
bool checkScheduleSinceExecutionStart(short day, short hour, short minute, short second);

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool result = checkScheduleSinceExecutionStart(-1, -1, 1, 10);
  bool scheduleActive = result == 1;

  if (scheduleActive) {
    action();
  } else {
    cleanup();
  }

  Serial.println(result);
  delay(100);
}

void action() {
    digitalWrite(ledPin, HIGH);
    tone(activeBuzzerPin, 1000);
};

void cleanup() {
    digitalWrite(ledPin, LOW);
    noTone(activeBuzzerPin);
}

bool checkScheduleSinceExecutionStart(short day, short hour, short minute, short second) {
  long baseMillis = millis();
  
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
