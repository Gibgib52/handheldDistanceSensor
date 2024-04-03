#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"
#include "GDis.hpp"
#include <ArxContainer.h>
#include <string.h>

#include "helpFunc.hpp"

// util funcs begin

void setupM(){
  // defaults
  userSamples = 1;
  mode = AVG;
  memRng = 52.52;
  light = false;
  buzzFlag = false;


  pinMode(LIGHT_PIN, OUTPUT);
}


//TODO these menus should be made into objects 

// main menu, or ranging menu
void menuMain(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);


    // range handling
    if(memRng > MAX_RANGE){
      lcd.setCursor(10, 0);
      lcd.print(">MAX");
    }else if (memRng < MIN_RANGE){
      lcd.setCursor(10, 0);
      lcd.print(">MIN");
    }
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

      // play correct sound
      if(memRng > MAX_RANGE){
        buzzFault();
      }else if (memRng < MIN_RANGE){
        buzzFault();
      }else{
        buzzS();
      }
      
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
    lcd.setCursor(14,0);
    lcd.print("S1");
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
      menuSettings2();
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

void menuSettings2(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(14,0);
    lcd.print("S2");
    lcd.setCursor(0,0);


    // print light state
    lcd.print("light=");
    if(light){
      lcd.print("on");
    } else {
      lcd.print("off");
    }


    int in = waitForInput();
    if(in == LEFT){
      menuSettings();
    } else if(in == UP){
      digitalWrite(LIGHT_PIN, HIGH);
    } else if(in == DOWN){
      digitalWrite(LIGHT_PIN, LOW);
    } else if(in == RIGHT) {
      menuSettings3();
    } else if(in == BTN){
      waitForBtnUp();
      if(light){
        light = false;
      }else if(!light){
        light = true;
      }
      digitalWrite(LIGHT_PIN, light);
    }

    delay(UI_DELAY);
  }
}

void menuSettings3(){
  waitForCenter();
  while(true){
    lcd.clear();
    lcd.setCursor(14,0);
    lcd.print("S3");
    lcd.setCursor(0,0);

    lcd.print("buzz=");
    
    if(buzzFlag){
      lcd.print("true");
    }else{
      lcd.print("false");
    }

    int in = waitForInput();
    if(in == LEFT){
      menuSettings2();
    } else if(in == UP){
      ;
    } else if(in == DOWN){
      ;
    } else if(in == RIGHT) {
      menuTest();
    } else if(in == BTN){
      waitForBtnUp();
      
      // toggle buzzflag
      if(buzzFlag){
        buzzFlag = false;
      }else{
        buzzFlag = true;
      }
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
      menuSettings3();
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
      buzzUp();
      alarmLoop();
      buzzDown();
    } else if(in == RIGHT){
      menuMain();
    } else if(in == LEFT){
      menuHelp();
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
    lcd.setCursor(15,1);
    lcd.print("*");
    lcd.setCursor(0,0);
    float dist = avgRange(userSamples, debug);
    lcd.setCursor(15,1);
    lcd.print(" ");
    lcd.setCursor(0,0);
    
    lcd.clear();
    // header
    lcd.setCursor(15,0);
    lcd.print("A");
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
      buzzArp();
    }
    delay(500); // rescan every 500 ms
    if(joyBtnDown()){
      break;
    }
  }
}


const int pageDelay = 100;
void menuHelp(){
  waitForCenter();

  int y = 0;
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("H");
    lcd.setCursor(0,0);

    lcd.print("pg=");
    lcd.print(y);

    String title = getTitle(y);
    lcd.setCursor(0,1);
    lcd.print(title);

    waitForBtnUp();
    int in = waitForInput();
    if(in == BTN){
      waitForBtnUp();
      lcd.setCursor(0,0);
      printHelp(y);
    } else if(in == RIGHT){
      menuAlarm();
    } else if(in == LEFT){
      ;
    } else if(in == UP){
      y--;
      delay(pageDelay);
    } else if(in == DOWN){
      y++;
      delay(pageDelay);
    }
    delay(UI_DELAY);
  }
}

// each y value should have a function and title associated with it
// when btnDown, enter that function ( and display help text with it)


