#ifndef OSFET_SHT3X_H
#define OSFET_SHT3X_H

#include <Arduino.h>
#include "ClosedCube_SHT31D.h"
#include "config.h"

extern ClosedCube_SHT31D sht3xIn;
extern double lastValueSht3xIn_T;
extern double lastValueSht3xIn_H;
extern ClosedCube_SHT31D sht3xOut;
extern double lastValueSht3xOut_T;
extern double lastValueSht3xOut_H;

bool initSht3xIn();
bool initSht3xOut();
bool readSht3xIn();
bool readSht3xOut();

#endif // OSFET_SHT3X_H