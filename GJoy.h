// #include <AlignedJoy.h>

#define trigButton 5

// wait for a direction from joystick
int waitForInput() {
  while(true) {
    // get positions
    int y = stick.read(X);
    int x = stick.read(Y);

    if(x > 800) {// right
      return 2;
    } else if(x < 300){// left
      return -2;
    } else if(y > 800){// up
      return 1;
    } else if(y < 300){// down
      return -1;
    }

    bool button = !digitalRead(trigButton);
    if(button == true) {
      return 3;
    }

  }
}

// non-blocking, instantaneous check for btn down
bool joyBtnDown(){
  bool button = !digitalRead(trigButton);
  return button;
}
