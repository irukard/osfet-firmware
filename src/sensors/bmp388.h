#ifndef OSFET_BMP388_H
#define OSFET_BMP388_H

#include <Arduino.h>
#include "config.h"
#include "utils.h"

#include "DFRobot_BMP388_I2C.h"
#include "DFRobot_BMP388.h"
#include "Wire.h"
#include "SPI.h"
#include "bmp3_defs.h"

extern DFRobot_BMP388_I2C bmp388In;
extern double valuesBmp388In_T[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388In_T;
extern double valuesBmp388In_P[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388In_P;

extern DFRobot_BMP388_I2C bmp388Out;
extern double valuesBmp388Out_T[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388Out_T;
extern double valuesBmp388Out_P[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388Out_P;

extern unsigned long lastMeasurementTimeBmp388;

bool initBmp388In();
bool initBmp388Out();
bool readBmp388In();
bool readBmp388Out();
void scheduleReadBmp388();

#endif // OSFET_BMP388_H