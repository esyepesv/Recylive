  #include <UnoWiFiDevEd.h>

// librerias id
#include <SPI.h>     
#include <MFRC522.h> 

// librerias peso
#include "HX711.h"   

//librerias esp8266
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "SoftwareSerial.h"
SoftwareSerial softSerial(0, 1); // RX, TX

// pines id
#define RST_PIN  9     
#define SS_PIN  10
//pines pesa
const int DOUT=A1;
const int CLK=A0;

MFRC522 mfrc522(SS_PIN, RST_PIN);
HX711 balanza;

//esp - thingspeak
const char* ssid     = "LISSETH";
const char* password = "3126632120";
WiFiClient  client;

unsigned long numeroCanal = 1724141;
const char * WriteAPIKey = "BVDXM9U1ZQRP5E1K" 


void setup() {
  Serial.begin(9600);
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();
  
  balanza.begin(DOUT, CLK);
  balanza.set_scale(-404672.89);
  balanza.tare(20);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Indicamos los datos de conexión para el monitor serial
  Serial.println("");
  Serial.println("Conectado WiFi");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client); 
}

void loop() {
// id:
  String id;
    if( !mfrc522.PICC_IsNewCardPresent()) return;  // si no hay una tarjeta presente retorna al loop
    if( !mfrc522.PICC_ReadCardSerial()) return;    // si no puede obtener datos de la tarjeta retorna al loop
      
    
    for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){   // si el byte leido es menor a 0x10
        id += " 0";
        }
        else{         
        id += " ";     
        }
      id += String(mfrc522.uid.uidByte[i], HEX);  // byte del UID leido en hexadecimal  
    }
        int identificacion = id.toInt();
    Serial.println();
    mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta



  //peso:
  float peso = balanza.get_units(20)*1000;


  //enviar a thingspeak
  ThingSpeak.setField(1, identificacion);
  ThingSpeak.setField(2, peso);

  // subimos los datos a nuestro canal en ThingSpeak
    //200 es el codigo tipico de una transmision OK en el protocolo HTTP
    int x = ThingSpeak.writeFields(numeroCanal, WriteAPIKey);
    if (x == 200) {
      Serial.println("Canal actualizado.");
    }
    else {
      Serial.println("Problema actualizando Canal, HTTP error code " + String(x));
    }

  delay(500);
}
