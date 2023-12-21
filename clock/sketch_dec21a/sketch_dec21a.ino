int secondClock = 2;
int halfSecondClock = 3;
int manualDebouncedIn = 4;
int manualDebouncedOut = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(secondClock, OUTPUT);
  pinMode(halfSecondClock, OUTPUT);
  pinMode(manualDebouncedIn, INPUT_PULLUP);
  pinMode(manualDebouncedOut, OUTPUT);
  Serial.begin(9600);
}

int halfSecondsPassed = 0;

void resetClocks() {
  digitalWrite(secondClock, LOW);
  digitalWrite(halfSecondClock, LOW);
  digitalWrite(manualDebouncedOut, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool secondPassed = halfSecondsPassed % 2 == 0;

  if (secondPassed) {
    digitalWrite(secondClock, HIGH);
  }

  digitalWrite(halfSecondClock, HIGH);

  if (digitalRead(manualDebouncedIn) == HIGH) {
    digitalWrite(manualDebouncedOut, HIGH);
  }

  resetClocks();

  delay(500);
  halfSecondsPassed += 1;
}
