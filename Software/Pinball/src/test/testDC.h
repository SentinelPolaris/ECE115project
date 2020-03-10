//
// Created by Scott Zhao on 2020-02-04.
//
#ifndef PINBALL_TESTDC_H
#define PINBALL_TESTDC_H
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include <peri/ioexp.h>
#include <peri/pwm.h>

void testDC() {
    DIO ioexp;
    PWM testPWM;
    testPWM.set(0, 100);
    testPWM.set(1, 100);
    while (true) {
        dly(2000);
        ioexp.setTBDirection(true);
        dly(2000);
        ioexp.setTBDirection(false);
    }
}

#endif //PINBALL_TESTDC_H
