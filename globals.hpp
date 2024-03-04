#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>

extern LiquidCrystal lcd;
extern AlignedJoy stick;

// for ranger
#define trigPin 2 // orange
#define echoPin 3 // blue

// for stick
#define trigButton 5
#define joyXpin 0
#define joyYpin 1