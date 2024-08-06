int dataPin = 8;
int storageClock = 2;
int shiftClock = 4;

bool turn = true;

void setup() {
  // put your setup code here, to run once:
    pinMode(dataPin, OUTPUT);
  pinMode(storageClock, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:



  delay(1000);
  Serial.println("Starting ...");
  Serial.print("turn = ");
  Serial.println(turn ? 1 : 0);
  // setup
  digitalWrite(storageClock, LOW);

  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);
  
  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, !turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);
  
  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);
  
  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, !turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);

  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);

  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, !turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);

  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);
  
  digitalWrite(shiftClock, LOW);
  digitalWrite(dataPin, !turn ? 1 : 0);
  digitalWrite(shiftClock, HIGH);

  digitalWrite(storageClock, HIGH);

  delay(2000);
  if (turn == 1) {
    turn = 0;
  } else {
    turn = 1;
  }


}
