#include "app/config.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"

const config_t g_config = {
    .col_expander = { 
        .i2c_addr = 0x21, 
        .type = MCP_TYPE_23017 
    },
    .row_expander = { 
        .i2c_addr = 0x20, 
        .type = MCP_TYPE_23008 
    },
    .status_led = { 
        .port = GPIOA,
        .pin = LL_GPIO_PIN_6,
        .periph = LL_AHB1_GRP1_PERIPH_GPIOA
    },
    .row_int_pin = { 
        .port = GPIOA,
        .pin = LL_GPIO_PIN_0
    }
};

