/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#include <AltSoftSerial.h>

#define isCentralBluetoothDevice false

AltSoftSerial mySerial;
char c=' ';
boolean NL = true;
char command[10];
uint8_t index = 0;


void setupBluetoothDevice(boolean isCentral) {
  mySerial.begin(9600);
  delay(1000);
  mySerial.flush();
  mySerial.flushInput();
  mySerial.flushOutput();
  if (isCentral) {
    sendCommand("AT+NAMECentral");
    sendCommand("AT+ROLE1");
    sendCommand("AT+INQ");
  } else {
    sendCommand("AT+NAMEPeriph");
    sendCommand("AT+ROLE0");
    sendCommand("AT+PIN 1111");
  }
  sendCommand("AT+LADDR");
  sendCommand("AT+RESET");
  sendCommand("AT+STATE?");
  sendCommand("AT+PIN");
  sendCommand("AT+ADDR?");
}

void setupConnectionWithPeripheral() {
  char peripheralName[] = "Periph";
}


// the setup function runs once when you press reset or power the board
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  setupBluetoothDevice(isCentralBluetoothDevice);
  Serial.flush();

  //sendCommand("AT");
  //sendCommand("AT+ROLE0");
  //sendCommand("AT+NAMECASTIEL");
  //sendCommand("AT");
  //sendCommand("AT+UUID0xFFE0");
  //sendCommand("AT+CHAR0xFFE1");
  //sendCommand("AT+NAMEbluino");
}

void sendCommand(String command) {
  Serial.println("Command to send: " + command);  // Print the command being sent

  // Clear the buffer before sending a new command
  while (mySerial.available()) {
    mySerial.read();  // Read and discard any remaining data
  }

  // Send command to Bluetooth module
  mySerial.print(command);
  mySerial.print("\r\n");

  // Wait briefly to ensure command is sent
  delay(200);

  // Prepare to collect the response
  String response = "";  // Initialize an empty string to store the response
  unsigned long timeout = millis() + 3000;  // Set a timeout of 2 seconds

  // Read response from Bluetooth module
  while (millis() < timeout ) {
    if (mySerial.available()) {

      char receivedChar = mySerial.read();  // Read a single character
      response += receivedChar;  // Append character to response string
    }
  }

  if (response == "") {
    sendCommand(command);
    return;
  }

  // Print the complete response to the Serial monitor
  Serial.println(response);
}

boolean isResonseReady() {
  return mySerial.available();
}

String waitForResponse() {

  // Prepare to collect the response
  String response = "";  // Initialize an empty string to store the response

  // Read response from Bluetooth module
  while (mySerial.available()) {
      char receivedChar = mySerial.read();  // Read a single character
      response += receivedChar;  // Append character to response string
  }
  mySerial.print("THX :)\r\n");

  // Print the complete response to the Serial monitor
  return response;
}


void loop() {
  delay(1000);


  if (!isCentralBluetoothDevice) {
    sendCommand("HELLLOOOO");
  } else {
    if (isResonseReady()) {
      String res = waitForResponse();
      Serial.println(res);
      if (res == "ledon") {
        digitalWrite(2, HIGH);
      } else if (res == "ledoff") {
        digitalWrite(2, LOW);
      }
    }
  }
}
