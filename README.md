# I2C-bit-banging
This project demonstrates how to use GPIO pins to simulate I²C communication. The MCU manually controls the clock (SCL) and data (SDA) lines to communicate with an MPU6050 sensor, allowing measurement of accelerometer data without using the built-in hardware I²C module.

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── sdkconfig
├── README.md    This is the file you are currently reading
├── main
│   ├── CMakeLists.txt
│   └── main.c
├── components
│   └── i2c_bitbang
│       ├── i2c_bitbang.c
│       └── i2c_bitbang.h
```