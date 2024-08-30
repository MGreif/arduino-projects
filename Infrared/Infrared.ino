#define ledPin 2
#define irPin 3
#define dhtPin 4
#include <IRremote.hpp>
#include <Wire.h>
#include <oled.h>
#include <DHT.h>
#define I2C_ADDRESS 0x3C


DHT dht(dhtPin, DHT22);
OLED display(A4,A5,NULL,OLED::W_128,OLED::H_32,OLED::CTRL_SH1106,0x3C);


int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(dhtPin, INPUT);
  Serial.begin(9600);
  IrReceiver.begin(irPin);
  display.begin();
  dht.begin();
}

void writeLCD() {
  display.clear(); //Löschen der aktuellen Displayanzeige
  display.flush();
  display.setCursor(0,0);
  display.print("Count: ");
  display.print(counter); //Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
    display.setCursor(6,8);
  display.print("Temp: ");
  display.print(dht.readTemperature()); //Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
  display.draw_pixel(5 + counter, 5 + counter);
  display.setCursor(12,16);
  display.print("Humid: ");
  display.print(dht.readHumidity()); //Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
        if (IrReceiver.decodedIRData.command == ((unsigned char) '\x80')) {
      Serial.println(digitalRead(ledPin));
      if (digitalRead(ledPin) == 1) {
      digitalWrite(ledPin, LOW);

      } else {
              digitalWrite(ledPin, HIGH);
              counter++;
              writeLCD();
      }

    }
    IrReceiver.resume(); // Enable receiving of the next value

  }
  
  writeLCD();
  delay(10);

  
}
