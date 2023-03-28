#include <DS3231.h>

DS3231  monRTC(SDA, SCL);

void setup()
{
  Serial.begin(9600);
  monRTC.begin();
  
  //monRTC.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //monRTC.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //monRTC.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
}

void loop()
{
  Serial.print(monRTC.getDOWStr());
  Serial.print(" ");
  
  Serial.print(monRTC.getDateStr());
  Serial.print(" -- ");
  
  Serial.println(monRTC.getTimeStr());
  
  delay (1000);
}
