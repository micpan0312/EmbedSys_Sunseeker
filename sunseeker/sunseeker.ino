#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"

unsigned long totsTime;
unsigned long oldTime;

void setup() {
  setup_avoid();
  Serial.begin(9600);  //initialized serial port , using Bluetooth as serial port, setting baud
  stopp();             //stop
  setup_compass();
  delay(1000);
}
void loop() {
  // loop_compass();
  // totsTime = millis();
  // oldTime = totsTime;
  // Self_Control();
  Serial.println("\ncar done");
  // Serial.println(millis());
  // Serial.println(oldTime);
  int dir = loop_compass();
  Serial.println("Compass: "+ (String) dir + " degree");
  float uv = loop_uv();
  Serial.println("UV: " + (String) uv);
}
