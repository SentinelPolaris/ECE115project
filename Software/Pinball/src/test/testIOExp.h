//
// Created by Scott Zhao on 2020-02-06.
//

#ifndef PINBALL_TESTIOEXP_H
#define PINBALL_TESTIOEXP_H
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "../peri/ioexp.h"

void testIOInterrupt() {
    DIO ioTester;
    uint32_t IRQCount = 0;
    uint32_t testTimer = millis();
    while (true) {
        if (IO_IRQ_WAITING) {
            ioTester.IOIRQHandler();
            IRQCount++;
        }
        if (millis() - testTimer > 500) {
            LOG(IRQCount);
            testTimer = millis();
            ioTester.clearInterrupt();
        }
    }
}

#endif //PINBALL_TESTIOEXP_H
