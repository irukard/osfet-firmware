#ifndef OSFET_CONFIG_H
#define OSFET_CONFIG_H

#define SERIAL_BAUD_RATE   115200


// I2C Pins mapping
#define I2C_SDA D3
#define I2C_SCL D4

// INLET - contaminated chamber
#define IN_I2C_ADDR_SHT3X 0x44
#define IN_I2C_ADDR_BMP388 0x76
#define IN_UART_TX_SPS30 D5 // Software Serial MOSI
#define IN_UART_RX_SPS30 D6 // Software Serial MISO

// OUTLET - clean chamber
#define OUT_I2C_ADDR_SHT3X 0x45
#define OUT_I2C_ADDR_BMP388 0x77
#define OUT_UART_TX_SPS30 D7 // Software Serial MOSI
#define OUT_UART_RX_SPS30 D8 // Software Serial MISO

#endif // OSFET_CONFIG_H