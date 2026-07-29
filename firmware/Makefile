# Target binary name
TARGET = simplekeyboard_firmware

# Device / Linker Definitions
LDSCRIPT = STM32F072XX_FLASH.ld

# Compiler and Toolchain Setup
PREFIX      ?= arm-none-eabi-
CC          = $(PREFIX)gcc
AS          = $(PREFIX)gcc -x assembler-with-cpp
OBJCOPY     = $(PREFIX)objcopy
OBJDUMP     = $(PREFIX)objdump
SIZE        = $(PREFIX)size

# Project Directories
BUILD_DIR   = build
SRC_DIR     = src
INC_DIR     = include
LIBS_DIR    = libs

# Library Directories (Matches your git submodules)
HAL_DIR           = $(LIBS_DIR)/stm32f0xx-hal-driver
CMSIS_DIR         = $(LIBS_DIR)/cmsis-device-f0
CMSIS_CORE_DIR 	  = $(LIBS_DIR)/cmsis-core/CMSIS/Core
FREERTOS_DIR      = $(LIBS_DIR)/FreeRTOS-Kernel
FREERTOS_PORT_DIR = $(FREERTOS_DIR)/portable/GCC/ARM_CM0
TINYUSB_DIR		  = $(LIBS_DIR)/tinyusb/src

# ------------------------------------------------------------------------------
# Source Files
# ------------------------------------------------------------------------------
# Application sources
SRCS += $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/app/*.c)
SRCS += $(wildcard $(SRC_DIR)/drivers/*.c)

# Startup Assembly
ASM_SRCS += $(wildcard $(SRC_DIR)/*.s)

# ST Low-Layer (LL) Sources 
SRCS += $(wildcard $(HAL_DIR)/Src/*_ll_*.c)

# FreeRTOS Kernel Sources
SRCS += $(FREERTOS_DIR)/tasks.c
SRCS += $(FREERTOS_DIR)/queue.c
SRCS += $(FREERTOS_DIR)/list.c
SRCS += $(FREERTOS_DIR)/timers.c
SRCS += $(FREERTOS_DIR)/portable/MemMang/heap_4.c

# TinyUSB Core Sources
SRCS += libs/tinyusb/src/tusb.c
SRCS += libs/tinyusb/src/common/tusb_fifo.c
SRCS += libs/tinyusb/src/device/usbd.c
SRCS += libs/tinyusb/src/class/hid/hid_device.c

# STM32 F0 USB Hardware Driver (Synopsys OTG / FSDEV)
SRCS += libs/tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c

# ------------------------------------------------------------------------------
# Include Directories
# ------------------------------------------------------------------------------
INCLUDES += -I$(INC_DIR)
INCLUDES += -I$(HAL_DIR)/Inc
INCLUDES += -I$(CMSIS_DIR)/Include
INCLUDES += -I$(CMSIS_CORE_DIR)/Include
INCLUDES += -I$(FREERTOS_DIR)/include
INCLUDES += -I$(FREERTOS_PORT_DIR)
INCLUDES += -I$(TINYUSB_DIR)

# ------------------------------------------------------------------------------
# Compiler & Linker Flags
# ------------------------------------------------------------------------------
ARCH_FLAGS  = -mcpu=cortex-m0 -mthumb

# C Flags
CFLAGS   += $(ARCH_FLAGS)
CFLAGS   += -O2 -g3 -Wall -Wextra -Wshadow
CFLAGS   += -DSTM32F072xB
CFLAGS   += -ffunction-sections -fdata-sections
CFLAGS   += $(INCLUDES)
CFLAGS   += -Wno-attributes

# Linker Flags
LDFLAGS  += $(ARCH_FLAGS)
LDFLAGS  += -T$(LDSCRIPT)
LDFLAGS  += -Wl,--gc-sections
LDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS  += --specs=nano.specs --specs=nosys.specs

# Generate Object lists in the build directory
OBJS      = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS     += $(patsubst %.s, $(BUILD_DIR)/%.o, $(ASM_SRCS))

# ==============================================================================
# Build Rules
# ==============================================================================

.PHONY: all clean flash lsp

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo ""
	@echo "--- Firmware Size ---"
	$(SIZE) $(BUILD_DIR)/$(TARGET).elf

# Compile C source files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile Assembly files
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "[AS] $<"
	@$(AS) $(CFLAGS) -c $< -o $@

# Link ELF binary
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo "[LD] $@"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

# Generate HEX file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo "[OBJCOPY] $@"
	@$(OBJCOPY) -O ihex $< $@

# Generate Binary file
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo "[OBJCOPY] $@"
	@$(OBJCOPY) -O binary $< $@

# Generate compile_commands.json for Neovim / clangd
lsp:
	@echo "Generating compile_commands.json for Neovim LSP..."
	@make clean
	@if command -v bear >/dev/null 2>&1; then \
		bear -- make all; \
	elif command -v compiledb >/dev/null 2>&1; then \
		compiledb make all; \
	else \
		echo "ERROR: Neither 'bear' nor 'compiledb' is installed. Install one to generate LSP compile database."; \
		exit 1; \
	fi

# Flash target using OpenOCD & ST-Link
flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

# Clean build artifacts
clean:
	@rm -rf $(BUILD_DIR) compile_commands.json
	@echo "Cleaned build output."
