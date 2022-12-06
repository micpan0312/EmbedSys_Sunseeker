#ifndef COMPANSS_H
#define COMPANSS_H
#include <Wire.h>
#include <HMC5883L.h>

void setup_compass();
float get_compass() {
float loop_compass();
void compass_read_XYZdata();
void compass_offset_calibration(int select);
void compass_init(int gain);
void compass_scalled_reading();
void compass_heading();

#endif
