# AT09 Bluetooth module

## What

Simple testing project to test out the capabilities of the AT09 cc2541 bluetooth module.
It was used to be loaded into separated atmega328PU chips with slight adjustments (One is central and the other peripheral).
I tried to let those two MCUs communicate via a stable bluetooth connection.
Unfortunately my AT09 module was not really capable of programatically connecting to other devices. It was possible via my phone, but not using the central BT device.

I then ordered other modules e.g: HC-05 HC-06 (peripheral only) and the HM-10 to test out BLE functionality.

## Why

Mostly for testing and education purposes.

## Used components
- 2* AT09 cc2541 bluetooth module
- 2* Atmega328PU
