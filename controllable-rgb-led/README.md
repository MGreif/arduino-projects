# Controllable RGB diode

## What
A project to control each color segment of a RGB diode using some kind of input (Rotary encoder)

## Why
A perfect little project to learn Arduino programming with INPUTs and OUTPUT voltage. Also learning about the electronical part with wiring everything and using and figuring out the rotary encoder

## Used components
- RGB Diode (4 pinned)
- Red, Green, Blue diode
- 6 Resistors (220o)
- Rotary encoder module (5 pinned)

## Wiring
For each single colored diode:
- PIN -> resistor 220o -> diode -> GND

For the RGB diode:
- For RGB segments: PIN -> resistor 220o -> diode pin -> GND
- Ground pin goes into ground

For the rotary encoder:
- GND -> GND
- CLK -> PIN
- DT -> PIN
- +Pin -> 5v (i used 3.3v tho)
- SW -> PIN (INPUT_PULLUP)

All of the actual logic is defined in the script
