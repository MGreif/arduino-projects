# ESP8266 with SD-Card Reader

## What

NodeMCU ESP8266 with a simple "webserver", reading wifi config from sd-card

## Why

Learning ESP8266 setup and Wiring
Learning SPI interfaces
Learning SD-Card reading using SD Library


## Used components
- ESP8266 NodeMCU
- SPI SD-Card Reader
- LED
- 220 ohm resistor

## Wiring
- NodeMCU VV (Input voltage 5V) -> SD VCC
- NodeMCU GND -> SD GND
- NodeMCU D5 (SCLK) -> SD SCLK
- NodeMCU D6 (MISO) -> SD MISO
- NodeMCU D7 (MOSI) -> SD MOSI
- NodeMCU D8 (CS) -> SD CS
