/* Inputs:
 * Munn = 2
 * Øyne = 8;
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define MUNN           2
#define OYNE           8

#define NUMPIXELS  15 //Antall LEDs i stripen
#define PIXELOYE   12 //Antall LEDs i oynene

unsigned long forrigeTid = 0;

unsigned long tidNaa = 0;

const int gronnS1 = 9;
const int rodS1 = 10;
const int gronnS2 = 11;
const int rodS2 = 12;

boolean ferdig = false;

Adafruit_NeoPixel pixels(NUMPIXELS, MUNN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oyne(PIXELOYE, OYNE, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);
  delay(3000); //sikkerhetsdelay ved oppstart
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  oyne.begin();
  pixels.setBrightness(40); //Justerer lysstyrke på LEDs
  oyne.setBrightness(40);
  pinMode(gronnS1, INPUT_PULLUP);       //Reverserer input-signal slik at de alltid sender HIGH, og programmet lytter etter LOW
  pinMode(rodS1, INPUT_PULLUP);         //Dette må gjøres siden knappene kun har to 'pins', og vil gi merkelige resultater ellers
  pinMode(gronnS2, INPUT_PULLUP);
  pinMode(rodS2, INPUT_PULLUP);
  
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  //oyeAv();
  while (!ferdig) {
    nedtelling();
  }
  

  ferdig = false;
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
    oyeVenstre.setPixelColor(i, oyne.Color(255, 255, 255));
    oyeVenstre.show();
    forsinkelse(125);
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyeVenstre.setPixelColor(i, oyne.Color(0, 0, 0));
    oyeVenstre.show();
    forsinkelse(125);
  }
  
}

void oyeAv() { //Slår av lysene i øyne
  for (int j = 0; j < PIXELOYE; j++) {
      oyeVenstre.setPixelColor(j, oyne.Color(0, 0, 0));
      oyeVenstre.show();
  }
}

void forsinkelse(int forsinkelse) { //For å unngå problemer med delay(), bruker vi heller millis() for å skape en forsinkelse
  forrigeTid = millis();
  while (millis() < forrigeTid + forsinkelse) {
    //Vent [forsinkelse] ms
  }
}

boolean nedtelling() {

  tidNaa = millis();

  sjekkTrykk();
  allePaa();
  pixels.show();

  //forsinkelse(1500);
  oyeSnurr();
  sjekkTrykk();
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.show();

  //forsinkelse(1500);
  oyeSnurr();
  sjekkTrykk();
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.show();

  //forsinkelse(1500);
  oyeSnurr();
  sjekkTrykk();
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(9, pixels.Color(0, 0, 0));
  pixels.show();

  //forsinkelse(1500);
  oyeSnurr();
  sjekkTrykk();
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(10, pixels.Color(0, 0, 0));
  pixels.show();
  sjekkTrykk();
  //forsinkelse(1500);
  oyeSnurr();

  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 0));
  pixels.show();
  sjekkTrykk();
  //forsinkelse(1500);
  oyeSnurr();

  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(12, pixels.Color(0, 0, 0));
  pixels.show();
  sjekkTrykk();
  //forsinkelse(1500);
  
  oyeSnurr();
  sjekkTrykk();
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(13, pixels.Color(0, 0, 0));
  pixels.show();
  sjekkTrykk();
  //forsinkelse(1500);

  oyeSnurr();

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setPixelColor(14, pixels.Color(0, 0, 0));
  pixels.show();

  //forsinkelse(1500);
  oyeSnurr();
  sjekkTrykk();
  tidUte();

}

void tidUte() {
  ferdig = true;
  
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

void sjekkTrykk() {
  if (digitalRead(gronnS1) == LOW) {
        Serial.println("Grønn 1");
        delay(250);
    };
    
    if (digitalRead(rodS1) == LOW) {
        Serial.println("Rød 1");
        delay(250);
    };
    
    if (digitalRead(gronnS2) == LOW) {
        Serial.println("G2 OK");
    };
    
    if (digitalRead(rodS2) == LOW) {
        Serial.println("R2 OK");
    }
}
