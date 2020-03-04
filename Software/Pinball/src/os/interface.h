//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_INTERFACE_H
#define PINBALL_INTERFACE_H

#include "arch.h"

extern volatile uint32_t __timer_temp;
extern volatile bool SERIAL_SET_UP;
extern volatile bool WIRE_DEFINED_FLAG;
extern volatile bool WIRE_CURRENTLY_USED;
extern volatile bool IO_IRQ_WAITING;

extern void IOISR();

inline void wireLock() {
    taskENTER_CRITICAL();
//#if DEBUG==1
//    uint32_t wireLockWait = millis();
//#endif
//    while (WIRE_CURRENTLY_USED) {
//        ASSERT_WARN(wireLockWait - millis() < WIRE_LOCK_TIMEOUT_MS, "Wire Lock Is Taking Too Long!");
//        vYield();
//    }
//    WIRE_CURRENTLY_USED = true;
}

inline void wireUnlock() {
    taskEXIT_CRITICAL();
//    ASSERT_FATAL(WIRE_CURRENTLY_USED, "Attempting to unlock an already unlocked wire bus!");
//    WIRE_CURRENTLY_USED = false;
}

#endif //PINBALL_INTERFACE_H
