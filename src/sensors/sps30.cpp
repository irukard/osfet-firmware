#include "sps30.h"

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ SPS30 global variables                           ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

SoftwareSerial serialSPSIn(IN_UART_TX_SPS30, IN_UART_RX_SPS30, false);
SoftwareSerial serialSPSOut(OUT_UART_TX_SPS30, OUT_UART_RX_SPS30, false);

unsigned long lastMeasurementTimeSps30 = 0;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SPS30 in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSps30In(){
    
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Init SPS30 in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool initSps30Out(){
    
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SPS30 in contaminated chamber (INLET)       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSps30In(){
    
    return true;

}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Read SPS30 in clean chamber (OUTLET)             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

bool readSps30Out(){
    
    return true;
    
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Schedule SHT3x Reads                             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void scheduleReadSps30() {

    if (millis() - lastMeasurementTimeSps30 < SPS30_READ_INTERVAL) {
        return;
    }
    
    for (int i=0; i < SPS30_READ_RETRY; i++) {
        if (readSps30In()) {
            break;
        }
    }
    for (int i=0; i < SPS30_READ_RETRY; i++) {
        if (readSps30Out()) {
            break;
        }
    }

    lastMeasurementTimeSps30 = millis();
}
