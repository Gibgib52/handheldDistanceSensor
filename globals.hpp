#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>


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

// no changing below

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define BTN 3

extern LiquidCrystal lcd;
extern AlignedJoy stick;

extern int userSamples;
extern float memRng;

extern bool debug;

