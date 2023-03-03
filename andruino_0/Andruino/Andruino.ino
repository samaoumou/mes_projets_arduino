/***********************************************************************/
/*                           ANDRUINO V1.0                             */
/*                                                                     */
/* Programme nécessaire au fonction de l'Application Android Andruino  */
/*                                                                     */
/*                 le 27/02/2015 par Alexandre Pailhoux                */
/*                                                                     */
/*           Schéma et App sur:  http://les-electroniciens.com         */
/***********************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial HC06(13,12);

String messageRecu = "";
float valeurAnalog = 0;
/***********************************************************************/
/*                              INIT                                   */
/***********************************************************************/
void setup() 
{
  HC06.begin(9600);  
  for(int i=0;i<=11;i++)
  {
    pinMode(i, OUTPUT); 
    digitalWrite(i, LOW);
  }
}
/***********************************************************************/
/*                         BOUCLE INFINIE                              */
/***********************************************************************/ 
void loop() 
{
 while(HC06.available()) 
 {
  delay(3);
  char c = HC06.read();
  messageRecu += c;
 }
 if (messageRecu.length() >0) 
 {  
  /*****************************************************/
  /*                  DIGITAL 0                        */
  /*****************************************************/
  if ((messageRecu.indexOf("D00") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(0,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(0,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 1                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D01") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(1,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(1,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 2                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D02") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(2,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(2,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 3                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D03") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(3,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(3,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(3,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 4                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D04") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(4,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(4,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 5                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D05") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(5,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(5,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(5,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 6                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D06") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(6,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(6,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(6,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 7                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D07") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(7,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(7,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 8                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D08") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(8,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(8,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 9                        */
  /*****************************************************/
  else if ((messageRecu.indexOf("D09") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(9,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(9,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(9,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 10                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("D10") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(10,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(10,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(10,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 11                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("D11") != -1)) 
  {
   if ((messageRecu.indexOf("ON") != -1)) 
   {digitalWrite(11,HIGH);}
   else if((messageRecu.indexOf("OFF") != -1)) 
   {digitalWrite(11,LOW);}   
   else
   {   
     messageRecu =  messageRecu.substring(4,7);
     analogWrite(11,messageRecu.toInt());
   }  
  }
  /*****************************************************/
  /*                    ANALOG 0                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A0") != -1)) 
  {
   valeurAnalog = analogRead(0);   
   valeurAnalog = valeurAnalog*4.8/1000;
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
  /*                    ANALOG 1                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A1") != -1)) 
  {
   valeurAnalog = analogRead(1);   
   valeurAnalog = valeurAnalog*4.8/1000; 
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
  /*                    ANALOG 2                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A2") != -1)) 
  {
   valeurAnalog = analogRead(2);   
   valeurAnalog = valeurAnalog*4.8/1000; 
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
  /*                    ANALOG 3                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A3") != -1)) 
  {
   valeurAnalog = analogRead(3);   
   valeurAnalog = valeurAnalog*4.8/1000;
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
  /*                    ANALOG 4                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A4") != -1)) 
  {
   valeurAnalog = analogRead(4);   
   valeurAnalog = valeurAnalog*4.8/1000;
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
  /*                    ANALOG 5                       */
  /*****************************************************/
  else if ((messageRecu.indexOf("A5") != -1)) 
  {
   valeurAnalog = analogRead(5);   
   valeurAnalog = valeurAnalog*4.8/1000;
   HC06.print(String(valeurAnalog));
  }
  /*****************************************************/
 }
 messageRecu="";
} 
