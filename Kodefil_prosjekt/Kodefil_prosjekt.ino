#define FASTLED_INTERNAL  
#include "FastLED.h"     
#include "MobaLedLib.h"  // Use the Moba Led Library

#define NUM_LEDS          12;  // Number of LEDs with some spare channels (Maximal 256 RGB LEDs could be used)
#define LED_PIN            3;
#define STYRKE        64; 
#define LED_TYPE      WS2812;
#define COLOR_ORDER      RGB;

CRGB leds[NUM_LEDS];

const int gronnS1 = 4;
const int rodS1 = 5;
const int gronnS2 = 6;
const int rodS2 = 7;

const int lysS1 = 8;
const int lysS2 = 9;

const int raspberryPi = 10;

float forsinkelse = 0;

CRGBPalette16 startOppsett;

void setup() {
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  Fast.LED.setBrightness(STYRKE);

  startOppsett = RainbowColors_p;

}

void loop() {

}


void nedtellingMunn() {
  starttid = millis();
  if (tid - forsinkelse >= 8000) {
     return;
  }
}
