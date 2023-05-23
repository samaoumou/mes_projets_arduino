/* 
 * Code d'exemple pour un capteur à ultrasons HC-SR04.
 */

/* Constantes pour les broches */
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
#include "Servo.h"

Servo issa; // création de l'objet "servo"

 /* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

/** Fonction setup() */
void setup() {
  issa.attach(5); // attache le servo au pin spécifié
   pinMode(A1, INPUT);
   
  /* Initialise le port série */
  Serial.begin(9600);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}
 
/** Fonction loop() */
void loop() {
  
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float hauteur = measure / 2.0 * SOUND_SPEED;
   
  /* Affiche les résultats en mm, cm et m */
  Serial.print(F("Distance: "));
  Serial.print(hauteur);
  Serial.print(F("mm ("));
  //Serial.print(distance_mm / 10.0, 2);
  //Serial.print(F("cm, "));
  //Serial.print(distance_mm / 1000.0, 2);
  //Serial.println(F("m)"));
   
  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  delay(500);
   
  /*On va considere la distance en cm pour commander ton servo moteur*/
  /*et la hauteur par défaut je l'ai considéré égal à 150*/
     if (hauteur < 150) { issa.write(0); }
   if (hauteur > 150) { issa.write(180); }
}
