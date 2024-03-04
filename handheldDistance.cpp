#include <Arduino.h>

#include <LiquidCrystal.h>
#include <AlignedJoy.h>

#include "globals.h"
#include "Ranger.hpp"

#define trigButton 5
#define joyXpin 0
#define joyYpin 1


// sketch here
int main(){
  // do not remove
  init();
  Serial.begin(9600);
  Serial.println("serial started");


  // sketch begin

  const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  AlignedJoy stick(joyXpin, joyYpin);

  lcd.begin(16,2);
  lcd.print("working");

  while(true){
    lcd.clear();
    float dist = getRange();
    lcd.print(dist);
    // delay(1000);
  }

  // sketch end

  // do not remove
  Serial.flush();
  return 0;
}

