# ESP8266 with SD-Card Reader

## What

NodeMCU ESP8266 with a simple "webserver", reading wifi config from sd-card
Serving a simple webserver (ESP8266WebServer library) with following routes
- / : Shows simple alive message
- /LED : param "status" determines whether LED is "ON" or "OFF"
- /DHT : Gives information about the current temperature and humidity received from sensor

## Why

Learning ESP8266 setup and Wiring
Learning SPI interfaces
Learning SD-Card reading using SD Library

## Used components
- ESP8266 NodeMCU
- SPI SD-Card Reader
- DHT11 Temperature and Humidity sensor
- LED
- 220 ohm resistor

## Wiring
- NodeMCU VV (Input voltage 5V) -> SD VCC
- NodeMCU GND -> SD GND
- NodeMCU D5 (SCLK) -> SD SCLK
- NodeMCU D6 (MISO) -> SD MISO
- NodeMCU D7 (MOSI) -> SD MOSI
- NodeMCU D8 (CS) -> SD CS

- NodeMCU D0 -> LED

- NodeMCU D1 -> DHT
