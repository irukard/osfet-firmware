#include "sht3x.h"

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ SHT3x global variables                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

ClosedCube_SHT31D sht3xIn;
double valuesSht3xIn_T[SHT3X_MEDIAN_ARRAY];
unsigned int indexSht3xIn_T = 0;
double valuesSht3xIn_H[SHT3X_MEDIAN_ARRAY];
unsigned int indexSht3xIn_H = 0;

ClosedCube_SHT31D sht3xOut;
double valuesSht3xOut_T[SHT3X_MEDIAN_ARRAY];
unsigned int indexSht3xOut_T = 0;
double valuesSht3xOut_H[SHT3X_MEDIAN_ARRAY];
unsigned int indexSht3xOut_H = 0;

unsigned long lastMeasurementTimeSht3x = 0;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SHT3x in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSht3xIn(){
    sht3xIn.begin(IN_I2C_ADDR_SHT3X);
    if (sht3xIn.periodicStart(SHT3XD_REPEATABILITY_HIGH, SHT3XD_FREQUENCY_1HZ) == SHT3XD_NO_ERROR) {
        debug("[ OK ] SHT3x IN: Periodic mode started", 2);
        return true;
    } else {
        debug("[ ER ] SHT3x IN: Cannot start periodic mode", 1);
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SHT3x in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSht3xOut(){
    sht3xOut.begin(OUT_I2C_ADDR_SHT3X);
    if (sht3xOut.periodicStart(SHT3XD_REPEATABILITY_HIGH, SHT3XD_FREQUENCY_1HZ) == SHT3XD_NO_ERROR) {
        debug("[ OK ] SHT3x OUT: Periodic mode started", 2);
        return true;
    } else {
        debug("[ ER ] SHT3x OUT: Cannot start periodic mode", 1);

        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SHT3x in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSht3xIn(){
    SHT31D result = sht3xIn.periodicFetchData();
    if (result.error == SHT3XD_NO_ERROR) {
        valuesSht3xIn_T[(indexSht3xIn_T++ % SHT3X_MEDIAN_ARRAY)] = result.t;
        valuesSht3xIn_H[(indexSht3xIn_H++ % SHT3X_MEDIAN_ARRAY)] = result.rh;
        debug("[ OK ] SHT3x IN: Values T & H fetched from sensor", 2);
        return true;
    } else {
        debug("[ ER ] SHT3x IN: Cannot read values", 1);
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SHT3x in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSht3xOut(){
    SHT31D result = sht3xOut.periodicFetchData();
    if (result.error == SHT3XD_NO_ERROR) {
        valuesSht3xOut_T[(indexSht3xOut_T++ % SHT3X_MEDIAN_ARRAY)] = result.t;
        valuesSht3xOut_H[(indexSht3xOut_H++ % SHT3X_MEDIAN_ARRAY)] = result.rh;
        debug("[ OK ] SHT3x OUT: Values T & H fetched from sensor", 2);
        return true;
    } else {
        debug("[ ER ] SHT3x OUT: Cannot read values", 1);
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Schedule SHT3x Reads                             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void scheduleReadSht3x() {

    if (millis() - lastMeasurementTimeSht3x < SHT3X_READ_INTERVAL) {
        return;
    }
    
    for (int i=0; i < SHT3X_READ_RETRY; i++) {
        if (readSht3xIn()) {
            break;
        }
    }
    for (int i=0; i < SHT3X_READ_RETRY; i++) {
        if (readSht3xOut()) {
            break;
        }
    }

    lastMeasurementTimeSht3x = millis();
}
