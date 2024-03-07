// for display effects

#include "GDis.hpp"
#include "globals.hpp"
#include <string.h>
// #include <Vector.h>
#include <ArxContainer.h>

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

// write katakana out to the lcd
// txt must be romaji seperated by spaces
void writeKana(char txt[]){
  String str = "fu bu ki n gu";


  // https://sentry.io/answers/split-string-in-cpp/
  std::vector<String> total;
  int i = 0;
  while(i < str.length()){
    i = str.indexOf(" ");// delim
    total.push_back(str.substring(0, i));
    str.remove(0, i+1); // i + length of delim
  }

  // print the vector
  for(int i = 0; i < total.size(); i++){
    String cur = total[i];
    Serial.println(cur);
  }


  // match the tokens to a map

  // write the converted text to lcd

}


std::map<String, char> kana {
  {"a", 0b10110001},
  {"i", 0b10110010},
  {"u", 0b10110011},
  {"e", 0b10110100},
  {"o", 0b10110101},
 
  {"xa", 0b10100111},
  {"xi", 0b10101000},
  {"xu", 0b10101001},
  {"xe", 0b10101010},
  {"xo", 0b10101011},
 
  {"ka", 0b10110110},
  {"ki", 0b10110111},
  {"ku", 0b10111000},
  {"ke", 0b10111001},
  {"ko", 0b10111010},
 
  {"sa", 0b10111011},
  {"si", 0b10111100},
  {"su", 0b10111101},
  {"se", 0b10111110},
  {"so", 0b10111111},
 
  {"ta", 0b11000000},
  {"ti", 0b11000001},
  {"tu", 0b11000010},
  {"te", 0b11000011},
  {"to", 0b11000100},
 
  {"xtu", 0b10101111},
 
  {"na", 0b11000101},
  {"ni", 0b11000110},
  {"nu", 0b11000111},
  {"ne", 0b11001000},
  {"no", 0b11001001},
 
  {"ha", 0b11001010},
  {"hi", 0b11001011},
  {"hu", 0b11001100},
  {"he", 0b11001101},
  {"ho", 0b11001110},
 
  {"ma", 0b11001111},
  {"mi", 0b11010000},
  {"mu", 0b11010001},
  {"me", 0b11010010},
  {"mo", 0b11010011},
 
  {"ya", 0b11010100},
  {"yu", 0b11010101},
  {"yo", 0b11010110},
 
  {"xya", 0b10111100},
  {"xyu", 0b10111101},
  {"xyo", 0b10111110},

  {"ra", 0b11010111},
  {"ri", 0b11011000},
  {"ru", 0b11011001},
  {"re", 0b11011010},
  {"ro", 0b11011011},

  {"wo", 0b10100110},
  {"wa", 0b11011100},
  {"nn", 0b11011101},

  // dakuten and handakuten
  {"ten", 0b11011110},
  {"han", 0b11011111}
};

