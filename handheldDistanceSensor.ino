#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <AceSorting.h>
using ace_sorting::shellSortKnuth;
// shellSortKnuth()

#define trigPin 2 // orange
#define echoPin 3 // blue
#define endl "\n"

#define trigButton 5

#define joyXpin 0
#define joyYpin 1

#define endl "\n"

// why is lcd not global? why cant Menu.c or Ranger.h see it??????????
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy stick(joyXpin, joyYpin);


// TODO: add temp/humididy sensor and correction for temp/humid

const int UP = 1;
const int DOWN = -1;
const int LEFT = -2;
const int RIGHT = 2;
const int BTN = 3;

// menu consts
const int MAIN = 10;
const int SETTINGS = 11;


const int MAX_SAMPLES = 100;
int samples = 1;

const int UI_DELAY = 100; // ms delay for ui loops

// returns distance in cm
float getRange() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration*.0343)/2;
  return distance;
}

float avgRange(int samples, bool debug = false) {
  // get avg of samples
  float dists[samples];
  for(int i = 0; i < samples; i++){
    if(debug){
      lcd.setCursor(14,1);
      lcd.print(i+1);
    }
    dists[i] = getRange();
    delay(50);
  }
  
  float total = 0;
  for(int i = 0; i < samples; i++) {
    total += dists[i];
  }

  float distance = total/samples;
  return distance;
}

float medianRange(int samples, bool debug = false){
  // gather samples
  float dists[samples];
  for(int i = 0; i < samples; i++){
    if(debug){
      lcd.setCursor(14,1);
      lcd.print(i+1);
    }
    dists[i] = getRange();
    delay(50);
  }

  // get median
  int len = sizeof(dists);
  shellSortKnuth(dists, len);

  // if len is odd return middle, if len is even return avg of middle values
  if(!len % 2){
    return dists[len/2];
  } else{
    int hi = ceil(len/2);
    int lo = floor(len/2);

    return (hi + lo)/2;
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.print("starting...");

  // start serial
  lcd.setCursor(0, 1);
  lcd.print("s");
  Serial.begin(9600);
  // while(!Serial){} // do nothing while serial is starting
  // Serial.println("serial started");
  lcd.print("S");

  // start ranger
  lcd.print("r");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  float tmpRng = getRange();
  lcd.print(tmpRng);
  lcd.print("R");

  // button
  pinMode(trigButton, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("done! press btn");


  // testing
  // lcd.clear();
  // lcd.write();

  while(true){
    if(waitForInput() == BTN){
      menuMain();
    }
  }
}

float dsplyRng;

int menu = MAIN;
int update = 0; // counts up on failure, shows display still working
void loop() {
  // int in = waitForInput();
  // if(in == BTN) {
  //   dsplyRng = avgRange(1);
  //   lcd.clear();
  //   lcd.print(dsplyRng);
  // }

  update++;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("in loop() ");
  lcd.print(update);
  lcd.setCursor(0,1);
  lcd.print("something went wrong.");

  delay(100);
}

// mainmenu / ranging menu
void menuMain(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("R");
    lcd.setCursor(0,0);

    lcd.print(dsplyRng);
    lcd.print(" cm");

    int in = waitForInput();
    if(in == BTN){
      lcd.setCursor(15,1);
      lcd.print("*");
      dsplyRng = avgRange(samples);
    } else if(in == RIGHT){
      menuSettings();
    } else if(in == LEFT){
      menuAlarm();
    }
    delay(UI_DELAY);
  }
}

void menuSettings(){
  while(true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("S");
    lcd.setCursor(0,0);

    lcd.print("smpls=");
    lcd.print(samples);

    int in = waitForInput();
    if(in == LEFT){
      menuMain();
    } else if(in == UP){
      if(samples < MAX_SAMPLES){
        samples++;
      }
    } else if(in == DOWN){
      if(samples > 1){
        samples--;
      }
    } else if(in == RIGHT) {
      menuTest();
    }
    delay(UI_DELAY);
  }
}


// trying to write other chars from the charmap
void menuTest(){
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("T");
    lcd.setCursor(0,0);

    int in = waitForInput();
    if(in == LEFT){
      menuSettings();
    } else{
      // en is at 1100 1111 on the charmap, reverse it to 1111 1110
      char en = 0b1111110;
      lcd.write(en);
    }
    delay(UI_DELAY);
  }
}


// makes periodic measurements, if they fall
// below prescribedDist alert the user
const int changeDelay = 100; // delay of changing prescribedDist
int prescribedDist = 10;
void menuAlarm(){
  lcd.clear();
  lcd.setCursor(15,0);
  lcd.print("A");
  lcd.setCursor(0,0);

  lcd.print("pDist=");
  lcd.print(prescribedDist);


  int in = waitForInput();
    if(in == BTN){
      alarmLoop();
    } else if(in == RIGHT){
      menuMain();
    } else if(in == LEFT){
      ;
    } else if(in == UP){
      prescribedDist++;
      delay(changeDelay);
    } else if(in == DOWN){
      prescribedDist--;
      delay(changeDelay);
    }
    delay(UI_DELAY);
}


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

// TODO: finish
void alarmLoop(){
  float pDistFloat = (float)prescribedDist;
  while(true) {
    lcd.clear();
    // header
    lcd.setCursor(15,0);
    lcd.print("A");
    lcd.setCursor(15,1);
    lcd.print("*");
    lcd.setCursor(0,0);

    float dist = avgRange(samples);
    lcd.print("dist=");
    lcd.print(dist);
    if(dist < pDistFloat){
      flashTxt("* ALARM *", 2, 100, 0, 1);
    }
    if(joyBtnDown()){
      break;
    }
  }
}

// wait for a direction from joystick
int waitForInput() {
  while(true) {
    // get positions
    int y = stick.read(X);
    int x = stick.read(Y);

    if(x > 800) {// right
      return 2;
    } else if(x < 300){// left
      return -2;
    } else if(y > 800){// up
      return 1;
    } else if(y < 300){// down
      return -1;
    }

    bool button = !digitalRead(trigButton);
    if(button == true) {
      return 3;
    }

  }
}

// non-blocking, instantaneous check for btn down
bool joyBtnDown(){
  bool button = !digitalRead(trigButton);
  return button;
}




