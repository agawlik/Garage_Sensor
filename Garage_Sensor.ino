/*
  Garage_Sensor

  Detects garage door safety sensor, looking for pulse train on digital 
  input pin 2, and indicating whether it is obstructed or clear on RGB
  LEDs on A5 (using FastLED library). There is a 15 ms latency over which 
  a low pulse is searched for.

  The expected pulse train is 0.5 ms low, 6.5 ms high

  Hardware: Arduino Nano (knockoff: https://www.amazon.com/dp/B0DFGR288F)

  created 2025
  by Aaron Gawlik

  This code is in the public domain.

*/

#include <stdint.h>
#include <FastLED.h>

/*
 * Constants
 */
const int receiverPin = 2;  // the number of the sensor receiver pin
const int ledPin = 13;    // the number of the on-board builtin LED pin

// RGB strip configuration
#define NUM_LEDS 8
#define RGB_DATA_PIN A5

// number of active LEDs. Must be less than NUM_LEDS. Remainder will be blank (black)
uint8_t numActiveLeds = 2u;

/*
 * Variables
 */
int receiverState = 0;  //!< receiver status / state

volatile uint16_t receiverEdgeCount = 0u; //!< number of ISR calls for pulse train
volatile uint8_t timerReset = 0u; //!< ISR call indicator

CRGB leds[NUM_LEDS]; //< FastLED RBG

void receiver_fall_ISR(void)
{
  timerReset = 1u;
  receiverEdgeCount += 1u;
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting Garage_Sensor");

  // Handle out of range number of LEDs
  if (numActiveLeds > NUM_LEDS)
  {
    numActiveLeds = NUM_LEDS;
  }
  else if (numActiveLeds == 0)
  {
    numActiveLeds = 1u;
  }

  // digital IO
  pinMode(ledPin, OUTPUT);
  pinMode(receiverPin, INPUT);

  // RGB LEDs
  FastLED.addLeds<NEOPIXEL, RGB_DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  // Interrupt
  attachInterrupt(digitalPinToInterrupt(receiverPin), receiver_fall_ISR, FALLING);

  // Initialize ISR indicator
  timerReset = 0u;
}

void loop() 
{
  uint8_t ledState;

  // clear ISR indicator
  timerReset = 0u;
  // Delay for 16 ms 
  delayMicroseconds(15000);
  
  // check whether ISR has been triggered
  if (timerReset == 0u)
  {
    ledState = 0u;
    // no ISR --> no pulse train
    digitalWrite(ledPin, LOW);
  }
  else
  {
    ledState = 1u;
    digitalWrite(ledPin, HIGH);
  }

  // Update RGB
  for (uint8_t i = 0u; i < numActiveLeds; i++)
  {
    leds[i] = (ledState == 0u) ? CRGB::Red : CRGB::Green;
  }
  FastLED.show();
}
