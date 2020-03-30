#ifndef OSFET_BMP388_H
#define OSFET_BMP388_H

#include <Arduino.h>
#include "config.h"
#include "utils.h"

extern double valuesBmp388In_T[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388In_T;
extern double valuesBmp388In_P[BMP388_MEDIAN_ARRAY];
extern unsigned int indexBmp388In_P;

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