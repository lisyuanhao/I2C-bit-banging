#ifndef I2C_BITBANG_H
#define I2C_BITBANG_H
#include <stdint.h>
#include <stdbool.h>
void i2c_init(uint8_t scl, uint8_t sda);
void i2c_start(uint8_t scl, uint8_t sda);
void i2c_stop(uint8_t scl, uint8_t sda);
int i2c_write_byte(uint8_t data, uint8_t scl, uint8_t sda);
void i2c_read_byte(uint8_t* buf, uint8_t idx, uint8_t num_reg, uint8_t scl, uint8_t sda);

#endif // I2C_BITBANG_H
