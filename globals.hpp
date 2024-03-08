#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <ArxContainer.h>

// settings
#define BAUD_RATE 9600
#define MAX_SAMPLES 100
#define UI_DELAY 100 // delay for menu loops
#define UI_SWITCH_DELAY 500 // delay between switching menus

// pin locations
// for ranger
#define trigPin 2 // orange
#define echoPin 3 // blue
// for stick
#define trigButton 5
#define joyXpin 0
#define joyYpin 1

#define LIGHT_PIN 31

// lcd pins
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;

// no changing below

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define BTN 3

// modes
#define AVG 1
#define MED 2

extern int mode;

extern LiquidCrystal lcd;
extern AlignedJoy stick;

extern int userSamples;
extern float memRng;

extern bool light;

extern bool debug;

extern std::map<String, int, 64> kana;