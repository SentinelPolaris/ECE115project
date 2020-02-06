//
// Created by Scott Zhao on 2020-02-04.
//
#ifndef PINBALL_TESTDC_H
#define PINBALL_TESTDC_H
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "peri/pwm.h"

void testDC() {
    PWM testPWM;
    while (true) {
        for (uint8_t ii = 0; ii < 100; ii++) {
            testPWM.set(0, ii);
            dly(50);
        }
    }
}

#endif //PINBALL_TESTDC_H
