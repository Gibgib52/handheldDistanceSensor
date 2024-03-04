#include "Ranger.hpp"

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