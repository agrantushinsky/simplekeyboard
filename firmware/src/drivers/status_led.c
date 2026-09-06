#include "drivers/status_led.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "app/config.h"

static TimerHandle_t s_led_timer = NULL;
static led_mode_t s_current_mode = LED_MODE_OFF;
static uint8_t s_hb_step = 0;

static void led_timer_callback(TimerHandle_t xTimer);

/* -------------------------------------------------------------------------- */
/* Low-Level Driver Implementation                                            */
/* -------------------------------------------------------------------------- */

void status_led_init(void) {
    // Enable clock for the respective GPIO port
    LL_AHB1_GRP1_EnableClock(g_config.status_led.periph);

    // Configure GPIO Pin
    LL_GPIO_SetPinMode(g_config.status_led.port, g_config.status_led.pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(g_config.status_led.port, g_config.status_led.pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(g_config.status_led.port, g_config.status_led.pin, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinPull(g_config.status_led.port, g_config.status_led.pin, LL_GPIO_PULL_NO);

    status_led_off();

    if (s_led_timer == NULL) {
        s_led_timer = xTimerCreate(
            "LED_Timer",
            pdMS_TO_TICKS(500),
            pdTRUE,
            NULL,
            led_timer_callback
        );
    }
}

void status_led_on(void) {
    LL_GPIO_SetOutputPin(g_config.status_led.port, g_config.status_led.pin);
}

void status_led_off(void) {
    LL_GPIO_ResetOutputPin(g_config.status_led.port, g_config.status_led.pin);
}

void status_led_toggle(void) {
    LL_GPIO_TogglePin(g_config.status_led.port, g_config.status_led.pin);
}

static void led_timer_callback(TimerHandle_t xTimer) {
    (void)xTimer;

    switch (s_current_mode) {
        case LED_MODE_BLINK_SLOW:
        case LED_MODE_BLINK_FAST:
            status_led_toggle();
            break;

        case LED_MODE_HEARTBEAT:
            // Heartbeat: ON(80ms) -> OFF(80ms) -> ON(80ms) -> OFF(760ms)
            switch (s_hb_step) {
                case 0: // End 1st pulse -> Turn OFF
                    status_led_off();
                    s_hb_step = 1;
                    xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(80), 0);
                    break;

                case 1: // End 1st gap -> Turn ON (2nd pulse)
                    status_led_on();
                    s_hb_step = 2;
                    xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(80), 0);
                    break;

                case 2: // End 2nd pulse -> Turn OFF (Long gap)
                    status_led_off();
                    s_hb_step = 3;
                    xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(760), 0);
                    break;

                case 3: // End long gap -> Turn ON (1st pulse)
                default:
                    status_led_on();
                    s_hb_step = 0;
                    xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(80), 0);
                    break;
            }
            break;

        case LED_MODE_OFF:
        case LED_MODE_ON:
        default:
            break;
    }
}

void status_led_set_mode(led_mode_t mode) {
    if (s_led_timer == NULL) {
        return;
    }

    s_current_mode = mode;
    s_hb_step = 0;

    switch (mode) {
        case LED_MODE_OFF:
            xTimerStop(s_led_timer, 0);
            status_led_off();
            break;

        case LED_MODE_ON:
            xTimerStop(s_led_timer, 0);
            status_led_on();
            break;

        case LED_MODE_BLINK_SLOW:
            status_led_off();
            xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(500), 0);
            xTimerStart(s_led_timer, 0);
            break;

        case LED_MODE_BLINK_FAST:
            status_led_off();
            xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(100), 0);
            xTimerStart(s_led_timer, 0);
            break;

        case LED_MODE_HEARTBEAT:
            status_led_on();
            s_hb_step = 0;
            xTimerChangePeriod(s_led_timer, pdMS_TO_TICKS(80), 0);
            xTimerStart(s_led_timer, 0);
            break;
    }
}
