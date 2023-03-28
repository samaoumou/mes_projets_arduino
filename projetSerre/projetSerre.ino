/*
  ReadField
  
  Description: Demonstates reading from a public channel which requires no API key and reading from a private channel which requires a read API key.
               The value read from the public channel is the current outside temperature at MathWorks headquaters in Natick, MA.  The value from the
               private channel is an example counter that increments every 10 seconds.
  
  Hardware: ESP32 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires installation of EPS32 core. See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/
//#include <Servo.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <WiFi.h>
#define servo 11
#define photo 21  // composante photoresistor sur la pin A1
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
Servo servoToit;
WiFiClient  client;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  servoToit.attach(11); // attache le servo au pin spécifié
  pinMode(photo, INPUT);
  pinMode(RED, OUTPUT);  // qui permet de manipuler la led tricolore avec les différentes couleures 
  pinMode(GRN, OUTPUT); // et de les définir comme les sortie 
  pinMode(BLU, OUTPUT);
  Serial.begin(115200);  //Initialize serial 
  Serial.println(F("DHTxx test!"));
  pinMode(ventilo, OUTPUT);
  pinMode(buzz, OUTPUT);
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
   if (value < 80) { servoToit.write(0); }
   if (value >= 80) { servoToit.write(180); }
}



 

 
