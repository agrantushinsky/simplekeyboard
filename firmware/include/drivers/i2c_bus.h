#ifndef I2C_BUS_H
#define I2C_BUS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    I2C_OK = 0,
    I2C_ERR_TIMEOUT,
    I2C_ERR_NACK
} i2c_status_t;

void configure_i2c(void);

i2c_status_t i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);

i2c_status_t i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);

#endif
