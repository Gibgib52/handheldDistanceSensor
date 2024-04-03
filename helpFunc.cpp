#include "GJoy.hpp"
#include "globals.hpp"
#include "GDis.hpp"

void h_ranging(){
  String txt = "some text to type out on the lcd, very long so i can test the word wrap on typeText";
  typeText(txt);
  waitForInput();
}

void h_alarm(){
  lcd.print("alarm help");
  waitForInput();
}

void printHelp(int id){
  switch(id){
    case 0:
      h_ranging();
      break;
    case 1:
      h_alarm();
      break;
    default:
      break;
  }
}

String getTitle(int id){
  switch(id){
    case 0:
      return "ranging";
      break;
    case 1:
      return "alarm";
      break;
    default:
      return "err";
      break;
  }
}