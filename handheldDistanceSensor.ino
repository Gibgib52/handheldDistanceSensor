#include <LiquidCrystal.h>
#include <AceSorting.h>
#include <AlignedJoy.h>
using ace_sorting::shellSortKnuth;

#define joyXpin 0
#define joyYpin 1

#define endl "\n"

// why is lcd not global? why cant Menu.c or Ranger.h see it??????????
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy stick(joyXpin, joyYpin);

#include "Ranger.h"
#include "GJoy.h"
#include "Menu.h"

// TODO: add temp/humididy sensor and correction for temp/humid

void setup() {
  lcd.begin(16, 2);
  lcd.print("starting...");

  // start serial
  lcd.setCursor(0, 1);
  lcd.print("s");
  Serial.begin(9600);
  // while(!Serial){} // do nothing while serial is starting
  // Serial.println("serial started");
  lcd.print("S");

  // start ranger
  lcd.print("r");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  float tmpRng = getRange();
  lcd.print(tmpRng);
  lcd.print("R");

  // button
  pinMode(trigButton, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("done! press btn");


  // testing
  // lcd.clear();
  // lcd.write();

  while(true){
    if(waitForInput() == BTN){
      menuMain();
    }
  }
}

int update = 0; // counts up on failure, shows display still working
void loop() {
  // int in = waitForInput();
  // if(in == BTN) {
  //   dsplyRng = avgRange(1);
  //   lcd.clear();
  //   lcd.print(dsplyRng);
  // }

  update++;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("in loop() ");
  lcd.print(update);
  lcd.setCursor(0,1);
  lcd.print("something went wrong.");

  delay(100);
}





