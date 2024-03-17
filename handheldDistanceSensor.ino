// https://www.gammon.com.au/forum/?id=12625
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <ArxContainer.h>
#include <string.h>

#include "globals.hpp"


// one-time globals

extern AlignedJoy stick(joyXpin, joyYpin);


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int userSamples;
float memRng;
bool debug = false;
int mode;
extern std::map<String, int, 64> kana;

bool light;

extern float humidity;
extern float temp;
extern float c;
