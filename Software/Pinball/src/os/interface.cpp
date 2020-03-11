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
extern volatile bool ISRHandled;

void IOISR() {
    if(ISRHandled) {
        ISRHandled = false;
        BaseType_t xHigherPriorityTaskWoken;
        // Init xHigherPriorityTaskWoken to pdFALSE. If vTaskNotifyGiveFromISR() clears Block on vIOTask,
        // and vIOTask's priority > currently running task, xHigherPriorityTaskWoken will be set to pdTRUE
        xHigherPriorityTaskWoken = pdFALSE;

        // Notify xIOTask
        vTaskNotifyGiveFromISR(xIOTask, &xHigherPriorityTaskWoken);

        // IF xHigherPriorityTaskWoken was set to true, force context switching
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken)
    }
    /* Old Non-RTOS Implementation
#if DEBUG == 1
    if (IO_IRQ_WAITING) {
        LOGWARNING("IO IRQ Skipped! IRQ triggered without previous flag handled!");
    }
#endif
    IO_IRQ_WAITING = true;
     */
}

void i2cCheck() {
    Wire.begin();

    byte error, address;
    int nDevices;

    Serial.println("Scanning connected I2C...");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Scanning Finished\n");

    delay(5000);           // wait 5 seconds for next scan
}
