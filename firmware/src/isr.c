/**
 ******************************************************************************
 * @file    stm32f0xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "stm32f0xx_ll_exti.h"
#include "drivers/status_led.h"

//extern PCD_HandleTypeDef hpcd_USB_FS;
//extern TIM_HandleTypeDef htim1;

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
    while (1)
    {

    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    while(1)
    {

    }
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles EXTI line 0 and 1 interrupts.
 */
void EXTI0_1_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
    }
}

/**
 * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
 */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    //HAL_TIM_IRQHandler(&htim1);
}

/**
 * @brief This function handles USB global interrupt / USB wake-up interrupt through EXTI line 18.
 */
void USB_IRQHandler(void)
{
    //HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

