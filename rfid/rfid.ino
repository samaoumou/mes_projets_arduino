#include <SPI.h>
#include <RFID.h>

const char DOUT_LED_ROUGE = 2;
const char DOUT_LED_VERTE = 3;

RFID monModuleRFID(10,9);

int UID[5]={};
int MASTERKEY[5]={67,139,127,198,113};

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  monModuleRFID.init();  
  pinMode(DOUT_LED_ROUGE, OUTPUT);
  pinMode(DOUT_LED_VERTE, OUTPUT);
  digitalWrite(DOUT_LED_ROUGE, LOW);
  digitalWrite(DOUT_LED_VERTE, LOW);

}

void loop()
{
    if (monModuleRFID.isCard()) {  
          if (monModuleRFID.readCardSerial()) {        
            Serial.print("L'UID est: ");
            for(int i=0;i<=4;i++)
            {
              UID[i]=monModuleRFID.serNum[i];
              Serial.print(UID[i],DEC);
              Serial.print(".");
            }
            Serial.println("");
          }
          
          if (UID[0] == MASTERKEY[0]
           && UID[1] == MASTERKEY[1]
           && UID[2] == MASTERKEY[2]
           && UID[3] == MASTERKEY[3]
           && UID[4] == MASTERKEY[4])
          {
              digitalWrite(DOUT_LED_VERTE, HIGH);
              delay(500);
              digitalWrite(DOUT_LED_VERTE, LOW);
          }
          else
          {
              digitalWrite(DOUT_LED_ROUGE, HIGH);
              delay(500);
              digitalWrite(DOUT_LED_ROUGE, LOW);
          }          
          monModuleRFID.halt();
    }
    delay(1);    
}
