// Pins with PWM
uint8_t Rpin = 3;
uint8_t Gpin = 5;
uint8_t Bpin = 6;
uint8_t RSelectedPin = 13;
uint8_t GSelectedPin = 12;
uint8_t BSelectedPin = 11;
uint8_t ButtonPin = 4;
uint8_t PotentioPin = A0;
byte selectedId = 0;
int oldButtonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(RSelectedPin, OUTPUT);
  pinMode(GSelectedPin, OUTPUT);
  pinMode(BSelectedPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  pinMode(PotentioPin, INPUT);
  analogWrite(Rpin,120);
  analogWrite(Gpin,10);
  analogWrite(Bpin,80);
  Serial.begin(9600);
}

struct Map {
  uint8_t RGBPin;
  uint8_t SelectedPin;
  byte id;
};

Map pinMap[] = { {Rpin, RSelectedPin, 0}, {Gpin, GSelectedPin, 1}, {Bpin, BSelectedPin, 2} };

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(ButtonPin) == HIGH && oldButtonState != 1) {
    Serial.println("PRESS BUTTON");
    oldButtonState = digitalRead(ButtonPin);
    selectedId = selectedId + 1;
    if (selectedId > 2) {
      selectedId = 0;
    }
  }
  oldButtonState = digitalRead(ButtonPin);
  

  Map selected = pinMap[0];

  for (byte i = 0; i < 3; i++) {
    if (pinMap[i].id == selectedId) {
      selected = pinMap[i];

    };
    digitalWrite(pinMap[i].SelectedPin, LOW);
  };
  digitalWrite(selected.SelectedPin, HIGH);

  analogWrite(selected.RGBPin, analogRead(PotentioPin)/4);
  delay(100);
  }
