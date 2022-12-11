#include <Servo.h>
#include "avoid.h"
#include "compass.h"
#include "uv.h"
#include "math.h"
#define Pin12 12
#define Pin13 13
#define PI 3.1415926535897932384626433832795
#define camHeight 0.33

String command;
unsigned long totsTime;
unsigned long oldTime;
int Value;
int distance = 2;
bool stopNow = false;
float myPrediction[4];
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
  stopp();  //stop
  setup_compass();
  delay(1000);
}

void loop() {
  // read if the bot should be ON or OFF
  Value = digitalRead(Pin12);

  if (Value) {
    // *******************************************************************
    // Bluetooth communication result from user, input desired time window
    // *******************************************************************
    digitalWrite(Pin13, HIGH);

    // *****************************************************************
    // inital search for windows, sending window request to Pi in serial
    // *****************************************************************
    Serial.println("winreq");

    // if got distance from Pi
    if (Serial.available()) {
      // store current bot angel
      float theta1 = loop_compass();
      float theta3 = 30 * PI / 180;          // sun altitude angle in the sky
      float theta4 = (170 - 90) * PI / 180;  // sun direction
      float theta5 = PI - theta1 - theta4;

      // read Serial write from Pi
      command = Serial.readStringUntil('\n');
      command.trim();

      if (command.substring(0, 6).equals("window")) {
        float d1 = command.substring(7, 11).toFloat();  // distance from bot to window
        float d3 = command.substring(23).toFloat();     // absolute distance from bot to window
        Serial.println("Arduino: Distance: " + (String)d1 + " Abs distance: " + (String)d3);

        float theta2 = acos(d3 / d1);
        float d5 = d1 * sin(theta2) + camHeight;
        float d6 = d5 / tan(theta3);
        float d7 = sqrt(sq(d3) + sq(d6) - 2 * d3 * d6 * cos(theta5));  // the dist to the sunlight

        // ***********************
        // Checking compass value
        // ***********************
        // rotate bot to the desired angle (relative to curr bot)
        float cur_angle = loop_compass();
        while ((int)(theta5 / PI * 180) != (int) cur_angle) {
          rotate();
          cur_angle = loop_compass();
        }
        
        // go straight to predicted sunlight spot
        int times_needed = (int) d7 * 75 / 0.5;
        for (int times = 0; times < times_needed; times++) {
          advance();
        }
        // ****************************
        // Checking if under sunlight
        // ****************************
        float uv = loop_uv();
        if (uv > 0.20) {
          stopp();
          newSpot++;
        }
      } else {
        Serial.println("Arduino: Invalid serial");
      }
    } else {
      // **********************************************
      // Sunseeker starts moving w obstacle avoidance
      // **********************************************
      // if not catch any serial port input, cruise around the bot
      Self_Control();
    }

    // ***************************
    // Checking if under sunlight
    // ***************************
    float uv = loop_uv();
    Serial.println("UV: " + (String)uv);
    if (uv > 0.20) {
      stopp();
      //stopNow = true;
      newSpot++;
    }

    if (predict) {
      // stopp();
      delay(1000);
      Serial.println("started");
      for (int times = 0; times < 75; times++) {
        advance();
      }
      delay(1000);
      for (int times = 0; times < 75; times++) {
        back();
      }
      if (alreadyPredicted) {
        myPrediction[newSpot] = uv;
        for (int times = 0; times < newSpot + 1; times++) {
          tot = tot + myPrediction[times];
        }
      } else {
        myPrediction[newSpot] = uv;
      }
    } else {
      digitalWrite(Pin13, LOW);
      self_Control(Value);
    }
  }
}
