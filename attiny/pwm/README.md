# AVR Attiny45 PWM

## What

A simple 5V/5W LED dimming project controlled using a potentiometer.
The dimming is done using the pulse-width-modulation signal of the attiny.


## Why

To learn about pulse-width-modulation.
To practically transform 2 usually battery powered led strips into two led strips controlled via a single device that is able to dimm them.


## Used components
- 10k potentiometer
- 1M ohm resistor (probably overkill)
- IRLZ44N logic level MOSFET
- Toggle Switch
- 2 * 1000nF electrolytic capacitor
- 22nF ceramic capacitor

## Wiring
- 5V
	-> Toggle switch (series)
	-> 1000nF Capacitor (series)
	-> 1000nF Capacitor (series)
		-> Attiny Vcc (parallel)
		-> Potentiometer (parallel)
		-> LED strip 1 (parallel)
			-> 22nF decoupling capacitor
				-> IRLZ44N drain
		-> LED strip 2 (parallel)
			-> 22nF decoupling capacitor
				-> IRLZ44N drain


- potentiometer -> GND
- potentiometer -> Attiny ADC 3
- Attiny OC0A -> IRLZ44N Gate
- IRLZ44N source -> GND

# Extra

- 2 x 1000nF capacitors were used because i had no 2k handy
- Ensure to separate the load GND with the MCU GND to decrease voltage drops off the MCU.

## Attny

- I used a 8.000.000 CPU clock speed for the Attiny, coupled with a 256 prescaler value will result in a ~120Hz frequency
	- 8000000/(256*256) = 122.0703125Hz
- Coupled with the IRLZ44N LL MOSFET with a total gate charge of 48nC we can do the math for the current our Attiny pin needs to supply
	- 1s/122Hz = Period of ~0.0082 per cycle
	- 0.000048C/0.0082 Period =~ 0.00585A -> 5.85mA
	- Our Attiny can provide up to 25mA current on one output pin. So we are in a safe space




