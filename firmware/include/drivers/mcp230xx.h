#ifndef MCP230XX_H
#define MCP230XX_H

#include <stdint.h>
#include <stdbool.h>

#include "drivers/i2c_bus.h"

typedef enum {
    MCP_TYPE_23008 = 0,
    MCP_TYPE_23017
} mcp_type_t;

typedef enum {
    MCP_PORT_A = 0,
    MCP_PORT_B
} mcp_port_t;

typedef struct {
    uint8_t i2c_addr;
    mcp_type_t type;
} mcp230xx_t;

// =================================================================
// Generic read/write
// =================================================================
i2c_status_t mcp230xx_write_reg(mcp230xx_t *dev, uint8_t reg, uint8_t value);
i2c_status_t mcp230xx_read_reg(mcp230xx_t *dev, uint8_t reg, uint8_t *value);


// =================================================================
// Pin Configuration
// =================================================================
i2c_status_t mcp230xx_set_direction(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);
i2c_status_t mcp230xx_set_input_polarity(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);
i2c_status_t mcp230xx_set_enable_interrupt(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);
i2c_status_t mcp230xx_set_default_value(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);
i2c_status_t mcp230xx_set_interrupt_behaviour(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);
i2c_status_t mcp230xx_set_config(mcp230xx_t *dev, uint8_t iocon_mask);
i2c_status_t mcp230xx_set_pullups(mcp230xx_t *dev, mcp_port_t port, uint8_t mask);

// =================================================================
// Read-only data
// =================================================================
i2c_status_t mcp230xx_read_interrupt_flag(mcp230xx_t *dev, mcp_port_t port, uint8_t *mask);
i2c_status_t mcp230xx_read_interrupt_capture(mcp230xx_t *dev, mcp_port_t port, uint8_t *mask);

// =================================================================
// Port read/write
// =================================================================
i2c_status_t mcp230xx_write_port(mcp230xx_t *dev, mcp_port_t port, uint8_t value);
i2c_status_t mcp230xx_read_port(mcp230xx_t *dev, mcp_port_t port, uint8_t *value);

#endif

