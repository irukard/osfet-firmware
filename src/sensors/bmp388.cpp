#include "bmp388.h"

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ BMP388 global variables                          ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

double valuesBmp388In_T[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388In_T = 0;
double valuesBmp388In_P[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388In_P = 0;

double valuesBmp388Out_T[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388Out_T = 0;
double valuesBmp388Out_P[BMP388_MEDIAN_ARRAY];
unsigned int indexBmp388Out_P = 0;

unsigned long lastMeasurementTimeBmp388 = 0;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init BMP388 in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initBmp388In() {

    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init BMP388 in clean chamber (OUTLET)            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initBmp388Out() {

    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read BMP388 in contaminated chamber (INLET)      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readBmp388In() {
    
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read BMP388 in clean chamber (OUTLET)            ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readBmp388Out() {

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
