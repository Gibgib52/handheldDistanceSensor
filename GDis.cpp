// for display effects

#include "GDis.hpp"
#include "globals.hpp"

// flashes text on lcd
// default 2 flashes, 100 ms interval
// preserves screen content(excluding what txt overwrites), doesnt lcd.clear()
void flashTxt(char* txt, int flashes = 2, int interval = 200, int x = 0, int y = 0){
  int len = strlen(txt);
  for(int i = 0; i < flashes; i++){
    // -- on
    lcd.setCursor(x,y);
    lcd.print(txt);
    delay(interval);

    // -- off
    lcd.setCursor(x,y);
    // print blanks len times
    for(int j = 0; j < len; j++){
      lcd.print(" ");
    }
    delay(interval);
  }
}


// special chars

namespace spec{
  char a  = 0b10110001;
  char i  = 0b10110010;
  char u  = 0b10110011;
  char e  = 0b10110100;
  char o  = 0b10110101;

  char xa  = 0b10100111;
  char xi  = 0b10101000;
  char xu  = 0b10101001;
  char xe  = 0b10101010;
  char xo  = 0b10101011;

  char ka = 0b10110110;
  char ki = 0b10110111;
  char ku = 0b10111000;
  char ke = 0b10111001;
  char ko = 0b10111010;

  char sa = 0b10111011;
  char si = 0b10111100;
  char su = 0b10111101;
  char se = 0b10111110;
  char so = 0b10111111;

  char ta = 0b11000000;
  char ti = 0b11000001;
  char tu = 0b11000010;
  char te = 0b11000011;
  char to = 0b11000100;

  char xtu = 0b10101111;

  char na = 0b11000101;
  char ni = 0b11000110;
  char nu = 0b11000111;
  char ne = 0b11001000;
  char no = 0b11001001;

  char ha = 0b11001010;
  char hi = 0b11001011;
  char hu = 0b11001100;
  char he = 0b11001101;
  char ho = 0b11001110;

  char ma = 0b11001111;
  char mi = 0b11010000;
  char mu = 0b11010001;
  char me = 0b11010010;
  char mo = 0b11010011;

  char ya = 0b11010100;
  char yu = 0b11010101;
  char yo = 0b11010110;

  char xya = 0b10111100;
  char xyu = 0b10111101;
  char xyo = 0b10111110;

  char ra = 0b11010111;
  char ri = 0b11011000;
  char ru = 0b11011001;
  char re = 0b11011010;
  char ro = 0b11011011;

  char wo = 0b10100110;
  char wa = 0b11011100;
  char n  = 0b11011101;

  // dakuten and handakuten
  char ten = 0b11011110;
  char han = 0b11011111;
}
