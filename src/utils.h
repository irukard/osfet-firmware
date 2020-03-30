#ifndef OSFET_UTILS_H
#define OSFET_UTILS_H

#include <Arduino.h>
#include "sensors/sht3x.h"
#include "sensors/bmp388.h"
#include "sensors/sps30.h"

extern unsigned long lastWriteTimeCSV;
extern bool displayHeadersCSV;

double medianFromArray(double values[], int size);
void writeCSV();
void scheduleWriteCSV();
String currentTimeStamp();
void debug(const String& message, const int level);

#endif // OSFET_UTILS_H