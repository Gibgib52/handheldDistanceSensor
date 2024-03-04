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

  Serial.println(duration);
  return distance;
}