#include <AltSoftSerial.h>
#define ledPin PD7


AltSoftSerial mySerial;


void sendCommand(String command) {
  Serial.println("Command to send: " + command);  // Print the command being sent

  // Clear the buffer before sending a new command
  while (mySerial.available()) {
    mySerial.read();  // Read and discard any remaining data
  }

  // Send command to Bluetooth module
  mySerial.print(command);
  //mySerial.print("\r\n");

  // Wait briefly to ensure command is sent
  delay(200);

  // Prepare to collect the response
  String response = "";  // Initialize an empty string to store the response
  unsigned long timeout = millis() + 10000;  // Set a timeout of 2 seconds

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

  if (response != "") {
    mySerial.print("THX :)\r\n");
  }
  // Print the complete response to the Serial monitor
  return response;
}


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

 // sendCommand("AT+VERS?");

 // sendCommand("AT+TYPE?");
 // sendCommand("AT+NAMEMIKABLE");
 // sendCommand("AT+TYPE2");
 // sendCommand("AT+PASS123456");
// sendCommand("AT+TYPE?");
 //sendCommand("AT+ADDR?");

 // Configuring the slave
 //sendCommand("AT+ADVI0");
 //sendCommand("AT+ROLE0");
// sendCommand("AT+FLAG0");

  // put your setup code here, to run once:

}
void loop() {  
  delay(10);
  String x;
  // put your main code here, to run repeatedly:
  while ((x = waitForResponse()) != NULL) {
    Serial.println(x);
    if (strncmp(x.c_str(), "hi", 2) == 0) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}
