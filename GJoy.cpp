#include "GJoy.hpp"
#include "globals.hpp"

int waitForInput(){
  while(true) {
    // get positions
    int y = stick.read(X);
    int x = stick.read(Y);

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