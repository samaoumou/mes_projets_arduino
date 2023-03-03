#include "SPI.h"
#include "MFRC522.h"

#define RST_PIN 9 // RES pin
#define SS_PIN  10 // SDA (SS) pin

byte readCard[4];
String cardID = "20C3935E"; // remplacer par l'ID de votre tag
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  while (getID()) {
    if (tagID == cardID) {
      Serial.println("Accès garanti");
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }
    else {
      Serial.println("Accès refusé");
    }
    Serial.print("ID: ");
    Serial.println(tagID);
    delay(2000);
    digitalWrite(6, LOW);
  }
}

boolean getID() {
  if (! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  if (! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";
  
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}
