                                                                  /*Groupe 4 code de l'esp32*/
                                               /*le keypad et l'écran lcd par préference seront géré par l'arduino Mega*/       
/*ici on a l'ensemble des fichiers et bibliothèques utilisé*/
              #include <ESP32Servo.h>
              #include <LiquidCrystal.h>
              #include <WiFi.h>
              #include "secrets.h"
              #include "DHT.h"
              
/*la déclaration des différents pins utilisé*/
#define RED 14 //led tricolor(rouge)
#define GRN 12    //led tricolor(vert)
#define BLU 13  //led tricolor(blue)
#define DHTTYPE DHT11   // DHT 11
#define servo 19     //le pin du servoMoteur
#define photo 36  // composante photoresistor sur le pin 36
#define DHTPIN 23     // Digital pin connected to the DHT sensor
int digitalPin = 33; // pour le relais
int analogPin = 32; // pour le capteur de l'humidité du sol
int digitalVal; // digital readings
int analogVal; //analog readings


char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int ventilo = 22;
int buzz = 15;

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

  // lit et retourne moi une chaine de caractere en cas de problème de branchement.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("erreur de donnée")); // le message affiché quand il y a un mal branchement
       digitalWrite(RED, HIGH);
       digitalWrite(GRN, LOW);
       digitalWrite(BLU, LOW);
 
   delay(1000);
    return;
  }
  
  //float hif = dht.computeHeatIndex(f, h);
  //float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("HumiditéSerre: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C luminosité: "));  
  Serial.print(value);
  Serial.print(F(" HumiditéSol: "));
  Serial.println(analogVal);

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



 

 
