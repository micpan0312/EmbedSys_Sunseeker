#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"
#define Pin12  12
#define Pin13  13
unsigned long totsTime;
unsigned long oldTime;
int Value;
float theta1, theta2, OriginAngle;
int L1, L2, H1, H2, test_travel;
float predictionDegrees[] = {0, 0, 0, 0, 0, 0};
//height of the robot is 33 cm 

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
    for (int i = 0; i < 1; i++) {
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
    if(uv > 0.00){
        stopp();
    }
    
//    theta1 = 0;
//    theta2 = 0;
//    L2 = sqrt(sq(L1) + sq(H2) - 2*L1*H1*cos((180.0 - theta1 - theta2)*(PI/180.0)));
//    test_travel = distance * (1/3)
  }
  else{
    digitalWrite(Pin13, LOW );
    self_Control(Value);
  }
}
