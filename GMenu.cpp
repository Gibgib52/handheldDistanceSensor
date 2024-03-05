#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"

// util funcs begin

void setupM(){
  userSamples = 1;
  memRng = 5.2;
}


// flashes text on lcd
// default 2 flashes, 100 ms interval
// preserves screen content(excluding what txt overwrites), doesnt lcd.clear()
void flashTxt(char* txt, int flashes = 2, int interval = 200, int x = 0, int y = 0){
  int len = strlen(txt);
  for(int i = 0; i < flashes; i++){
    // -- on
    lcd.setCursor(x,y);
    lcd.print(txt);
    delay(interval);

    // -- off
    lcd.setCursor(x,y);
    // print blanks len times
    for(int j = 0; j < len; j++){
      lcd.print(" ");
    }
    delay(interval);
  }
}

// util funcs end

// menu funcs start

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

int prescribedDist;
const int changeDelay = 200;
void menuAlarm(){
  lcd.clear();
  lcd.setCursor(15,0);
  lcd.print("A");
  lcd.setCursor(0,0);

  lcd.print("pDist=");
  lcd.print(prescribedDist);


  int in = waitForInput();
    if(in == BTN){
      alarmLoop();
    } else if(in == RIGHT){
      menuMain();
    } else if(in == LEFT){
      ;
    } else if(in == UP){
      prescribedDist++;
      delay(changeDelay);
    } else if(in == DOWN){
      prescribedDist--;
      delay(changeDelay);
    }
    delay(UI_DELAY);
}

void alarmLoop(){
  float pDistFloat = (float)prescribedDist;
  while(true) {
    lcd.clear();
    // header
    lcd.setCursor(15,0);
    lcd.print("A");
    lcd.setCursor(15,1);
    lcd.print("*");
    lcd.setCursor(0,0);

    float dist = avgRange(userSamples);
    lcd.print("dist=");
    lcd.print(dist);
    if(dist < pDistFloat){
      flashTxt("* ALARM *", 2, 100, 0, 1);
    }
    if(joyBtnDown()){
      break;
    }
  }
}
