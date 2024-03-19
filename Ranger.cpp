#include <math.h>
#include "Ranger.hpp"
#include "globals.hpp"
#include "dht11.h"

#include <AceSorting.h>
using ace_sorting::shellSortKnuth;

// extern must be defined in file scope, not function scope

float humidity = 0.5; // in percent relative humidity
float temperature = 20.0; // celsius
float c = 0.0343; // speed of sound, in cm/us

// setup ranger
void setupR(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  dht11 DHT11;
}

// update humid and temp with current readings
//TODO: read from humid and temp sensor
//TODO: add new menu for calibration and manual adjustment of temp and humid values
void calibrate(){

  lcd.print(temperature);
  
  // update current speed of sound https://www.reddit.com/r/arduino/comments/gdysbx/temperature_and_humidity_ultrasonic_rangefinder/
  //  base c   temp coeff     humid coeff
  c = 331.4 + (0.606*temperature) + (0.0124*humidity);

}

// returns distance in cm
//WIP: Account for humid and temp
float getRange() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH); // pulseIn returns time in microseconds

  



  float distance = (duration*0.0343)/2;
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