int soundInput = A1;
int led1Out = 2;
int threshold = 720;

void setup() {
  // put your setup code here, to run once:
  pinMode(soundInput, INPUT);
  pinMode(led1Out, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(soundInput);
  Serial.println(value);
  if (value >= threshold) {
    digitalWrite(led1Out, HIGH);
  } else {
    digitalWrite(led1Out, LOW);
  }
  delay(1000);
  }
