#ifndef OSFET_UTILS_H
#define OSFET_UTILS_H

#include <Arduino.h>
#include "sensors/sht3x.h"

extern unsigned long lastWriteTimeCSV;
extern bool displayHeadersCSV;

double medianFromArray(double values[], int size);
void writeCSV();
void scheduleWriteCSV();

#endif // OSFET_UTILS_H