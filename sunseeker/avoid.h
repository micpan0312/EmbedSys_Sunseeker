#ifndef AVOID_H
#define AVOID_H
#include <Arduino.h>
#include <Servo.h>

void setup_avoid();
void M_Control_IO_config(void);
void Set_Speed(unsigned char Left, unsigned char Right);
void advance();
void turnR();
void turnL();
void stopp();
void back();
void Self_Control(void);
void self_Control(int Value);
int Ultrasonic_Ranging(unsigned char Mode);
int ask_pin_L(unsigned char Mode);
int ask_pin_R(unsigned char Mode);

#endif
