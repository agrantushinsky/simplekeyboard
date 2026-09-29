#include "drivers/mcp230xx.h"
#include "drivers/mcp230xx_regs.h"

static uint8_t resolve_register(mcp230xx_t *dev, mcp_port_t port, uint8_t reg_base_a) {
    if(dev->type == MCP_TYPE_23008) {
        switch (reg_base_a) {
            case MCP23017_IOCON:   return MCP23008_IOCON;
            case MCP23017_GPPUA:   return MCP23008_GPPU;
            case MCP23017_INTFA:   return MCP23008_INTF;
            case MCP23017_INTCAPA: return MCP23008_INTCAP;
            case MCP23017_GPIOA:   return MCP23008_GPIO;
            case MCP23017_OLATA:   return MCP23008_OLAT;
            default:               return reg_base_a;
        }
    }

    return (port == MCP_PORT_B) ? (reg_base_a + 1) : reg_base_a;
}

// =================================================================
// Generic read/write
// =================================================================
i2c_status_t mcp230xx_write_reg(mcp230xx_t *dev, uint8_t reg, uint8_t value) {
    return i2c_write_reg(dev->i2c_addr, reg, value);
}

i2c_status_t mcp230xx_read_reg(mcp230xx_t *dev, uint8_t reg, uint8_t *value) {
    return i2c_read_reg(dev->i2c_addr, reg, value);
}

// =================================================================
// Pin Configuration
// =================================================================
i2c_status_t mcp230xx_set_direction(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_IODIRA);
    return mcp230xx_write_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_set_input_polarity(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_IPOLA);
    return mcp230xx_write_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_set_enable_interrupt(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_GPINTENA);
    return mcp230xx_write_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_set_default_value(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_DEFVALA);
    return mcp230xx_write_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_set_interrupt_behaviour(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_INTCONA);
    return mcp230xx_write_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_set_config(mcp230xx_t *dev, uint8_t iocon_mask) {
    uint8_t reg = (dev->type == MCP_TYPE_23008) ? MCP23008_IOCON : MCP23017_IOCON;
    return mcp230xx_write_reg(dev, reg, iocon_mask);
}

i2c_status_t mcp230xx_set_pullups(mcp230xx_t *dev, mcp_port_t port, uint8_t mask) {
    uint8_t reg = resolve_register(dev, port, MCP_GPPUA);
    return mcp230xx_write_reg(dev, reg, mask);
}

// =================================================================
// Read-only data
// =================================================================
i2c_status_t mcp230xx_read_interrupt_flag(mcp230xx_t *dev, mcp_port_t port, uint8_t *mask) {
    uint8_t reg = resolve_register(dev, port, MCP_INTFA);
    return mcp230xx_read_reg(dev, reg, mask);
}

i2c_status_t mcp230xx_read_interrupt_capture(mcp230xx_t *dev, mcp_port_t port, uint8_t *mask) {
    uint8_t reg = resolve_register(dev, port, MCP_INTCAPA);
    return mcp230xx_read_reg(dev, reg, mask);
}

// =================================================================
// Port read/write
// =================================================================
i2c_status_t mcp230xx_write_port(mcp230xx_t *dev, mcp_port_t port, uint8_t value) {
    uint8_t reg = resolve_register(dev, port, MCP_OLATA);
    return mcp230xx_write_reg(dev, reg, value);
}

i2c_status_t mcp230xx_read_port(mcp230xx_t *dev, mcp_port_t port, uint8_t *value) {
    uint8_t reg = resolve_register(dev, port, MCP_GPIOA);
    return mcp230xx_read_reg(dev, reg, value);
}

