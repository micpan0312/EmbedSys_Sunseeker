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
  // *****************************************************************************************
  // tx rx from master arduino (BT), check if arduno with BT send ON signal
  // *****************************************************************************************
  Value = digitalRead(Pin12);

  // if True, bot starts
  if(Value){
    // light on Pin13, indicating the bots working
    digitalWrite(Pin13, HIGH);
    // totsTime = millis();
    // oldTime = totsTime;

    // *****************************************************************************************
    // receiving Serial data from Pi
    // *****************************************************************************************
    // if (Serial.available()) {
    //   command = Serial.readStringUntil('\n');
    //   command.trim(); 

    //   if (command.equals("over 40")) {
    //     digitalWrite(Pin13, HIGH);  
    //   } else { 
    //     digitalWrite(Pin13, LOW);   
    //   }
    // }
  

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
    float angle_avg = loop_compass();
    // Serial.println("Compass: " + (String) (angle_avg/5.0 )+ " degree");
    Serial.println(angle_avg);



    // *****************************************************************************************
    // Checking if under sunlight
    // *****************************************************************************************
    float uv = loop_uv();
    Serial.println("UV: " + (String) uv);

    Serial.println();
  }
  else{
      digitalWrite(Pin13, LOW);
  }
}
