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
        
        Serial.print("TIMESTAMP;");
        Serial.print("IN_SHT_T;");
        Serial.print("IN_SHT_H;");
        Serial.print("IN_BMP_T;");
        Serial.print("IN_BMP_P;");
        Serial.print("OUT_SHT_T;");
        Serial.print("OUT_SHT_H;");
        Serial.print("OUT_BMP_T;");
        Serial.print("OUT_BMP_P;");


        Serial.println();

        displayHeadersCSV = false;
    }

    Serial.print(currentTimeStamp());                                       Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xIn_T, SHT3X_MEDIAN_ARRAY));     Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xIn_H, SHT3X_MEDIAN_ARRAY));     Serial.print(";");
    Serial.print(medianFromArray(valuesBmp388In_T, BMP388_MEDIAN_ARRAY));   Serial.print(";");
    Serial.print(medianFromArray(valuesBmp388In_P, BMP388_MEDIAN_ARRAY));   Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xOut_T, SHT3X_MEDIAN_ARRAY));    Serial.print(";");
    Serial.print(medianFromArray(valuesSht3xOut_H, SHT3X_MEDIAN_ARRAY));    Serial.print(";");
    Serial.print(medianFromArray(valuesBmp388Out_T, BMP388_MEDIAN_ARRAY));  Serial.print(";");
    Serial.print(medianFromArray(valuesBmp388Out_P, BMP388_MEDIAN_ARRAY));  Serial.print(";");
    Serial.println();
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Schedule CSV Write on Serial Console             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void scheduleWriteCSV() {
    if (millis() - lastWriteTimeCSV < SERIAL_WRITE_INTERVAL) {
        return;
    }

    lastWriteTimeCSV = millis();
    writeCSV();
 
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Timestamp with milisecond precision              ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

String currentTimeStamp() {
    String tmp = "";
    unsigned dt = 0;
    unsigned long t = millis();

    if ((dt = t / (60 * 60 * 1000)) > 0)  {
        t = t - dt * 60 * 60 * 1000;

        if (dt < 10) {
            tmp += String("0"); // hours - leading zero
        }

        tmp += String(dt) + String(":"); // hours
    } else {
        tmp += String("00:"); // hours
    }

    if ((dt = t / (60 * 1000)) > 0) {
        t = t - dt * 60 * 1000;

        if (dt < 10) {
            tmp += String("0"); // minutes - leading zero
        }

        tmp += String(dt) + String(":"); // minutes

    } else {
        tmp += String("00:"); // minutes
    }

    if ((dt = t / (1000)) > 0) {
        t = t - dt * 1000;

        if (dt < 10) {
            tmp += String("0"); // seconds - leading zero
        }

        tmp += String(dt) + String(","); // seconds

    } else {
        tmp += String("00,"); // seconds
    }

    if (t < 10) {
        tmp += String("0"); // miliseconds - leading zero
    }

    if (t < 100) {
        tmp += String("0"); // miliseconds - leading zero
    }

    tmp += String(t); // miliseconds

    return tmp;    
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Debug output                                     ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

void debug(const String& message, const int level) {

    if (level <= DEBUG_LEVEL) {
        String tmp = "";
        tmp += currentTimeStamp() + String(": ") + message;
        Serial.println(tmp);
    }

}
