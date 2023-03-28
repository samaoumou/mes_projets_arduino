/*Groupe 4*/

int digitalPin = 33; // pour le relais
int analogPin = 32; // pour le capteur de l'humidité du sol
int digitalVal; // digital readings
int analogVal; //analog readings

#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <WiFi.h>
#define servo 11     //le pin du servoMoteur
#define photo 36  // composante photoresistor sur le pin 36
#include "secrets.h"
#include "DHT.h"
#define RED 14
#define GRN 12
#define BLU 13
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 23     // Digital pin connected to the DHT sensor
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int ventilo = 22;
int buzz = 15;
unsigned int lumiere;
Servo servoToit;     // on crée l'objet servoToit
WiFiClient  client;
DHT dht(DHTPIN, DHTTYPE);
void setup() {

  pinMode(digitalPin, OUTPUT); //pour initialiser le capteure de l'himudité
  digitalWrite(digitalPin, LOW);
  
  servoToit.setPeriodHertz(50); // Fréquence PWM pour le SG90
  servoToit.attach(11); // attache le servo au pin spécifié
  pinMode(photo, INPUT);
  pinMode(RED, OUTPUT);  // qui permet de manipuler la led tricolore avec les différentes couleures 
  pinMode(GRN, OUTPUT); // et de les définir comme les sortie 
  pinMode(BLU, OUTPUT);
  Serial.begin(115200);  //Initialize serial 
  Serial.println(F("DHTxx test!"));
  pinMode(ventilo, OUTPUT);
  pinMode(buzz, OUTPUT);
  int analogValue = analogRead(photo);
  
  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
}
void loop() {
  delay(2000);
  int statusCode = 0;
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("En cours de connexion: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");  //la connexion de l'esp affichage message
    Serial.println (WiFi.localIP ());
      // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  }
    float value = analogRead(photo);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("erreur de donnée")); // le message affiché quand il y a une errreure de branchement
       digitalWrite(RED, HIGH);
       digitalWrite(GRN, LOW);
       digitalWrite(BLU, LOW);
 
   delay(1000);
    return;
  }
  
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F(" luminosité: "));  
  Serial.println(value);

   delay(5000);
/*Cette partie consiste à faire l'arrosage automatique*/

   analogVal = analogRead(analogPin);               //lire la valeur retournée par le capteur de l'humidité
    if (analogVal<400){                              //si la capteur de l'humidité retourne une valeur<500
    digitalWrite(digitalPin, HIGH);                    //La pompe à eau arrose la plante
    } else {                            // sinon
    digitalWrite(digitalPin, LOW); //La pompe à eau arrête l'arrosage
    }
    delay(100);

  /*cette partie décrit le comportement du système en temps normal c'est à dire température inférieure à 30*/  
  if(t<30){
       digitalWrite(ventilo, LOW);
       digitalWrite(RED, LOW);
       digitalWrite(GRN, HIGH);
       digitalWrite(BLU, LOW);
 
   delay(1000);
    }
    else{
      digitalWrite(ventilo, HIGH);
       digitalWrite(RED, LOW);
       digitalWrite(GRN, LOW);
       digitalWrite(BLU, HIGH);
 
   delay(1000);
      }
      /*ici on dicte l'ouverture ou la fermeture du toit selon la luminosité mesurée*/
   if (value < 80) { servoToit.write(0); }
   if (value >= 80) { servoToit.write(180); }
}



 

 
