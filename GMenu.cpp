#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"

void setupM(){
  userSamples = 1;
  memRng = 5.2;
}


// main menu, or ranging menu
void menuMain(){
  // delay on menu switch
  delay(UI_SWITCH_DELAY);

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
      menuSettings();
      ;
    } else if(in == LEFT){
      // menuAlarm();
      ;
    }
    delay(UI_DELAY);
  }
}

void menuSettings(){
  delay(UI_SWITCH_DELAY);

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
      menuTest();
      ;
    }
    delay(UI_DELAY);
  }
}

void menuTest(){
  delay(UI_SWITCH_DELAY);
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("T");
    lcd.setCursor(0,0);

    int in = waitForInput();
    if(in == LEFT){
      menuSettings();
    } else if(in == RIGHT){
      ;
    } else if(in == UP){
      ;
    } else if(in == DOWN){

    } else if (in == BTN){
      ;
    } else{
      // en is at 1100 1111 on the charmap, reverse it to 1111 1110
      char en = 0b1111110;
      lcd.write(en);
    }
    delay(UI_DELAY);
  }
}

// template for menu structure
void menuTemplate(){
  delay(UI_SWITCH_DELAY);
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("?"); // replace this with 1 char to describe menu
    lcd.setCursor(0,0);

    int in = waitForInput();
    if(in == LEFT){
      ;
    } else if(in == RIGHT){
      ;
    } else if(in == UP){
      ;
    } else if(in == DOWN){

    } else if (in == BTN){
      ;
    } else{
      ;
    }
    delay(UI_DELAY);
  }
}

