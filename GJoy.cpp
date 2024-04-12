#include "GJoy.hpp"
#include "globals.hpp"

void setupJ(){
  pinMode(trigButton, INPUT_PULLUP);
  pinMode(frontTrig, INPUT_PULLUP);
}

int waitForInput(){
  while(true) {
    // get positions
    int y = stick.read(X);
    int x = stick.read(Y);

    // stick.read returns analog value from 0 to 1023

    if(x > 800) {
      return LEFT;
    } else if(x < 300){
      return RIGHT;
    } else if(y > 800){
      return DOWN;
    } else if(y < 300){
      return UP;
    }

    bool button = !digitalRead(trigButton);
    bool trigger = !digitalRead(frontTrig);
    if((button || trigger) == true) {
      return 3;
    }
  }
}

bool joyBtnDown(){
  bool button = !digitalRead(trigButton);
  bool trigger = !digitalRead(frontTrig);
  return (button || trigger);
}

void waitForBtnUp(){
  bool button;
  while(true){
    button = joyBtnDown();
    if(!button){
      return;
    }
  }
}
void waitForCenter(){
  while(true){
    int y = stick.read(X);
    int x = stick.read(Y);

    // stick.read returns analog value from 0 to 1023

    if(x > 800) {
      ;
    } else if(x < 300){
      ;
    } else if(y > 800){
      ;
    } else if(y < 300){
      ;
    } else{
      break;
    }
  }
}