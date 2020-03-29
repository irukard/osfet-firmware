#ifndef OSFET_CONFIG_H
#define OSFET_CONFIG_H

// 0 - NoDebug
// 1 - Only Errors
// 2 - All

#define DEBUG_LEVEL             1

#define SERIAL_BAUD_RATE        115200

// I2C Pins mapping
#define I2C_SDA                 D3
#define I2C_SCL                 D4

// INLET - contaminated chamber
#define IN_I2C_ADDR_SHT3X       0x44
#define IN_I2C_ADDR_BMP388      0x76
#define IN_UART_TX_SPS30        D5 // Software Serial MOSI
#define IN_UART_RX_SPS30        D6 // Software Serial MISO

// OUTLET - clean chamber
#define OUT_I2C_ADDR_SHT3X      0x45
#define OUT_I2C_ADDR_BMP388     0x77
#define OUT_UART_TX_SPS30       D7 // Software Serial MOSI
#define OUT_UART_RX_SPS30       D8 // Software Serial MISO

// Time intervals
#define SHT3X_READ_INTERVAL     1000 // Read once a second
#define BMP388_READ_INTERVAL    1000 // Read once a second
#define SPS30_READ_INTERVAL     1000 // Read once a second
#define SERIAL_WRITE_INTERVAL   15000 // Write measurements to serial once per 15 second

// Read retries
#define SHT3X_READ_RETRY        3
#define BMP388_READ_RETRY       3
#define SPS30_READ_RETRY        3

// Median array size
#define SHT3X_MEDIAN_ARRAY      10
#define BMP388_MEDIAN_ARRAY     10
#define SPS30_MEDIAN_ARRAY      10

#endif // OSFET_CONFIG_H