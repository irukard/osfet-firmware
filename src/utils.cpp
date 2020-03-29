#include "utils.h"

unsigned long lastWriteTimeCSV = 0;
bool displayHeadersCSV = true;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Rerutn median from Array of specified size       ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

double medianFromArray(double values[], int size) {

    // make a copy of values
    double a[size];
    for (int i=0; i<size; i++){
        a[i] = values[i];
    }
   
    // buble sort copy of array
    for(int i=0; i<(size-1); i++) {
        for(int j=0; j<(size-(i+1)); j++) {
            if(a[j] > a[j+1]) {
                double t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }

    // return median
    if (size % 2 == 0) {
        return (a[(size-1)/2] + a[size/2])/2.0;
    } else {
        return a[(size/2)];
    }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ CSV Write on Serial Console                      ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void writeCSV() {
    if (displayHeadersCSV) {
        Serial.println("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
        Serial.println("┃          Exporting DATA in CSV Format            ┃");
        Serial.println("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
        // CSV Values Header
        
        //Serial.print("TIMESTAMP;");
        Serial.print("MILLIS;");
        Serial.print("IN_SHT_T;");
        Serial.print("IN_SHT_H;");
        Serial.print("OUT_SHT_T;");
        Serial.print("OUT_SHT_H;");
        Serial.println();

        displayHeadersCSV = false;
    }

    // Serial.print("2020-03-28 14:50:51;");
    Serial.print(millis()); Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xIn_T, 10)); Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xIn_H, 10)); Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xOut_T, 10)); Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xOut_H, 10)); Serial.print(";");
    Serial.println();
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Schedule CSV Write on Serial Console             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛



void scheduleWriteCSV() {
    if (millis() - lastWriteTimeCSV < SERIAL_WRITE_INTERVAL) {
        return;
    }

    writeCSV();

    lastWriteTimeCSV = millis();
}
