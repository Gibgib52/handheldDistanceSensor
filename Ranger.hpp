#include <Arduino.h>
#include "globals.hpp"


void setupR();
float getRange();
float avgRange(int, bool debug = false);
float medianRange(int, bool debug = false);