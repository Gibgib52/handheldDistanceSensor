#include "globals.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"
#include "Gmenu.hpp"

// sketch here
int main(){
  // do not remove
  init();
  Serial.begin(BAUD_RATE);
  Serial.println("serial started");


  // sketch begin ////////////////////////////////////////////

  setupM();
  lcd.begin(16,2);
  lcd.print("Trigger to cont.");

  lcd.setCursor(0,1);
  // test ranger
  setupR();
  float tmpRng = getRange();
  lcd.print(tmpRng);


  setupJ();
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

