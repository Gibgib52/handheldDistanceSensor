#include "globals.hpp"
#include "Ranger.hpp"
// #include "GJoy.hpp"
// #include "Gmenu.hpp"

// sketch here
int main(){
  // do not remove
  init();
  Serial.begin(BAUD_RATE);
  Serial.println("serial started");


  // sketch begin ////////////////////////////////////////////

  const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  AlignedJoy stick(joyXpin, joyYpin);

  lcd.begin(16,2);
  lcd.print("Trigger to cont.");

  lcd.setCursor(0,1);
  // test ranger
  setupR();
  float tmpRng = getRange();
  lcd.print(tmpRng);

  // wait for btn to continue
  while(true){
    if(waitForInput() == BTN){
      // menuMain();
      ;
    }
  }
  // TODO: Rewrite all previous stuff to seperate files
  

  // sketch end /////////////////////////////////

  // do not remove
  Serial.flush();
  return 0;
}

