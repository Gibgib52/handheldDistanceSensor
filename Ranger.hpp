#include <Arduino.h>

const int trigPin = 2; // orange
const int echoPin = 3; // blue

float getRange();
float avgRange(int, bool);
float medianRange(int, bool);