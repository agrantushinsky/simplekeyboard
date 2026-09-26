#include "stm32f0xx.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "app/config.h"
#include "drivers/status_led.h"

#include "tusb.h"

#include "class/hid/hid.h"

void SystemClock_Config(void);

#include "class/hid/hid.h"
#include "drivers/usb_hid_descriptors.h" // Include your structs

void hid_task(void *param) {
    (void)param;

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5000));

        if (tud_hid_ready()) {
            
            // 1. Initialize a clean 16-byte struct
            nkro_keyboard_report_t report = {0};
            
            // 2. Press 'a' (HID_KEY_A is 0x04)
            //report.key_bits[0] |= (1 << 4);
            
            // 3. Send the custom struct (TinyUSB prepends the '1' for us)
            tud_hid_report(1, &report, sizeof(report)); 
            
            vTaskDelay(pdMS_TO_TICKS(15)); 

            // 4. Release all keys by sending a blank struct
            nkro_keyboard_report_t empty_report = {0};
            tud_hid_report(1, &empty_report, sizeof(empty_report));
        }
    }
}

void vInitTask(void *pvParameters) {
    (void)pvParameters;
    status_led_init();
    status_led_set_mode(LED_MODE_HEARTBEAT);

    vTaskDelete(NULL);
}

#define USBD_STACK_SIZE   (3 * configMINIMAL_STACK_SIZE)
#define USBD_PRIORITY     (configMAX_PRIORITIES - 1)

void usb_device_task(void *param) {
    (void)param;

    tusb_rhport_init_t rh_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_FULL
    };
    
    // Initialize the TinyUSB device stack
    if(!tusb_init(0, &rh_init)) {
        while(1) { }
    }

    while (1) {
        // Processes pending USB events. Blocks automatically if empty.
        tud_task(); 
        vTaskDelay(1);
    }
}

int main(void)
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CRS);
    SystemClock_Config();

    // 1. Route clock power to the USB peripheral
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USB);

    // 2. Configure PA11 and PA12 for USB Alternate Function 2 (AF2)
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_12, LL_GPIO_MODE_ALTERNATE);
    
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_HIGH);
    
    // Pins 11 and 12 are in the "High" register (8-15)
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_11, LL_GPIO_AF_2);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_12, LL_GPIO_AF_2);

    // 3. Enable the USB hardware interrupt so TinyUSB can receive events
    NVIC_SetPriority(USB_IRQn, 2);
    NVIC_EnableIRQ(USB_IRQn);

    BaseType_t result = xTaskCreate(vInitTask, "Init", 128, NULL, 1, NULL);
    if (result != pdPASS) {
        while(1) { }
    }
    xTaskCreate(usb_device_task, "usbd", USBD_STACK_SIZE, NULL, USBD_PRIORITY, NULL);

    // Create the HID typing task
    xTaskCreate(hid_task, "hid", 256, NULL, USBD_PRIORITY - 1, NULL);

    vTaskStartScheduler();

    while(1) { }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
    while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
    {
    }
    LL_RCC_HSI_Enable();

    /* Wait till HSI is ready */
    while(LL_RCC_HSI_IsReady() != 1)
    {

    }
    LL_RCC_HSI_SetCalibTrimming(16);
    LL_RCC_HSI48_Enable();

    /* Wait till HSI48 is ready */
    while(LL_RCC_HSI48_IsReady() != 1)
    {

    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI48);

    /* Wait till System clock is ready */
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI48)
    {

    }
    LL_SetSystemCoreClock(48000000);
    LL_Init1msTick(48000000);

    LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
    LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);
    LL_CRS_SetSyncDivider(LL_CRS_SYNC_DIV_1);
    LL_CRS_SetSyncPolarity(LL_CRS_SYNC_POLARITY_RISING);
    LL_CRS_SetSyncSignalSource(LL_CRS_SYNC_SOURCE_USB);
    LL_CRS_SetFreqErrorLimit(34);
    LL_CRS_SetHSI48SmoothTrimming(32);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {

    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

