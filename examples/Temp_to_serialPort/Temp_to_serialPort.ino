#include <thermo.h>

#define THERMOCOUPLEPIN A2

kThermocouple myTC = kThermocouple(THERMOCOUPLEPIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int Temp;

  //Show temperature read directly from analog port
  Temp = myTC.getTempWithFilter();

  //Show the temperature using a digital filter at the entrance
  //Temp = myTC.getTempDirect();
  
  Serial.println(Temp);

  delay(100);
}
