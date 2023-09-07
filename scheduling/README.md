# Scheduling

## What

Simple scheduling project that calculated the current days, hours, minutes and seconds since the context started executing.
It works like basic Linux/Unix cronjobs and can be configured with:
- "-1" (unix *) as every
- Any valid (0-23 for hours, 0-59 for minutes, etc..) number

Right now it can only be one concrete value or every, not multiple.


## Why

Fun project with C. I need this functionality for simple time/timer based Arduino projects and wanted to write it myself to learn C.


## Used components
- Buzzer
- LED

## Wiring
- OUTPUT => BUZZER => GROUND
- OUTPUT => 220o res => LED => GROUND
