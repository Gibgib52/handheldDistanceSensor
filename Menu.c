#include "Menu.h"
#include "Ranger.h"

///////////////////////
// flashes text on lcd
// default 2 flashes, 100 ms interval
// preserves screen content(excluding what txt overwrites), doesnt lcd.clear()
void flashTxt(char* txt, int flashes = 2, int interval = 100, int x = 0, int y = 0){
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

// use for end of a menu... self explanatory
void menuEnd(){
  flashTxt("* END *");
}

/////////////////////////////////////////////

void menuSettings(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("S");
    lcd.setCursor(0,0);

    lcd.print("smpls=");
    lcd.print(samples);

    int in = waitForInput();
    if(in == LEFT){
      menuMain();
    } else if(in == UP){
      if(samples < MAX_SAMPLES){
        samples++;
      }
    } else if(in == DOWN){
      if(samples > 1){
        samples--;
      }
    } else if(in == RIGHT) {
      menuTest();
    }
    delay(UI_DELAY);
  }
}

// trying to write other chars from the charmap
void menuTest(){
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("T");
    lcd.setCursor(0,0);

    int in = waitForInput();
    if(in == LEFT){
      menuSettings();
    } else{
      // en is at 1100 1111 on the charmap, reverse it to 1111 1110
      char en = 0b1111110;
      lcd.write(en);
    }
    delay(UI_DELAY);
  }
}


// TODO: finish
int prescribedDist = 10;
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

    float dist = avgRange(samples);
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

// makes periodic measurements, if they fall
// below prescribedDist alert the user
const int changeDelay = 100; // delay of changing prescribedDist
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
      menuEnd();
    } else if(in == UP){
      prescribedDist++;
    } else if(in == DOWN){
      prescribedDist--;
    }
    delay(UI_DELAY);
}

// mainmenu / ranging menu
float dsplyRng;
void menuMain(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);

    lcd.print(dsplyRng);
    lcd.print(" cm");

    int in = waitForInput();
    if(in == BTN){
      lcd.setCursor(15,1);
      lcd.print("*");
      dsplyRng = avgRange(samples);
    } else if(in == RIGHT){
      menuSettings();
    } else if(in == LEFT){
      menuAlarm();
    }
    delay(UI_DELAY);
  }
}

