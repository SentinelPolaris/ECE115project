//
// Created by Scott Zhao on 2020-02-06.
//
#include "interface.h"
#include <FreeRTOS_TEENSY4.h>

volatile uint32_t __timer_temp = 0;
/* Old Non-RTOS Flags
volatile bool SERIAL_SET_UP = false;
volatile bool WIRE_DEFINED_FLAG = false;
volatile bool WIRE_CURRENTLY_USED = false;
volatile bool IO_IRQ_WAITING = false;
 */

extern TaskHandle_t xIOTask;

void IOISR() {
    BaseType_t xHigherPriorityTaskWoken;
    // Init xHigherPriorityTaskWoken to pdFALSE. If vTaskNotifyGiveFromISR() clears Block on vIOTask,
    // and vIOTask's priority > currently running task, xHigherPriorityTaskWoken will be set to pdTRUE
    xHigherPriorityTaskWoken = pdFALSE;

    // Notify xIOTask
    vTaskNotifyGiveFromISR(xIOTask,&xHigherPriorityTaskWoken);

    // IF xHigherPriorityTaskWoken was set to true, force context switching
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken)
    /* Old Non-RTOS Implementation
#if DEBUG == 1
    if (IO_IRQ_WAITING) {
        LOGWARNING("IO IRQ Skipped! IRQ triggered without previous flag handled!");
    }
#endif
    IO_IRQ_WAITING = true;
     */
}