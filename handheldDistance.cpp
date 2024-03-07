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

  // String temp = "fu bu ki nn gu";
  // String temp = "a i u e o";
  // writeKana(temp);

  std::map<String, int> testMap = {
    {"a", 0b10110001},
    {"i", 0b10110010}
  };

  Serial.println(testMap["a"]);
  lcd.write(testMap["a"]);
  Serial.println(testMap["i"]);
  lcd.write(testMap["i"]);

  Serial.print(kana["a"]);
  lcd.write(kana["a"]);

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

