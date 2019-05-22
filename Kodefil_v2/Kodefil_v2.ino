#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>               // Required for 16 MHz Adafruit Trinket
#endif

#include <Wire.h>                     // Library for sammenkobling av arduinoer

#define MUNN                7
#define OYNE                8

#define SLAVE_ADDR          9              //Definerer nummer for slave-Arduino
#define ANSWER_SIZE         1              //Størrelse på forventet svar fra slave

#define PIXELMUNN           15             //Antall LEDs i munn
#define PIXELOYE            12             //Antall LEDs i oynene

unsigned long forrigeTid =  0;

int forsinkelseSnurr =      125;

const int gronnL1 = 5;
const int rodL1 =   6;
const int gronnL2 = 4;
const int rodL2 =   3;
const int gronnS1 = 9;
const int rodS1 =   10;
const int gronnS2 = 11;
const int rodS2 =   12;

//1 = true, 2 = false
int svarS1 = 0;
int svarS2 = 0;

int kort;

//1 = true, 2 = false
int svarKat1[5] = {1, 1, 2, 1,2};
int svarKat2[5] = {2, 2, 1, 2, 1};


Adafruit_NeoPixel munn(PIXELMUNN, MUNN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oyne(PIXELOYE, OYNE, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);
  delay(3000);                       //Sikkerhetsdelay ved oppstart for å hindre kortslutting
  Wire.begin();                      //Initialiserer kobling mellom de to arduinoene
  munn.begin();                      // Initialiserer LED-strips
  oyne.begin();
  munn.setBrightness(40);            //Justerer lysstyrke på LEDs
  oyne.setBrightness(40);
  pinMode(gronnS1, INPUT_PULLUP);    //Reverserer input-signal slik at de alltid sender HIGH, og programmet lytter etter LOW
  pinMode(rodS1, INPUT_PULLUP);      //Dette må gjøres siden knappene kun har to 'pins', og vil gi merkelige resultater ellers
  pinMode(gronnS2, INPUT_PULLUP);
  pinMode(rodS2, INPUT_PULLUP);

  pinMode(gronnL1, OUTPUT);
  pinMode(rodL1, OUTPUT);
  pinMode(gronnL2, OUTPUT);
  pinMode(rodL2, OUTPUT);

}

void loop() {
  munn.clear();                     // Slår av alle pixler i munn
  oyne.clear();                     // Slår av alle pixler i øyne

  //Wire.beginTransmission(SLAVE_ADDR);
  //Wire.write(0);
  //Wire.endTransmission();
  svarS1 = 0;
  svarS2 = 0;
  kort = 0;
  delay(10);

  
  while (kort == 0) {
    Wire.requestFrom(SLAVE_ADDR, 1);
  
    while (Wire.available()) {
      kort = Wire.read();
     }
  }

  
  Serial.print("KategoriID: ");
  Serial.println(kort);
  velgKat(kort);

}

void velgKat(int kort) {
  if (kort == 1) {
    Serial.println("Kategori 1 valgt");
    spill(1);
  } else if (kort == 2) {
    Serial.println("Kategori 2 valgt");
    spill(2);
  }
}

void spill(int kat) {

  if (kat == 1) {
    for (int i = 0; i < sizeof(svarKat2); i++) {
    //Send signal til raspberry pi for lyd
    //delay(varighet av lydfil)?
    nedtelling();
    delay(2000);
    sjekkSvar(svarKat1[i]);
    if (svarKat1[i] == 1) {
      alleGronn();
    } else {
      alleRod();
    }
    delay(5000);
    munnAv();
    oyeAv();
    slukkLysKontroll();
    }
  } 
  else {
    for (int i = 0; i < sizeof(svarKat2); i++) {
    //Send signal til raspberry pi for lyd
    //delay(varighet av lydfil)?
    nedtelling();
    delay(1000);
    sjekkSvar(svarKat2[i]);
    if (svarKat2[i] == 1) {
      alleGronn();
    } else {
      alleRod();
    }
    delay(5000);
    munnAv();
    oyeAv();
    slukkLysKontroll();
    }
  }
  
}

void sjekkTrykk() {
  if (digitalRead(gronnS1) == LOW) {
        svarS1 = 1;
        bekreftTrykk(1);
        Serial.println("S1 true");
    };

    if (digitalRead(rodS1) == LOW) {
        svarS1 = 2;
        bekreftTrykk(1);
        Serial.println("S1 false");
    };

    if (digitalRead(gronnS2) == LOW) {
        svarS2 = 1;
        bekreftTrykk(2);
        Serial.println("S2 true");
    };

    if (digitalRead(rodS2) == LOW) {
        svarS2 = 2;
        bekreftTrykk(2);
        Serial.println("S2 false");
    }
}

