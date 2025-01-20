# Garage_Sensor
Garage Safety Sensor detector and visual status indicator. This is intended for observiing sensor status when the sensor itself is not observable.

A garage safety sensor transmitter / receiver pair are used (Amazon link here).

An Arduino Nano is used to observe the expected receiver pulse train (0.5 ms low, 6.5 ms high) and then update ann RGB strip based on the receiver status. The RGB strip is interfaced with the FastLED library.

The Arduino Nano IO are used:
| Use Case | Pin |
| -------- | --- |
| Built-in LED, for receiver status | 13 |
| Receiver sensing | 2 |
| RGB strip | A5 |

# Hardware Description
* [12V wall wart power supply](https://www.amazon.com/dp/B091XSVV1Y)
* [DC/DC adjustable supply](https://www.amazon.com/dp/B076H3XHXP)
* [8-bit RBG strip](https://www.amazon.com/dp/B0C7CH8VRJ)
* [Arduino Nano (knockoff)](https://www.amazon.com/dp/B0DFGR288F)
* [Safety sensor pair](https://www.amazon.com/dp/B0CB1BM9Q3)
* [Project box](https://www.amazon.com/dp/B08N1DD5WJ)
* Safety sensor wire

The 12V supply is used to step down the voltage and power everything. This can optionally be run off the actual garage door light socket so the circuit is only active / powered while the garage light is on.

The DC/DC adjustable power supplies are used to supply the 
1. 5V Arduino power
2. the sensor / receiver pair at 5.4V. This voltage is selected so that after the 120 ohm load resistor that the sensed voltage is not above 5V. This likely runs the transmitter / receiver below the expected 6V or 6.31V but it works as is. 