//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_FLAGS_H
#define PINBALL_FLAGS_H

#include "arch.h"

volatile uint32_t __timer_temp = 0;
volatile bool SERIAL_SET_UP = false;
volatile bool WIRE_DEFINED_FLAG = false;
volatile bool WIRE_CURRENTLY_USED = false;
volatile bool IO_IRQ_WAITING = false;

void wireLock() {
    // TODO: Implement timeout warnings
    while (WIRE_CURRENTLY_USED) { yd(); }
    WIRE_CURRENTLY_USED = true;
}

void wireUnlock() {
    // TODO: Assert true
    WIRE_CURRENTLY_USED = false;
}

#endif //PINBALL_FLAGS_H
