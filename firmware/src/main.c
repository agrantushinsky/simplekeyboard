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

void SystemClock_Config(void);

void vInitTask(void *pvParameters)
{
    status_led_init();
    status_led_set_mode(LED_MODE_HEARTBEAT);

    vTaskDelete(NULL);
}

int main(void)
{
    SystemClock_Config();

    BaseType_t result = xTaskCreate(vInitTask, "Init", 128, NULL, 1, NULL);
    if (result != pdPASS) {
        while(1) { }
    }

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

