#include "sht3x.h"

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ SHT3x global variables                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

ClosedCube_SHT31D sht3xIn;
double lastValueSht3xIn_T;
double lastValueSht3xIn_H;
ClosedCube_SHT31D sht3xOut;
double lastValueSht3xOut_T;
double lastValueSht3xOut_H;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SHT3x in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSht3xIn(){
    sht3xIn.begin(IN_I2C_ADDR_SHT3X);
    if (sht3xIn.periodicStart(SHT3XD_REPEATABILITY_HIGH, SHT3XD_FREQUENCY_1HZ) == SHT3XD_NO_ERROR) {
        Serial.println("[ OK ] SHT3x IN: Periodic mode started");
        return true;
    } else {
        Serial.println("[ ER ] SHT3x IN: Cannot start periodic mode");
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SHT3x in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSht3xOut(){
    sht3xOut.begin(OUT_I2C_ADDR_SHT3X);
    if (sht3xOut.periodicStart(SHT3XD_REPEATABILITY_HIGH, SHT3XD_FREQUENCY_1HZ) == SHT3XD_NO_ERROR) {
        Serial.println("[ OK ] SHT3x OUT: Periodic mode started");
        return true;
    } else {
        Serial.println("[ ER ] SHT3x OUT: Cannot start periodic mode");
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SHT3x in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSht3xIn(){
    SHT31D result = sht3xIn.periodicFetchData();
    if (result.error == SHT3XD_NO_ERROR) {
        lastValueSht3xIn_T = result.t;
        lastValueSht3xIn_H = result.rh;
        return true;
    } else {
        Serial.println("[ ER ] SHT3x IN: Cannot read values");
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SHT3x in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSht3xOut(){
    SHT31D result = sht3xOut.periodicFetchData();
    if (result.error == SHT3XD_NO_ERROR) {
        lastValueSht3xOut_T = result.t;
        lastValueSht3xOut_H = result.rh;
        return true;
    } else {
        Serial.println("[ ER ] SHT3x OUT: Cannot read values");
        return false;
    }
}
