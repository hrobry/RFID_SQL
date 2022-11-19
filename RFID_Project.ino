
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN      5
#define  SS_PIN      53


MFRC522 RFID (SS_PIN , RST_PIN);

 String dataSend, data;


void setup() {
  Serial.begin(9600);
  SPI.begin();
  RFID.PCD_Init();
  

}

void loop() {

if(!RFID.PICC_IsNewCardPresent()){
  return;
}
if(! RFID.PICC_ReadCardSerial()){
  return;
}


  //RFID.PICC_DumpDetailsToSerial(&(RFID.uid));
  //Serial.println(F("Card UIDDDDD:"));
  for (byte i = 0; i < RFID.uid.size; i++) {
   
   
    data = String(RFID.uid.uidByte[i]);
   dataSend+=data;
  
  }
 RFID.PICC_HaltA(); 
  dataSend+="\n";
  Serial.print(dataSend);
  dataSend="";
  // put your main code here, to run repeatedly:

}
