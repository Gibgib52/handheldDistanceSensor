// https://www.gammon.com.au/forum/?id=12625
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>

#include "globals.hpp"


// one-time globals

extern AlignedJoy stick(joyXpin, joyYpin);
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int userSamples;
float memRng;
bool debug = false;