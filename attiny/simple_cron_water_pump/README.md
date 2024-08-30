# Attiny plant watering automation

## What

Basically just an Attiny connected to a real-time-clock to show status and/or water my plants in a certain interval. I tried to reuse the unix-cron notation here.
Its powered using a 5V 3W solar pannel and utilizes the inbuilt ATtiny watchdog timer software interrupt to wake up the MCU each second.
This reduces the battery usage from (5mA to 0.3mA) which pumped by contraption lifetime to ~300 days and one hour of straight sunlight could be able to add 60 days of lifetime.
The duration and strength of the waterpump pump is adjustable using potentiometers.


## Why

Plants need water and people are lazy....
I wanted to learn about batteries, solar panels, sleep modes of MCU and interrupts.
This was/is actually a great beginner project.
Calculating the correct formulas to get the waterpump running was interesting and educating.

This project showed me that decoupling capacitors are quite useful as without the casual 100pF cap the attiny was not able to power pump as expected. It resulted in a PWM like signal that just made my pump "shiver".
Also a noise/tolerance capacitor, to handle voltage drops induced by large current demands, is also a good idea in almost every project :D

## Used components
- Attiny (25/45/85)
- DS1307 RTC
- 5V (~200mA) water pump
- 2*Potentiometer
- Li-ion battery (3.7V, 2400mAh)
- Solar pannel (5V 3W)
- Li-ion Battery charge module
- HW-085 mini step up boost module to pump the 3.7V up to 5 for the water pump
