// Pins with PWM
uint8_t Rpin = 3;
uint8_t Gpin = 5;
uint8_t Bpin = 6;

// Pins for diodes indicating which color is being adjusted
uint8_t RSelectedPin = 13;
uint8_t GSelectedPin = 12;
uint8_t BSelectedPin = 11;

// Rotary encoder pins
uint8_t ButtonPin = 4;
uint8_t RotaryCLKPin = 8;
uint8_t RotaryDTPin = 9;

// Global variables
byte counter = 0;
byte lastRotaryCLKState = 0;
byte selectedId = 0;
byte stepModifier = 10;

long lastButtonPress = 0;

void setup() {
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(RSelectedPin, OUTPUT);
  pinMode(GSelectedPin, OUTPUT);
  pinMode(BSelectedPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(RotaryCLKPin, INPUT);
  pinMode(RotaryDTPin, INPUT);

  // Set initial values for each color
  analogWrite(Rpin,120);
  analogWrite(Gpin,10);
  analogWrite(Bpin,80);

  Serial.begin(9600);

  lastRotaryCLKState = digitalRead(RotaryCLKPin);
}

struct Map {
  uint8_t RGBPin;
  uint8_t SelectedPin;
  uint8_t savedColorValue;
  byte id;
};

Map pinMap[] = { {Rpin, RSelectedPin, 30, 0}, {Gpin, GSelectedPin, 30, 1}, {Bpin, BSelectedPin, 30, 2} };

void loop() {

  // Check if rotary button is pressed
  if (digitalRead(ButtonPin) == HIGH) {
    if (millis() - lastButtonPress > 50) {
      selectedId = selectedId + 1;
      if (selectedId > 2) {
        selectedId = 0;
      };
    };
    lastButtonPress = millis();
  };
  

  Map selected = pinMap[0];

  byte colorValue = 0;

  // Find corresponding pinMap for selected id
  for (byte i = 0; i < 3; i++) {
    if (pinMap[i].id == selectedId) {
      selected = pinMap[i];
      colorValue = selected.savedColorValue;
    };
    digitalWrite(pinMap[i].SelectedPin, LOW);
  };
  digitalWrite(selected.SelectedPin, HIGH);

  // Getting the counter value
  byte currentStateCLK = digitalRead(RotaryCLKPin);

  // Checking wether to increse or decrease the current color value based on rotary encoder state
  if (currentStateCLK != lastRotaryCLKState && currentStateCLK == 1) {

    if (digitalRead(RotaryDTPin) != currentStateCLK) {

        if (colorValue + stepModifier > 255) {
          colorValue = 255;
        } else {
          colorValue = colorValue + stepModifier;
        };

    } else {

      if (colorValue - stepModifier < 0) {
        colorValue = 0;
      } else {
        colorValue = colorValue - stepModifier;
      };

    };
  };

  // Saving current CLK state to determine direction switches
  lastRotaryCLKState = currentStateCLK;


  analogWrite(selected.RGBPin, colorValue);
  selected.savedColorValue = colorValue;
  pinMap[selectedId] = selected;
  }
