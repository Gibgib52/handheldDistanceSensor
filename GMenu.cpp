#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"

void setupM(){
  const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  userSamples = 1;
  memRng = 0;
}


// main menu, or ranging menu
void menuMain(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);

    lcd.print(memRng);
    lcd.print(" cm");

    int in = waitForInput();
    if(in == BTN){
      lcd.setCursor(15,1);
      lcd.print("*");
      memRng = avgRange(userSamples);
    } else if(in == RIGHT){
      // menuSettings();
      ;
    } else if(in == LEFT){
      // menuAlarm();
      ;
    }
    delay(UI_DELAY);
  }
}

void menuSettings(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("S");
    lcd.setCursor(0,0);

    lcd.print("smpls=");
    lcd.print(userSamples);

    int in = waitForInput();
    if(in == LEFT){
      menuMain();
    } else if(in == UP){
      if(userSamples < MAX_SAMPLES){
        userSamples++;
      }
    } else if(in == DOWN){
      if(userSamples > 1){
        userSamples--;
      }
    } else if(in == RIGHT) {
      // menuTest();
      ;
    }
    delay(UI_DELAY);
  }
}
