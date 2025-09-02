#include "i2c_bitbang.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_rom_sys.h"


void i2c_init(uint8_t scl, uint8_t sda){
    gpio_set_direction(scl, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(sda, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_level(scl, 1);
    gpio_set_level(sda, 1);
}
void i2c_start(uint8_t scl, uint8_t sda){
    gpio_set_level(scl, 1);
    gpio_set_level(sda, 1);
    esp_rom_delay_us(5);
    gpio_set_level(sda, 0);
    esp_rom_delay_us(5);
    gpio_set_level(scl, 0);
}
void i2c_stop(uint8_t scl, uint8_t sda){
    gpio_set_level(sda, 0);
    esp_rom_delay_us(5);
    gpio_set_level(scl, 1);
    esp_rom_delay_us(5);
    gpio_set_level(sda, 1);
    esp_rom_delay_us(5);
}
int i2c_write_byte(uint8_t data, uint8_t scl, uint8_t sda){
    uint8_t msb;
    for (int i = 0; i<8; i++){
        msb = (data >> (7-i)) & 0x01;
        gpio_set_level(sda, msb);
        esp_rom_delay_us(5);
        gpio_set_level(scl, 1);
        esp_rom_delay_us(5);
        gpio_set_level(scl, 0);
    }
    gpio_set_level(scl, 1);
    int ack = gpio_get_level(sda);
    gpio_set_level(scl, 0);
    return ack;
}
void i2c_read_byte(uint8_t* buf, uint8_t idx, uint8_t num_reg, uint8_t scl, uint8_t sda){
    uint8_t reg_data = 0;
    for (int i = 0; i<8; i++){
        reg_data = reg_data << 1;
        gpio_set_level(scl, 1);
        esp_rom_delay_us(5);
        reg_data |= gpio_get_level(sda);
        gpio_set_level(scl, 0);
        esp_rom_delay_us(5);
    }
    buf[idx] = reg_data;
    if (idx==num_reg)
        gpio_set_level(sda, 1);//over:NACK
    else
        gpio_set_level(sda, 0);//continue:ACK
    esp_rom_delay_us(5);
    gpio_set_level(scl, 1);
    esp_rom_delay_us(5);
    gpio_set_level(scl, 0);
    gpio_set_level(sda, 1);
}