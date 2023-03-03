#include <IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE = 11;
int buzz = 6;
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;

void setup()
{
Serial.begin(9600);
 pinMode(6, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(buzz, OUTPUT);
 noTone(buzz);
monRecepteurInfraRouge.enableIRIn();
monRecepteurInfraRouge.blink13(true);
}

void loop()
{
if (monRecepteurInfraRouge.decode(&messageRecu))
{
Serial.println(messageRecu.value,HEX);
delay(500);
if(messageRecu.value==0xFF5AA5){
    tone(buzz,1000,0);

  
  
}
  if(messageRecu.value==0xE090AB93){
         
    noTone(buzz);
    
}
monRecepteurInfraRouge.resume();
}
delay(1);
}
