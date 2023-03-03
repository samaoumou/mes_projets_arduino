#include <IRremote.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int humidity, temperature;
int buzz=8;
int ventilo = 9;
int led = 10;
const char DIN_RECEPTEUR_INFRAROUGE = 3;                      //le pin de donée du recepteur infra
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE); //ici on crée un objet
decode_results messageRecu;                   //pour décoder le message reçu en hexadécimal
StaticJsonDocument<50> doc;
JsonObject object;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  noTone(buzz);
  object = doc.to<JsonObject>();
  pinMode(buzz, OUTPUT);
  pinMode(ventilo, OUTPUT);
    monRecepteurInfraRouge.enableIRIn();
    monRecepteurInfraRouge.blink13(true);
}
void loop()
{
        humidity = dht.readHumidity();
        temperature = dht.readTemperature();
        //object["humidity"] = humidity;
        //object["temperature"] = temperature;
        //serializeJson(doc, Serial); //methode qui permet d'imposer le sérial notre format JSON
        Serial.println("");    //pour permettre d'afficher les données sous format JSON
        Serial.print(temperature);
        Serial.print("/");
        Serial.println(humidity);
       
        delay(2000);
               if(temperature>30){
                  tone(buzz,1000,0);
                  delay(1500);
                  noTone(buzz);
                  digitalWrite(ventilo, HIGH);
                  }
               else{
                  digitalWrite(ventilo, LOW);
                  noTone(buzz);
                }
                 
//ici on la partie commande
            if (monRecepteurInfraRouge.decode(&messageRecu))
            {
            Serial.println(messageRecu.value,HEX);
            delay(500);
            if(messageRecu.value==0xFFA25D){
              digitalWrite(ventilo, HIGH);
              digitalWrite(10, HIGH);
             
             
            }
            if(messageRecu.value==0xFF629D){
              digitalWrite(ventilo, LOW);
              digitalWrite(10, LOW);
             
            }
            monRecepteurInfraRouge.resume();
            }
            delay(1);
//pour l'interface
char etat= Serial.read();
if (etat == '1')
{
digitalWrite(ventilo, HIGH);
}
else if (etat == '0')
{
  digitalWrite(ventilo, LOW);
  }
  Serial.println(etat);
  //delay(1000);
                         
}
