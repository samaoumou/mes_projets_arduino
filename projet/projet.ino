#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
#define DHTPIN 2  
#define DHTTYPE    DHT11     // DHT 11
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
int buzz=3;
void setup() {
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  pinMode(buzz,OUTPUT);
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
noTone(buzz);

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);

  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temp: ")); 
    Serial.println(event.temperature);
    lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
     if(event.temperature>30){
    tone(buzz,1000,0);
    delay(1500);
    noTone(buzz);
    //ventilo
    }
 
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.println("/");
   Serial.print(F("Hum: ")); 
   Serial.println(event.relative_humidity);
       lcd.setCursor(0, 1);
    lcd.print(F("Hum: "));
    lcd.print(event.relative_humidity);
 
  }
 
   
}

/*#include <IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE = 2;
int ventilo = 6;
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;

void setup()
{
Serial.begin(9600);
 pinMode(6, OUTPUT);
 pinMode(8, OUTPUT);
monRecepteurInfraRouge.enableIRIn();
monRecepteurInfraRouge.blink13(true);
}

void loop()
{
if (monRecepteurInfraRouge.decode(&messageRecu))
{
Serial.println(messageRecu.value,HEX);
delay(500);
if(messageRecu.value==0xFF30CF){
  digitalWrite(ventilo, HIGH);
  digitalWrite(8, HIGH);
  
  
}
if(messageRecu.value==0xFF18E7){
  digitalWrite(ventilo, LOW);
  digitalWrite(8, LOW);
  
}
monRecepteurInfraRouge.resume();
}
delay(1);
}*/