void sjekkSvar(int riktig) {
    if (svarS1 == riktig) {
        digitalWrite(gronnL1, HIGH);
    } else if (svarS1 != riktig) {
        digitalWrite(rodL1, HIGH);
    }
    
    if (svarS2 == riktig) {
        digitalWrite(gronnL2, HIGH);
    } else if (svarS2 != riktig) {
        digitalWrite(rodL2, HIGH);
    }
}

/* For å unngå at programmet fryser fullstendig ved bruk av delay(), 
 * slik at f.eks. knappetrykk ikke registreres, lager vi en egen
 * metode for å oppnå forsinkelser i programmet mens knapper fremdeles
 * kan trykkes, og bruker dette der det er formålsmessig.
 */
void forsinkelse(int forsinkelse) { 
  forrigeTid = millis();
  while (millis() < forrigeTid + forsinkelse) {
    //Vent [forsinkelse] ms
    sjekkTrykk();
  }
}

boolean nedtelling() {

  munnPaa();
  munn.show();

  oyeSnurr();                        //Sørger for et 1500ms delay, totalt 13500ms nedtelling
  munn.setPixelColor(7, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  munn.setPixelColor(6, munn.Color(0, 0, 0));
  munn.setPixelColor(8, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  munn.setPixelColor(5, munn.Color(0, 0, 0));
  munn.setPixelColor(9, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  munn.setPixelColor(4, munn.Color(0, 0, 0));
  munn.setPixelColor(10, munn.Color(0, 0, 0));
  munn.show();
  
  oyeSnurr();
  munn.setPixelColor(3, munn.Color(0, 0, 0));
  munn.setPixelColor(11, munn.Color(0, 0, 0));
  munn.show();
  
  oyeSnurr();
  munn.setPixelColor(2, munn.Color(0, 0, 0));
  munn.setPixelColor(12, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  munn.setPixelColor(1, munn.Color(0, 0, 0));
  munn.setPixelColor(13, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();

  munn.setPixelColor(0, munn.Color(0, 0, 0));
  munn.setPixelColor(14, munn.Color(0, 0, 0));
  munn.show();

  oyeSnurr();
  tidUte();
  slukkLysKontroll();

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

//LIGHTS

void munnPaa() {                    //Setter alle LEDs i munnen til å være på med hvitt lys
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(255, 255, 255));

  }
}

void alleGronn() {                    //Setter alle LEDs i munnen til å være på med grønt lys
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(0, 255, 0));
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(0, 255, 0));
  }
  munn.show();
  oyne.show();
}

void alleRod() {                    //Setter alle LEDs i munnen til å være på med rødt lys
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(255, 0, 0));
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(255, 0, 0));
  }
  munn.show();
  oyne.show();
}

void munnAv() {                     //Slår av alle LEDs i munnen
  for (int i = 0; i < PIXELMUNN; i++) {
    munn.setPixelColor(i, munn.Color(0, 0, 0));
  }
}

void oyeSnurr() {
    oyne.clear();
  // oyeAv();                       //Starter med alle pixler slått av

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(255, 255, 255));
    oyne.show();
    forsinkelse(125);
  }

  for (int i = 0; i < PIXELOYE; i++) {
    oyne.setPixelColor(i, oyne.Color(0, 0, 0));
    oyne.show();
    forsinkelse(125);
  }

}

void oyeAv() {                    //Slår av lysene i øyne
  for (int j = 0; j < PIXELOYE; j++) {
      oyne.setPixelColor(j, oyne.Color(0, 0, 0));
      oyne.show();
      forsinkelse(125);
  }
}

void slukkLysKontroll() {
  digitalWrite(gronnL1, LOW);
  digitalWrite(rodL1, LOW);
  digitalWrite(gronnL2, LOW);
  digitalWrite(rodL2, LOW);
}

void bekreftTrykk(int spiller) {
  if (spiller == 1) {
    digitalWrite(gronnL1, HIGH);
    digitalWrite(rodL1, HIGH);
  }

  if (spiller == 2) {
    digitalWrite(gronnL2, HIGH);
    digitalWrite(rodL2, HIGH);
  }
}
