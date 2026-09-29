#include "FreeRTOS.h"
#include "task.h"

void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
}
