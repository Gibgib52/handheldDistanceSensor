#include "GJoy.hpp"
#include "globals.hpp"

void setupJ(){
  pinMode(trigButton, INPUT_PULLUP);
}

int waitForInput(){
  while(true) {
    // get positions
    int y = stick.read(X);
    int x = stick.read(Y);

    // stick.read returns analog value from 0 to 1023

    if(x > 800) {
      return RIGHT;
    } else if(x < 300){
      return LEFT;
    } else if(y > 800){
      return UP;
    } else if(y < 300){
      return DOWN;
    }

    bool button = !digitalRead(trigButton);
    if(button == true) {
      return 3;
    }
  }
}

bool joyBtnDown(){
  bool button = !digitalRead(trigButton);
  return button;
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