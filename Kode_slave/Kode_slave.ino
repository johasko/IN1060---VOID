#include <Wire.h>
#include <SPI.h>
#include <RFID.h>

#define SS_PIN        10
#define RST_PIN       9

RFID rfid(SS_PIN, RST_PIN);

int serNum[5];
int kategori;

#define SLAVE_ADDR    9
#define ANSWER_SIZE   1                     //Forventet lengde paa etterspurt svar

void setup() {
  Serial.begin(9600);
  SPI.begin();                              // Initierer SPI bus for RFID-scanner
  rfid.init();
  Wire.begin(SLAVE_ADDR);                   //Starter Wire-connection og initierer requestEvent paa foresporsel fra master
  Wire.onRequest(requestEvent);             //
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
