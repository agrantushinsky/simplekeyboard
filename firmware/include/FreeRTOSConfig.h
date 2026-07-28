#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

// ==========================================================================
// Core Processor & Timing Settings
// ==========================================================================
#define configENABLE_MPU                        0
#define configUSE_PREEMPTION                    1
#define configUSE_TIME_SLICING                  1
#define configCPU_CLOCK_HZ                      ( ( uint32_t ) 48000000 ) // 48MHz for STM32F072
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )   // 1kHz SysTick (1ms)
#define configMAX_PRIORITIES                    ( 5 )
#define configMINIMAL_STACK_SIZE                ( ( uint16_t ) 128 )      // Words (512 bytes)
#define configMAX_TASK_NAME_LEN                 ( 16 )
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0

// ==========================================================================
// Synchronization & IPC Primitives
// ==========================================================================
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_QUEUE_SETS                    0
#define configUSE_TASK_NOTIFICATIONS            1

// ==========================================================================
// Memory Allocation
// ==========================================================================
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 8 * 1024 ) ) // 8KB RTOS Heap

// ==========================================================================
// Software Timers
// ==========================================================================
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( 2 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            ( 128 )

// ==========================================================================
// API Function Inclusion Flags
// ==========================================================================
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1

// ==========================================================================
// Interrupt Handler Vector Remapping for Cortex-M0 CMSIS
// ==========================================================================
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

static inline uint32_t ulSetInterruptMask(void) {
    uint32_t ulResult;
    __asm volatile("mrs %0, primask \n cpsid i" : "=r"(ulResult) :: "memory");
    return ulResult;
}

static inline void vClearInterruptMask(uint32_t ulNewMaskValue) {
    __asm volatile("msr primask, %0" :: "r"(ulNewMaskValue) : "memory");
}

#endif /* FREERTOS_CONFIG_H */
