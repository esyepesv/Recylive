#include <SPI.h>     
#include <MFRC522.h> // librerias id

#include "HX711.h"   // librerias peso

// pines id
#define RST_PIN  9     
#define SS_PIN  10
//pines pesa
const int DOUT=A1;
const int CLK=A0;

MFRC522 mfrc522(SS_PIN, RST_PIN);
HX711 balanza;

String str;

void setup() {
  Serial.begin(9600);
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();
  
  balanza.begin(DOUT, CLK);
  balanza.set_scale(-247823.2);
  balanza.tare(20);
}

void loop() {
// id:
  String id;
    if( !mfrc522.PICC_IsNewCardPresent()) return;  // si no hay una tarjeta presente retorna al loop
    if( !mfrc522.PICC_ReadCardSerial()) return;    // si no puede obtener datos de la tarjeta retorna al loop
      
    
    for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){   // si el byte leido es menor a 0x10
        id += "0";
        }
        else{         
        id += "";     
        }
      id += String(mfrc522.uid.uidByte[i], DEC);  // byte del UID leido en hexadecimal  
    } 
    //Serial.println();
    mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta



//peso:

  float peso = balanza.get_units(20)*1000;
  peso = round(peso);  //se redondea el valor para no tener decimales
  
  //condicion peso negativo
  if(peso<0) peso = 0;
  
  
  str = id+","+String(int(peso));
  Serial.println(str);

  delay(500);
}
