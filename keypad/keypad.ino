#include <Keypad.h>


int led = 10;
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
const String val= "157";
String input_password;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  input_password.reserve(32);
}

void loop(){
  char key = keypad.getKey();
   

 if (key){
    Serial.println(key);

    if(key == '*') {
      input_password = ""; // clear input password
    } else if(key == '#') {
      if(val == input_password) {
        delay(1000);
        Serial.println("password is correct");
        // DO YOUR WORK HERE
        
      } else {
        Serial.println("password is incorrect, try again");
        digitalWrite(led, HIGH);
        delay(2000);
        digitalWrite(led, LOW);
      }

      input_password = ""; // clear input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}

void delai(){
  input_password.reserve(32);
  delay(2000);
  input_password = "";
  
  }
