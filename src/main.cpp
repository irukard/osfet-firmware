#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "utils.h"
#include "sensors/sht3x.h"
#include "sensors/bmp388.h"
#include "sensors/sps30.h"

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
    if (!initBmp388In()) setupFailed = true;
    if (!initBmp388Out()) setupFailed = true;
    if (!initSps30In()) setupFailed = true;
    if (!initSps30Out()) setupFailed = true;
    
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
    scheduleReadSht3x();
    scheduleReadBmp388();
    scheduleReadSps30();
    scheduleWriteCSV();
}
