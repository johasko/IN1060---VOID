#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>               // Required for 16 MHz Adafruit Trinket
#endif

#include <Wire.h>                     // Library for sammenkobling av arduinoer

#define MUNN           7
#define OYNE           8

//#define RST_PIN        6
//#define SS_PIN         5

#define SLAVE_ADDR     9              //Definerer nummer for slave-Arduino
#define ANSWER_SIZE    1              //Størrelse på forventet svar fra slave

#define PIXELMUNN      15             //Antall LEDs i munn
#define PIXELOYE       12             //Antall LEDs i oynene

unsigned long forrigeTid = 0;

int rfidKort[] = {1, 2, 3};

unsigned long tidNaa = 0;
int forsinkelseSnurr = 125;
// int nedtellingTid = 13500;

const int gronnS1 = 9;
const int rodS1 = 10;
const int gronnS2 = 11;
const int rodS2 = 12;

//1 = true, 2 = false
int svarS1 = 0;
int svarS2 = 0;


Adafruit_NeoPixel munn(PIXELMUNN, MUNN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oyne(PIXELOYE, OYNE, NEO_GRB + NEO_KHZ800);
//MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {

  Serial.begin(9600);
  delay(3000);                       //Sikkerhetsdelay ved oppstart for å hindre kortslutting
  Wire.begin();
  munn.begin();                      // Initialiserer LED-strip
  oyne.begin();
  munn.setBrightness(40);            //Justerer lysstyrke på LEDs
  oyne.setBrightness(40);
  pinMode(gronnS1, INPUT_PULLUP);    //Reverserer input-signal slik at de alltid sender HIGH, og programmet lytter etter LOW
  pinMode(rodS1, INPUT_PULLUP);      //Dette må gjøres siden knappene kun har to 'pins', og vil gi merkelige resultater ellers
  pinMode(gronnS2, INPUT_PULLUP);
  pinMode(rodS2, INPUT_PULLUP);

}

void loop() {
  munn.clear();                     // Slår av alle pixler i munn
  oyne.clear();                     // Slår av alle pixler i øyne

  //Wire.beginTransmission(SLAVE_ADDR);
  //Wire.write(0);
  //Wire.endTransmission();
  int kort;
  kort = 0;
  //Serial.println("Start");
  delay(1000);
  while (kort == 0) {
    Wire.requestFrom(SLAVE_ADDR, 1);
  
    while (Wire.available()) {
      //Serial.println("Leser kort");
      kort = Wire.read();
     }
     //Serial.println("Lest kort");
  }

  
  Serial.print("KategoriID: ");
  Serial.println(kort);
  delay(2000);
  //nedtelling();

}

void velgKat(int kort) {
}

void munnPaa() {                    //Setter alle LEDs i munnen til å være på med hvitt lys
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(255, 255, 255));

  }
}

void munnAv() {                     //Slår av alle LEDs i munnen
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(0, 0, 0));
  }
}

void faktaLys() {
    for (int i = 0; i < PIXELMUNN; i++) {
      munn.setPixelColor(i, munn.Color(0, 255, 0));
    }
    munn.show();

    for (int i = 0; i < PIXELOYE; i++) {
      oyne.setPixelColor(i, oyne.Color(0, 255, 0));
    }
    oyne.show();
}

void fleipLys() {
    for (int i = 0; i < PIXELMUNN; i++) {
      munn.setPixelColor(i, munn.Color(255, 0, 0));
    }
    munn.show();

    for (int i = 0; i < PIXELOYE; i++) {
      oyne.setPixelColor(i, oyne.Color(255, 0, 0));
    }
    oyne.show();
}

void oyeSnurr() {
    oyne.clear();
  // oyeAv();                       //Starter med alle pixler slått av

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(255, 255, 255));
    oyne.show();
    forsinkelse(125);
    /*tidNaa = millis();
    while ((millis() - tidNaa) >= forsinkelseSnurr) {
        sjekkTrykk();
    }*/
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(0, 0, 0));
    oyne.show();
    forsinkelse(125);
    /*tidNaa = millis();
    while ((millis() - tidNaa) >= forsinkelseSnurr) {
        sjekkTrykk();
    }*/
  }

}

void oyeAv() {                    //Slår av lysene i øyne
  for (int j = 0; j < PIXELOYE; j++) {
      oyne.setPixelColor(j, oyne.Color(0, 0, 0));
      oyne.show();
      forsinkelse(125);
  }
}

void forsinkelse(int forsinkelse) { //For å unngå problemer med delay(), bruker vi heller millis() for å skape en forsinkelse
  forrigeTid = millis();
  while (millis() < forrigeTid + forsinkelse) {
    //Vent [forsinkelse] ms
    sjekkTrykk();
  }
}

boolean nedtelling() {

  // sjekkTrykk();
  munnPaa();
  munn.show();

  oyeSnurr();                    //Sørger for et 1500ms delay, totalt 13500ms nedtelling
  // sjekkTrykk();
  munn.setPixelColor(7, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  // sjekkTrykk();
  munn.setPixelColor(6, munn.Color(0, 0, 0));
  munn.setPixelColor(8, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  // sjekkTrykk();
  munn.setPixelColor(5, munn.Color(0, 0, 0));
  munn.setPixelColor(9, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  // sjekkTrykk();
  munn.setPixelColor(4, munn.Color(0, 0, 0));
  munn.setPixelColor(10, munn.Color(0, 0, 0));
  munn.show();
  // sjekkTrykk();
  oyeSnurr();

  munn.setPixelColor(3, munn.Color(0, 0, 0));
  munn.setPixelColor(11, munn.Color(0, 0, 0));
  munn.show();
  // sjekkTrykk();
  oyeSnurr();

  munn.setPixelColor(2, munn.Color(0, 0, 0));
  munn.setPixelColor(12, munn.Color(0, 0, 0));
  munn.show();
  // sjekkTrykk();

  oyeSnurr();
  // sjekkTrykk();
  munn.setPixelColor(1, munn.Color(0, 0, 0));
  munn.setPixelColor(13, munn.Color(0, 0, 0));
  munn.show();
  // sjekkTrykk();

  oyeSnurr();

  munn.setPixelColor(0, munn.Color(0, 0, 0));
  munn.setPixelColor(14, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  // sjekkTrykk();
  tidUte();

}

void tidUte() {
  for (int i = 0; i<4; i++) {
    blinking();
  }
}

void blinking() {
  munnPaa();
  munn.show();
  delay(200);
  munnAv();
  munn.show();
  delay(200);
}

void sjekkTrykk() {
  if (digitalRead(gronnS1) == LOW) {
        svarS1 = 1;
        Serial.println("S1 true");
    };

    if (digitalRead(rodS1) == LOW) {
        svarS1 = 2;
        Serial.println("S1 false");
    };

    if (digitalRead(gronnS2) == LOW) {
        svarS2 = 1;
        Serial.println("S2 true");
    };

    if (digitalRead(rodS2) == LOW) {
        svarS2 = 2;
        Serial.println("S2 false");
    }
}

void sjekkSvar(int riktig) {
    if (svarS1 == riktig) {
        //Grønn pære lyser
    } else if (svarS1 != riktig) {
        //Rød pære lyser
    }
    if (svarS2 == riktig) {
        //Grønn pære lyser
    } else if (svarS2 != riktig) {
        //Rød pære lyser
    }

    delay(5000);


}
