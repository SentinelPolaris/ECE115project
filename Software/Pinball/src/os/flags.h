//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_FLAGS_H
#define PINBALL_FLAGS_H

#include "arch.h"

extern volatile uint32_t __timer_temp;
extern volatile bool SERIAL_SET_UP;
extern volatile bool WIRE_DEFINED_FLAG;
extern volatile bool WIRE_CURRENTLY_USED;
extern volatile bool IO_IRQ_WAITING;

extern void IOISR();

inline void wireLock() {
    // TODO: Implement timeout warnings
    while (WIRE_CURRENTLY_USED) { yd(); }
    WIRE_CURRENTLY_USED = true;
}

inline void wireUnlock() {
    // TODO: Assert true
    WIRE_CURRENTLY_USED = false;
}

#endif //PINBALL_FLAGS_H
