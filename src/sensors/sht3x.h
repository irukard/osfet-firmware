#ifndef OSFET_SHT3X_H
#define OSFET_SHT3X_H

#include <Arduino.h>
#include "ClosedCube_SHT31D.h"
#include "config.h"
#include "utils.h"

//extern ClosedCube_SHT31D sht3xIn;
extern double valuesSht3xIn_T[SHT3X_MEDIAN_ARRAY];
//extern unsigned int indexSht3xIn_T;
extern double valuesSht3xIn_H[SHT3X_MEDIAN_ARRAY];
//extern unsigned int indexSht3xIn_H;

//extern ClosedCube_SHT31D sht3xOut;
extern double valuesSht3xOut_T[SHT3X_MEDIAN_ARRAY];
//extern unsigned int indexSht3xOut_T;
extern double valuesSht3xOut_H[SHT3X_MEDIAN_ARRAY];
//extern unsigned int indexSht3xOut_H;

//extern unsigned long lastMeasurementTimeSht3x;

bool initSht3xIn();
bool initSht3xOut();
bool readSht3xIn();
bool readSht3xOut();
void scheduleReadSht3x();

#endif // OSFET_SHT3X_H