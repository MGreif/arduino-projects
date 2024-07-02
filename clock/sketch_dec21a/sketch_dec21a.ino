
void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  delay(1000);
}
