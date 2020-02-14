//
// Created by Scott Zhao on 2020-02-06.
//
#include "flags.h"

volatile uint32_t __timer_temp = 0;
volatile bool SERIAL_SET_UP = false;
volatile bool WIRE_DEFINED_FLAG = false;
volatile bool WIRE_CURRENTLY_USED = false;
volatile bool IO_IRQ_WAITING = false;

void IOISR() {
#if DEBUG == 1
    if (IO_IRQ_WAITING) {
        LOGWARNING("IO IRQ Skipped! IRQ triggered without previous flag handled!");
    }
#endif
    IO_IRQ_WAITING = true;
}