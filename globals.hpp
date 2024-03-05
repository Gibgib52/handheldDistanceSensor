#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AlignedJoy.h>

// #pragma once

// for ranger
#define trigPin 2 // orange
#define echoPin 3 // blue

// for stick
#define trigButton 5
#define joyXpin 0
#define joyYpin 1

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define BTN 3

#define BAUD_RATE 9600
#define MAX_SAMPLES 100
#define UI_DELAY 100


extern LiquidCrystal lcd;
extern AlignedJoy stick;

extern int userSamples;
extern float memRng;

