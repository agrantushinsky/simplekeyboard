#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f0xx.h"

typedef enum {
    LED_MODE_OFF = 0,
    LED_MODE_ON,
    LED_MODE_BLINK_SLOW,   // 500ms ON / 500ms OFF (1 Hz)
    LED_MODE_BLINK_FAST,   // 100ms ON / 100ms OFF (5 Hz)
    LED_MODE_HEARTBEAT     // Double-pulse heartbeat
} led_mode_t;

void status_led_init(void);
void status_led_on(void);
void status_led_off(void);
void status_led_toggle(void);
void status_led_set_mode(led_mode_t mode);

#endif
