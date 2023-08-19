byte buzzerOutput = 3;
byte potentioInput = A0;
short delayMs = 500;
short minFrequency = 0;
short maxFrequency = 10000;

void setup() {
  // put your setup code here, to run once:
  pinMode(potentioInput, INPUT);
  pinMode(buzzerOutput, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  short potentioValue = analogRead(potentioInput);
  short mappedValue = map(potentioValue, 0, 1024, minFrequency, maxFrequency);
  tone(buzzerOutput, mappedValue);
  delay(delayMs);
}
