#include "bmp388.h"

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ BMP388 global variables                          ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

DFRobot_BMP388_I2C bmp388In;
double valuesBmp388In_T[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388In_T = 0;
double valuesBmp388In_P[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388In_P = 0;

DFRobot_BMP388_I2C bmp388Out;
double valuesBmp388Out_T[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388Out_T = 0;
double valuesBmp388Out_P[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388Out_P = 0;

unsigned long lastMeasurementTimeBmp388 = 0;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init BMP388 in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initBmp388In() {
    bmp388In.set_iic_addr(IN_I2C_ADDR_BMP388);

    if (!bmp388In.begin()) {
        debug("[ OK ] BMP388 IN: Sensor initialized", 2);
        return true;
    } else {
        debug("[ ER ] BMP388 IN: Cannot initialize sensor", 1);
        return false;
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init BMP388 in clean chamber (OUTLET)            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initBmp388Out() {

    bmp388Out.set_iic_addr(OUT_I2C_ADDR_BMP388);

    if (!bmp388Out.begin()) {
        debug("[ OK ] BMP388 OUT: Sensor initialized", 2);
        return true;
    } else {
        debug("[ ER ] BMP388 OUT: Cannot initialize sensor", 1);
        return false;
    }

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read BMP388 in contaminated chamber (INLET)      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readBmp388In() {
 
    // no support for retries yet
    valuesBmp388In_T[(indexBmp388In_T++ % BMP388_MEDIAN_ARRAY)] = bmp388In.readTemperature();
    valuesBmp388In_P[(indexBmp388In_P++ % BMP388_MEDIAN_ARRAY)] = bmp388In.readPressure();
    debug("[ OK ] BMP388 IN: Values T & P fetched from sensor", 2);
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read BMP388 in clean chamber (OUTLET)            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readBmp388Out() {

    // no support for retries yet
    valuesBmp388Out_T[(indexBmp388Out_T++ % BMP388_MEDIAN_ARRAY)] = bmp388Out.readTemperature();
    valuesBmp388Out_P[(indexBmp388Out_P++ % BMP388_MEDIAN_ARRAY)] = bmp388Out.readPressure();
    debug("[ OK ] BMP388 OUT: Values T & P fetched from sensor", 2);
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Schedule BMP388 Reads                            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void scheduleReadBmp388() {

    if (millis() - lastMeasurementTimeBmp388 < BMP388_READ_INTERVAL) {
        return;
    }
    
    for (int i=0; i < BMP388_READ_RETRY; i++) {
        if (readBmp388In()) {
            break;
        }
    }
    for (int i=0; i < BMP388_READ_RETRY; i++) {
        if (readBmp388Out()) {
            break;
        }
    }

    lastMeasurementTimeBmp388 = millis();
}
