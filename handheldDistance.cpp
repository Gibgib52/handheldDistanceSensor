#include <ArxContainer.h>
#include "globals.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"
#include "Gmenu.hpp"
#include "GDis.hpp"
#include <string.h>

// sketch here
int main(){
  // do not remove
  init();
  Serial.begin(BAUD_RATE);
  while(Serial == NULL){};
  Serial.println("serial started");


  // sketch begin ////////////////////////////////////////////

  setupM();
  lcd.begin(16,2);
  setupJ();
  setupR();

  String temp = "fu fu ten ki nn ku ten";
  // String temp = "a i u e o o o";
  writeKana(temp);

  // wait for btn to continue
  while(true){
    if(waitForInput() == BTN){
      menuMain();
    }
  }
  

  // sketch end /////////////////////////////////

  // do not remove
  Serial.flush();
  return 0;
}

