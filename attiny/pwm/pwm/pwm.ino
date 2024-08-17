/*
  Author: Mika Greif
  Description: Simple code for Attiny(45) pulse-width-modulation using fast PWM mode.
  PWM duty cycle is adjustable via a potentiometer 
*/

void setup() {
  pinMode(PB4, OUTPUT);
  digitalWrite(PB4, HIGH);
  delay(100);
  digitalWrite(PB4, LOW);
  delay(100);
  digitalWrite(PB4, HIGH);
  delay(100);
  digitalWrite(PB4, LOW);
  delay(100);
  setup_timer();
}

void setup_timer() {
  DDRB |= 0x01;
  TCCR0A |= B10000011;
  TCCR0B = TCCR0B & B00000000 | 0x01;
}

void loop() {
  int val = analogRead(A3);  
  OCR0A = byte(map(val, 0, 1023, 0, 255));
  delay(80);
}
