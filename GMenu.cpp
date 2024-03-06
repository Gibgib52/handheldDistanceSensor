#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"
#include "GDis.hpp"

// util funcs begin

void setupM(){
  userSamples = 1;
  mode = AVG;
  memRng = 52.52;
}

// main menu, or ranging menu
void menuMain(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);

    lcd.print(memRng);
    lcd.print(" cm");

    // print samples and mode
    lcd.setCursor(0,1);
    if(mode == AVG){
      lcd.print("avg ");
    } else if(mode == MED){
      lcd.print("med ");
    }
    lcd.print(userSamples);

    int in = waitForInput();
    if(in == BTN){
      lcd.setCursor(15,1);
      lcd.print("*");
      memRng = avgRange(userSamples, debug);
    } else if(in == RIGHT){
      menuSettings();
    } else if(in == LEFT){
      menuAlarm();
    }
    delay(UI_DELAY);
  }
}

void menuSettings(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("S");
    lcd.setCursor(0,0);

    lcd.print("smpls=");
    lcd.print(userSamples);

    lcd.setCursor(0,1);
    lcd.print("mode=");
    if(mode == AVG){
      lcd.print("avg");
    }else if(mode == MED){
      lcd.print("med");
    }

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
    } else if(in == BTN){
      // change mode on btn down
      if(mode == AVG){
        mode = MED;
      } else if (mode == MED){
        mode = AVG;
      }
      waitForBtnUp();
    }
    delay(UI_DELAY);
  }
}

void menuTest(){
  waitForCenter();
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("T");
    lcd.setCursor(0,0);


    lcd.print("debug=");

    if(debug){
      lcd.print("true");
    } else {
      lcd.print("false");
    }

    int in = waitForInput();
    if(in == LEFT){
      menuSettings();
    } else if(in == RIGHT){
      ;
    } else if(in == UP){
      ;
    } else if(in == DOWN){
      // lcd.setCursor(0,1);
      // lcd.write(1);
    } else if (in == BTN){ // toggle debug on BTN
      if(debug){
        debug = false;
      } else{
        debug = true;
      }
      delay(100);
    }
    delay(UI_DELAY);
  }
}

int prescribedDist;
void menuAlarm(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("A");
    lcd.setCursor(0,0);

    lcd.print("pDist=");
    lcd.print(prescribedDist);
    waitForBtnUp();

    int in = waitForInput();
    if(in == BTN){
      alarmLoop();
    } else if(in == RIGHT){
      menuMain();
    } else if(in == LEFT){
      ;
    } else if(in == UP){
      prescribedDist++;
    } else if(in == DOWN){
      prescribedDist--;
    }
    delay(UI_DELAY);
  }
}

void alarmLoop(){
  float pDistFloat = (float)prescribedDist;
  float prevAlarmDist = 0;
  delay(200); // to stop instant break
  while(true) {
    float dist = avgRange(userSamples, debug);
    
    lcd.clear();
    // header
    lcd.setCursor(15,0);
    lcd.print("A");
    lcd.setCursor(15,1);
    lcd.print("*");
    lcd.setCursor(0,0);

    lcd.print("dist=  ");
    lcd.print(dist);

    lcd.setCursor(0,1);
    lcd.print("prvAlr=");
    lcd.print(prevAlarmDist);

    if(dist < pDistFloat){
      prevAlarmDist = dist;
      lcd.setCursor(0,0);
      lcd.print("*ALARM*");
    }
    delay(500);
    if(joyBtnDown()){
      break;
    }
  }
}
