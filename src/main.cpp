#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "sensors/sht3x.h"

// #include <SoftwareSerial.h>
// SoftwareSerial serialSPSIn(IN_UART_TX_SPS30, IN_UART_RX_SPS30, false);
// SoftwareSerial serialSPSOut(OUT_UART_TX_SPS30, OUT_UART_RX_SPS30, false);


void setup() {
    bool setupFailed = false;
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();
    Serial.println("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    Serial.println("┃       Open Source Filter Efficiency Tester       ┃");
    Serial.println("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
    Serial.println("┃                  Sensors Init                    ┃");
    Serial.println("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!initSht3xIn()) setupFailed = true;
    if (!initSht3xOut()) setupFailed = true;
    
    if (setupFailed) {
        Serial.println("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
        Serial.println("┃             Sensors Init Failed!                 ┃");
        Serial.println("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
        Serial.println("Reboot in: ");
        for (int i = 10; i > 0; i--) {
            Serial.print(i);
            Serial.print("... ");
            delay(1000);
        }
        ESP.restart();
    } else {
        Serial.println("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
        Serial.println("┃            Sensors Init Completed!               ┃");
        Serial.println("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    }

}

void loop() {
    if (readSht3xIn()) {
        Serial.print(lastValueSht3xIn_T); Serial.println(" *C");
        Serial.print(lastValueSht3xIn_H); Serial.println(" %");
    }

    if (readSht3xOut()) {
        Serial.print(lastValueSht3xOut_T); Serial.println(" *C");
        Serial.print(lastValueSht3xOut_H); Serial.println(" %");
    }

    delay(1000);
}
