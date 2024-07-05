# ESP8266 WiFi Waterpump

## What

NodeMCU ESP8266 with a simple "webserver", reading wifi config from sd-card
Serving a simple webserver (ESP8266WebServer library) with following routes
- / : Shows simple alive message
- /water : Simply toggles a digital output. This puts a transistor into saturation mode and toggles a 200mA waterpump

## Why

Learning transistor calculations

## Used components
- ESP8266 NodeMCU
- SPI SD-Card Reader
- S8050 NPN Transistor (To handle 200mA currents)
- 220 ohm resistor (After fiddling around i managed to get a stable HFE of around 20 with a Base current of around 10mA, which amplifies to 200mA, the desired current
for the waterpump)

## Wiring
- NodeMCU VV (Input voltage 5V) -> SD VCC
- NodeMCU GND -> SD GND
- NodeMCU D5 (SCLK) -> SD SCLK
- NodeMCU D6 (MISO) -> SD MISO
- NodeMCU D7 (MOSI) -> SD MOSI
- NodeMCU D8 (CS) -> SD CS

- NodeMCU D0 -> Transistor Base

- NodeMCU VV -> Waterpump -> Transistor collector -> Transistor Emitter -> Ground
