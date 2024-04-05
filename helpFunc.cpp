#include "GJoy.hpp"
#include "globals.hpp"
#include "GDis.hpp"

void h_ranging(){
  String txt = "the ultrasonic  "
  "ranger has a max"
  "range of 400 cm "
  "and a min of 2cm"
  ". for good dists"
  "measure against "
  "an object with  "
  "1m^2 surf. area."
  "and within 30deg"
  "angle of surface"
  "careful of multi"
  "path or uninten "
  "ded echoes      ";



  typeText(txt);
  waitForInput();
}

void h_alarm(){
  String txt = "pDist is the set"
  "distance to test"
  "for, if dist is "
  "below pDist an  "
  "alert will      "
  "display on lcd  ";

  typeText(txt);
  waitForInput();
}

void printHelp(int id){
  waitForBtnUp();
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