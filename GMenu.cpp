#include "globals.hpp"
#include "GMenu.hpp"
#include "Ranger.hpp"
#include "GJoy.hpp"

// main menu, or ranging menu
void menuMain(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);

    lcd.print(memRng);
    lcd.print(" cm");

    int in = waitForInput();
    if(in == BTN){
      lcd.setCursor(15,1);
      lcd.print("*");
      memRng = avgRange(userSamples);
    } else if(in == RIGHT){
      // menuSettings();
      ;
    } else if(in == LEFT){
      // menuAlarm();
      ;
    }
    delay(UI_DELAY);
  }
}

// void menuSettings(){
//   while(true){
//     lcd.clear();
//     lcd.setCursor(15,0);
//     lcd.print("S");
//     lcd.setCursor(0,0);

//     lcd.print("smpls=");
//     lcd.print(samples);

//     int in = waitForInput();
//     if(in == LEFT){
//       menuMain();
//     } else if(in == UP){
//       if(samples < MAX_SAMPLES){
//         samples++;
//       }
//     } else if(in == DOWN){
//       if(samples > 1){
//         samples--;
//       }
//     } else if(in == RIGHT) {
//       // menuTest();
//       ;
//     }
//     delay(UI_DELAY);
//   }
// }
