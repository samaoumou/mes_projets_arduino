/****************************************
 * ENREGISTREUR DE DONNEES
 * le 03.04.2016
 * par Alexandre Pailhoux
 * 
 * Ce programme permet de sauvegarger vos données au format csv sur une carte SD.
 * Vous pouvez ensuite ouvrir le fichier DONNEES.csv sous excel et créer facilement un graphique.
 * Cet exemple est adapté pour la lecture d'un capteur DHT
 * 
 * Nécessite les libraires DS3231 et DHT
 * Schéma de cablâge disponible sur www.les-electroniciens.com
 * 
 * Besoin d'aide? http://www.les-electroniciens.com/forum  
 */


/**************************************
 * Librairies
 */
#include <SD.h>
#include <SPI.h>
#include <DS3231.h> //Librairie à installer
#include "DHT.h"    //Librairie à installer

/**************************************
 * Affectation des broches
 */
#define CS_PIN 10
#define DHTPIN 2
#define DHTTYPE DHT22

/**************************************
 * Création des instances
 */
File monFichier;
DS3231  monRTC(SDA, SCL);
DHT monDHT(DHTPIN, DHTTYPE);

/**************************************
 * Initialisation
 */
void setup()
{
  Serial.begin(9600);
  monRTC.begin();
  monDHT.begin();

  Serial.print("Initialisation de la carte SD en cours...");
  if (SD.begin())
  {
    Serial.println(" Terminee.");
  } else
  {
    Serial.println(" Echec.");
    return;
  }  
  monFichier = SD.open("donnees.csv", FILE_WRITE);
  if (monFichier) 
  {   
    monFichier.println("Heure,Temperature,Humidite");
    Serial.println("");
    Serial.println("   Heure  | Temperature | Humidite");
    monFichier.close();    
  } 
}
/**************************************
 * Boucle Infinie
 */
void loop()
{  
  // On mesure par exemple l'humidité et la température.
  float humidite = monDHT.readHumidity();
  float temperature = monDHT.readTemperature();
  
  // On demande l'heure exacte au module Real Time Clock.
  String temps = String(monRTC.getTimeStr());

  // On met en forme la donnée au formar csv, c'est-à dire chaque paramètre séparé par une virgule.
  String donnee = temps + "," + String(temperature) + "," + String(humidite);

  // On enregistre la donnée 
  monFichier = SD.open("donnees.csv", FILE_WRITE); //Maximum 8 caractères avant le .csv
  if (monFichier) 
  {   
    monFichier.println(donnee);
    Serial.println(" " + temps + " |    " + String(temperature)+ "    |   " + String(humidite));
    monFichier.close();    
  } 
  else 
  {
    Serial.println("Impossible d'ouvrir le fichier");
  }  
  delay(60000);
}
