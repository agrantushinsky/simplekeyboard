#ifndef MCP230XX_REGS_H
#define MCP230XX_REGS_H

// =============================================================================
// MCP23008 Register Map (8-bit / Single Port)
// =============================================================================
#define MCP23008_IODIR      0x00
#define MCP23008_IPOL       0x01
#define MCP23008_GPINTEN    0x02
#define MCP23008_DEFVAL     0x03
#define MCP23008_INTCON     0x04
#define MCP23008_IOCON      0x05
#define MCP23008_GPPU       0x06
#define MCP23008_INTF       0x07
#define MCP23008_INTCAP     0x08
#define MCP23008_GPIO       0x09
#define MCP23008_OLAT       0x0A

// =============================================================================
// MCP23017 Register Map (16-bit / BANK = 0 Interleaved)
// =============================================================================

// I/O Direction Registers (1 = Input, 0 = Output)
#define MCP23017_IODIRA     0x00
#define MCP23017_IODIRB     0x01

// Input Polarity Registers (1 = Inverted, 0 = Normal)
#define MCP23017_IPOLA      0x02
#define MCP23017_IPOLB      0x03

// Interrupt-on-Change Enable Registers (1 = Enable, 0 = Disable)
#define MCP23017_GPINTENA   0x04
#define MCP23017_GPINTENB   0x05

// Default Compare Value Registers for Interrupts
#define MCP23017_DEFVALA    0x06
#define MCP23017_DEFVALB    0x07

// Interrupt Control Registers (1 = Compare against DEFVAL, 0 = Compare against previous pin value)
#define MCP23017_INTCONA    0x08
#define MCP23017_INTCONB    0x09

// Configuration Register (0x0B is an alias for 0x0A in BANK = 0)
#define MCP23017_IOCON      0x0A
#define MCP23017_IOCON_ALIAS 0x0B

// Pull-Up Resistor Configuration Registers (1 = Enable 10k internal pull-up)
#define MCP23017_GPPUA      0x0C
#define MCP23017_GPPUB      0x0D

// Interrupt Flag Registers (Read-Only: 1 = Pin caused interrupt)
#define MCP23017_INTFA      0x0E
#define MCP23017_INTFB      0x0F

// Interrupt Capture Registers (Read-Only: Pin state at moment of interrupt)
#define MCP23017_INTCAPA    0x10
#define MCP23017_INTCAPB    0x11

// Port Registers (Read = Reads physical pins, Write = Writes output latch)
#define MCP23017_GPIOA      0x12
#define MCP23017_GPIOB      0x13

// Output Latch Registers (Read/Write = Output Latch values)
#define MCP23017_OLATA      0x14
#define MCP23017_OLATB      0x15

// =============================================================================
// IOCON Configuration Bit Masks (Shared across both MCP23008 & MCP23017)
// =============================================================================
#define MCP_IOCON_BANK      (1 << 7) // 1 = BANK 1 (Separated), 0 = BANK 0 (Interleaved - MCP23017 only)
#define MCP_IOCON_MIRROR    (1 << 6) // 1 = INTA and INTB connected internally (MCP23017 only)
#define MCP_IOCON_SEQOP     (1 << 5) // 1 = Sequential operation disabled, 0 = Enabled
#define MCP_IOCON_DISSLW    (1 << 4) // 1 = Slew rate control disabled, 0 = Enabled
#define MCP_IOCON_HAEN      (1 << 3) // Hardware Address Enable (SPI version only)
#define MCP_IOCON_ODR       (1 << 2) // 1 = INT pin Open-Drain, 0 = Active Driver
#define MCP_IOCON_INTPOL    (1 << 1) // 1 = Active-HIGH INT pin, 0 = Active-LOW INT pin

// =============================================================================
// Convenient Port A Aliases
// =============================================================================
#define MCP_IODIRA          MCP23017_IODIRA
#define MCP_IODIRB          MCP23017_IODIRB
#define MCP_IPOLA           MCP23017_IPOLA
#define MCP_IPOLB           MCP23017_IPOLB
#define MCP_GPINTENA        MCP23017_GPINTENA
#define MCP_GPINTENB        MCP23017_GPINTENB
#define MCP_DEFVALA         MCP23017_DEFVALA
#define MCP_DEFVALB         MCP23017_DEFVALB
#define MCP_INTCONA         MCP23017_INTCONA
#define MCP_INTCONB         MCP23017_INTCONB
#define MCP_GPPUA           MCP23017_GPPUA
#define MCP_GPPUB           MCP23017_GPPUB
#define MCP_INTFA           MCP23017_INTFA
#define MCP_INTFB           MCP23017_INTFB
#define MCP_INTCAPA         MCP23017_INTCAPA
#define MCP_INTCAPB         MCP23017_INTCAPB
#define MCP_GPIOA           MCP23017_GPIOA
#define MCP_GPIOB           MCP23017_GPIOB
#define MCP_OLATA           MCP23017_OLATA
#define MCP_OLATB           MCP23017_OLATB

#endif
