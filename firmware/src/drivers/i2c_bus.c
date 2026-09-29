#include "drivers/i2c_bus.h"
#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_bus.h"

// TODO: Calculate timing
#define I2C_TIMING 0x00901850

void configure_i2c(void) {
    // Enable peripheral clock for GPIOB
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    // Configure SCL
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_8, LL_GPIO_AF_1);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);


    // Configure SDA
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_9, LL_GPIO_AF_1);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);

    // Enable peripheral clock for I2C
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

    // Disable I2C1 before configuration
    LL_I2C_Disable(I2C1);

    LL_I2C_SetTiming(I2C1, I2C_TIMING);
    LL_I2C_EnableAnalogFilter(I2C1);

    LL_I2C_Enable(I2C1);
}

i2c_status_t i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
    // Generate start condition and send device address
    LL_I2C_HandleTransfer(I2C1, dev_addr << 1, LL_I2C_ADDRESSING_MODE_7BIT, 2,
                          LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

    // Transmit register address
    while(!LL_I2C_IsActiveFlag_TXIS(I2C1));
    LL_I2C_TransmitData8(I2C1, reg_addr);

    // Transmit data byte
    while(!LL_I2C_IsActiveFlag_TXIS(I2C1));
    LL_I2C_TransmitData8(I2C1, data);

    // Wait for stop flag
    while(!LL_I2C_IsActiveFlag_STOP(I2C1));
    LL_I2C_ClearFlag_STOP(I2C1);

    return I2C_OK;
}

i2c_status_t i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data) {
    // Generate start condition and send device address
    LL_I2C_HandleTransfer(I2C1, dev_addr << 1, LL_I2C_ADDRESSING_MODE_7BIT, 1,
                          LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);

    // Transmit register address
    while(!LL_I2C_IsActiveFlag_TXIS(I2C1));
    LL_I2C_TransmitData8(I2C1, reg_addr);

    // Wait until the register address byte has been transmitted
    while (!LL_I2C_IsActiveFlag_TC(I2C1));

    // Switch to read mode
    LL_I2C_HandleTransfer(I2C1, dev_addr << 1, LL_I2C_ADDRESSING_MODE_7BIT, 1,
                          LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

    // Wait for and read the byte
    while (!LL_I2C_IsActiveFlag_RXNE(I2C1));
    *data = LL_I2C_ReceiveData8(I2C1);

    // Wait for stop flag
    while(!LL_I2C_IsActiveFlag_STOP(I2C1));
    LL_I2C_ClearFlag_STOP(I2C1);

    return I2C_OK;
}
