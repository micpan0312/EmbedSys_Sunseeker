#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"
#define Pin12  12
#define Pin13  13
unsigned long totsTime;
unsigned long oldTime;
int Value;
int distance = 2;
bool stopNow = false;
int myPrediction[4];
bool predict = false;
bool alreadyPredicted = false;
int newSpot = 0;
int tot = 0;

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
  //if(stopNow == true){
  //  Value = 0;
  //}
  if(Value){
  // *****************************************************************************************
  // Bluetooth communication result from user, input desired time window
  // *****************************************************************************************

    digitalWrite(Pin13, HIGH );
    
  // *****************************************************************************************
  // inital search for windows
  // *****************************************************************************************
  
  // totsTime = millis();
  // oldTime = totsTime;

  // *****************************************************************************************
  // Sunseeker starts moving w obstacle avoidance
  // *****************************************************************************************
  
//    Self_Control();
//    Serial.println("\ncar done");
  // Serial.println(millis());
  // Serial.println(oldTime);

  // *****************************************************************************************
  // Checking compass value
  // *****************************************************************************************
  // float dir = loop_compass();
  // Serial.println("Compass: "+ (String) dir + " degree");
    loop_compass();
    Serial.println("Compass: " + (String) (dir_avg/5.0 )+ " degree");

  // *****************************************************************************************
  // Checking if under sunlight
  // *****************************************************************************************
    
    float uv = loop_uv();
    Serial.println("UV: " + (String) uv);
    if(uv > 0.20){
        stopp();
        //stopNow = true;
        newSpot++;
    }
    Serial.println();
  }
    if(predict){
      // stopp();
      delay(1000);
      Serial.println("started");
      for(int times = 0; times < 75; times++){
        advance();
      }
      delay(1000);
      for(int times = 0; times < 75; times++){
        back();
      }
      if(alreadyPredicted){
        myPrediction[newSpot] = uv;
        for(int times = 0; times < newSpot+1; times++){
            tot = tot + myPrediction[times];
        }
      }
      else{
        myPrediction[newSpot] = uv;
      }
    }
  else{
    digitalWrite(Pin13, LOW );
    self_Control(Value);
    //Serial.println("time");
  }
}
