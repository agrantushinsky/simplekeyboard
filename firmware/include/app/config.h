#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "drivers/mcp230xx.h"
#include "stm32f0xx.h"

#define MCP23017_ADDR 0x21
#define MCP23008_ADDR 0x20

typedef struct {
    // I2C Peripherals
    mcp230xx_t col_expander;
    mcp230xx_t row_expander;

    // Direct MCU Pins
    struct {
        GPIO_TypeDef* port;
        uint32_t      pin;
        uint32_t      periph;
    } status_led;

    struct {
        GPIO_TypeDef* port;
        uint32_t      pin;
    } row_int_pin;
} config_t;

extern const config_t g_config;

#endif

