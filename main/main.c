#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_bitbang.h"
#include "driver/gpio.h"
#include "esp_private/esp_clk.h"

#define MPU6050_ADDR 0X68
#define MPU6050_PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define NUM_REG 6
#define W_BIT 0
#define R_BIT 1
#define WAKEUP_VAL 0x00
#define SCL 18
#define SDA 17

void wakeup_mpu6050(uint8_t scl, uint8_t sda){
    i2c_init(SCL, SDA);
    i2c_start(scl, sda);
    if (!i2c_write_byte(MPU6050_ADDR << 1 | W_BIT, scl, sda)){
        if (!i2c_write_byte(MPU6050_PWR_MGMT_1, scl, sda)){
            if (!i2c_write_byte(WAKEUP_VAL, scl, sda)){
                i2c_stop(scl, sda);
            }
        }
        else{
            printf("I2C write reg failed!\n");
            i2c_stop(scl, sda);
        }
    }
    else{
        printf("I2C write sensor addr failed!\n");
        i2c_stop(scl, sda);
    }
}

void read_mpu6050_accel(uint8_t scl, uint8_t sda, uint8_t *accel){
    i2c_init(SCL, SDA);
    i2c_start(scl, sda);
    if (!i2c_write_byte(MPU6050_ADDR << 1 | W_BIT, scl, sda)) {
        if (!i2c_write_byte(ACCEL_XOUT_H, scl, sda)) {
            i2c_start(scl, sda);                // Repeated START
            if (!i2c_write_byte((MPU6050_ADDR << 1) | R_BIT, scl, sda)) {
                for (uint8_t i = 0; i < NUM_REG; i++){
                    i2c_read_byte(accel, i, NUM_REG, scl, sda);
                }
                i2c_stop(scl, sda);
                int16_t accel_x = (accel[0] << 8) | accel[1];
                int16_t accel_y = (accel[2] << 8) | accel[3];
                int16_t accel_z = (accel[4] << 8) | accel[5];
                printf("Accel X: %d, Y: %d, Z: %d\n", accel_x, accel_y, accel_z);
            }
            else{
                printf("I2C read failed!\n");
                i2c_stop(scl, sda);
            }
        }
        else{
            printf("I2C write reg failed!\n");
            i2c_stop(scl, sda);
        }
    }
    else{
        printf("I2C write sensor addr failed!\n");
        i2c_stop(scl, sda);
    }

}

void app_main(void){
    while(1){
        uint8_t accel[6] = {0};
        wakeup_mpu6050(SCL, SDA);
        read_mpu6050_accel(SCL, SDA, accel);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
