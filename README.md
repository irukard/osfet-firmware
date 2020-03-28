# Open Source Filter Efficiency Tester

## Firmware Repository

The goal of Osfet Project is to build small, replicable and affordable lab equipment for testing filtering efficiency of different materials.

### Suported sensors

During research phase of OSFET project we decided to use most accurate sensors in their price range.

We chose Sensirion SPS30 because of their excelent performance and factory calibration using TSI DustTrack 8533. Sensirion is also known for remarkable build quality.

In our opinion SHT35 is the most accurate sensor in it's class. SHT31 is a cheaper variant with also great performance.

Bosch Sensortec BMP388 was selected without any experience with this sensor. According to it's datasheet it's a very precise barometric sensor.

* Sensirion SPS30 - Particulate Matter Sensor - due to only one I2C address, in this project we use UART.
* Sensirion SHT30, SHT31 or SHT35 - Temperature and relative humidity sensor. Two sensors connected via I2C bus (0x44, 0x45).
* Bosch Sensortec BMP388 - Temperature and pressure. Two sensors connected via I2C bus (0x76, 0x77).

### Documentation

* [Hardware Repository](https://github.com/irukard/osfet-hardware)
* [License](LICENSE) - The TAPR Open Hardware License
