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
#define trigPin 52 // orange
#define echoPin 50 // blue
// for stick
#define trigButton 2
// remember these are analog pins
#define joyXpin 13
#define joyYpin 14

#define LIGHT_PIN 23


// lcd pins
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;

#define BUZZ_PIN 39



// no changing below

#define MAX_RANGE 400
#define MIN_RANGE 3

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
extern bool buzzFlag;

extern bool debug;

extern std::map<String, int, 64> kana;

extern float humidity;
extern float temperature;
extern float c;