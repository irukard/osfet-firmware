#ifndef OSFET_SPS30_H
#define OSFET_SPS30_H

#include <Arduino.h>
#include "config.h"
#include "utils.h"

#include <SoftwareSerial.h>

extern unsigned long lastMeasurementTimeSps30;

bool initSps30In();
bool initSps30Out();
bool readSps30In();
bool readSps30Out();
void scheduleReadSps30();

#endif // OSFET_SPS30_H