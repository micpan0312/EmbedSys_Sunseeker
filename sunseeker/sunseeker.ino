#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"
#include "bluetooth.h"

unsigned long totsTime;
unsigned long oldTime;

void setup() {
  Serial.begin(9600);  //initialized serial port , using Bluetooth as serial port, setting baud
  setup_bluetooth();
  setup_avoid();
  // Serial.begin(9600);  //initialized serial port , using Bluetooth as serial port, setting baud
  stopp();             //stop
  setup_compass();
  delay(1000);
}
void loop() {
  // totsTime = millis();
  // oldTime = totsTime;

  // *****************************************************************************************
  // Bluetooth communication from user, input desired time window
  // *****************************************************************************************
  loop_bluetooth();
  Serial.println("\nBluetooth done");

  // *****************************************************************************************
  // Sunseeker starts moving w obstacle avoidance
  // *****************************************************************************************
  Self_Control();
  Serial.println("\ncar done");
  // Serial.println(millis());
  // Serial.println(oldTime);

  // *****************************************************************************************
  // Checking compass value
  // *****************************************************************************************
  // float dir = loop_compass();
  // Serial.println("Compass: "+ (String) dir + " degree");
  float dir_avg = 0.0;
  for (int i = 0; i < 5; i++) {
    float dir = loop_compass();
    // Serial.println("Measurement " + (String) (i+1) + ": " + (String) dir + " degree");
    dir_avg += dir;
  }
  Serial.println("Compass: " + (String) (dir_avg/5.0 )+ " degree");

  // *****************************************************************************************
  // Checking if under sunlight
  // *****************************************************************************************
  float uv = loop_uv();
  Serial.println("UV: " + (String) uv);

  Serial.println();
}
