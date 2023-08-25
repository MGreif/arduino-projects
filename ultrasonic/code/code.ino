int triggerPin = 2;
int echoPin = 3;
int ledPin = 4;
int thresholdCm = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int time = pulseIn(echoPin, HIGH);
  if (time == 0) {
      Serial.println("Ran into timeout 0");
  } else {
    int distanceCm = time * 0.034/2;
    Serial.println("Distance(cm): ");
    Serial.println(distanceCm);
    if (distanceCm < thresholdCm) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }

  delay(100);

  }
