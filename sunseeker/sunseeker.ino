#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"
#define Pin12  12
#define Pin13  13
unsigned long totsTime;
unsigned long oldTime;
int Value;

void setup() {
  Serial.begin(9600);  //initialized serial port , using Bluetooth as serial port, setting baud
  pinMode(Pin12, INPUT);
  pinMode(Pin13, OUTPUT);
  setup_avoid();
  // Serial.begin(9600);  //initialized serial port , using Bluetooth as serial port, setting baud
  stopp();             //stop
  setup_compass();
  delay(1000);
}
void loop() {
  Value = digitalRead( Pin12 );
  if(Value){
    digitalWrite(Pin13, HIGH );
  // totsTime = millis();
  // oldTime = totsTime;

  // *****************************************************************************************
  // Bluetooth communication from user, input desired time window
  // *****************************************************************************************

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
  else{
      digitalWrite(Pin13, LOW );
  }
}
