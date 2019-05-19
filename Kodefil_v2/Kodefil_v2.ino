#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        8
#define OYEPIN     3

#define NUMPIXELS  15 //Antall LEDs i stripen
#define PIXELOYE   12 //Antall LEDs i oynene

unsigned long forrigeTid = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oyeVenstre(PIXELOYE, OYEPIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);
  delay(3000); //sikkerhetsdelay ved oppstart
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(40); //Justerer lysstyrke på LEDs
  oyeVenstre.setBrightness(40);
  
  //oyeAv();
  
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  //oyeAv();
  nedtelling();
}

void allePaa() { //Setter alle LEDs i munnen til å være på med hvitt lys
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    
  }
}

void alleAv() { //Slår av alle LEDs i munnen
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void oyeSnurr() {
  oyeAv();
  for (int i = 0; i < PIXELOYE; i++) {
    oyeVenstre.setPixelColor(j, oyeVenstre.Color(255, 255, 255));
    oyeVenstre.show();
    forsinkelse(125);
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyeVenstre.setPixelColor(j, oyeVenstre.Color(0, 0, 0));
    oyeVenstre.show();
    forsinkelse(125);
  }
  
}


void oyeAv() { //Slår av lysene i øyne
  for (int j = 0; j < PIXELOYE; j++) {
      oyeVenstre.setPixelColor(j, oyeVenstre.Color(0, 0, 0));
      oyeVenstre.show();
  }
}

void forsinkelse(int forsinkelse) { //For å unngå problemer med delay(), bruker vi heller millis() for å skape en forsinkelse
  forrigeTid = millis();
  while (millis() < forrigeTid + forsinkelse) {
    //Vent [forsinkelse] ms
  }
}

void nedtelling() {

  allePaa();
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(10, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(12, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(13, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setPixelColor(14, pixels.Color(0, 0, 0));
  pixels.show();

  forsinkelse(1500);

  tidUte();

}

void tidUte() {
  
  for (int i = 0; i<4; i++) {
    blinking();
  }
}

void blinking() {
  allePaa();
  pixels.show();
  forsinkelse(200);
  alleAv();
  pixels.show();
  forsinkelse(200);
}
