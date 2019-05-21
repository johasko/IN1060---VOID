#include <Wire.h>
#include <SPI.h>
#include <RFID.h>

#define SS_PIN        10
#define RST_PIN       9

RFID rfid(SS_PIN, RST_PIN);

const int power = 7;
const int led = 8; 
int serNum[5];
int kategori;

int cards[][5] = {{138,84,37,131,120}};

#define SLAVE_ADDR    9
#define ANSWER_SIZE   1
byte svar[ANSWER_SIZE];

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initierer SPI bus for RFID-scanner
  rfid.init();
  pinMode(power, OUTPUT);
  digitalWrite(power, LOW);
  Wire.begin(SLAVE_ADDR);
  Wire.onRequest(requestEvent);
}

void requestEvent() {
  int kort; // Kategorien bestemmes ut i fra rfid-kortets forste rekke med ID.
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            kort = rfid.serNum[1];  
        }
        
        if(kort == 197){
            kategori = 1;
        }else if(kort == 84){
            kategori = 2;
        }

        Wire.write(kategori);
    }
    
    rfid.halt();
}

void loop() {
  delay(50);
}
