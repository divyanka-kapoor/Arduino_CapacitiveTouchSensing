
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif` .  

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#define LED_PIN     7
#define LED_COUNT  8
#define BRIGHTNESS 50

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // Get the currently touched pads
  //  setThreshholds(uint8_t touch, uint8_t release);
  
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {

    switch (i) {
      case 0:
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 0.5 ml");
          //        }
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 1:
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 1.5 ml");       
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 2 :
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 2 ml");
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 3 :
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 4 ml");
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 4 :
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 6 ml");
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 5 :
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 10 ml");
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      case 6 :
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
          Serial.println("Volume is 16 ml");
          colorWipe(strip.Color(255,   0,   0)     , 50, i); // Red
          colorWipe(strip.Color(  0, 255,   0)     , 50, i); // Green
          colorWipe(strip.Color(  0,   0, 255)     , 50, i); // Blue
          colorWipe(strip.Color(  0,   0,   0, 255), 50, i); // True white (not RGB white)
        }
        break;
      default:
        // statements
        break;
    }
  }

  // reset our state
  lasttouched = currtouched;

  return;
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
 
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  //  Serial.print(cap.baselineData(4)); Serial.print("\t");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(5000);

}

void colorWipe(uint32_t color, int wait, int lednum) {

    strip.setPixelColor(lednum, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment

}
