//
// Created by Scott Zhao on 2020-02-04.
//
#include "peri/pwm.h"

#ifndef PINBALL_TESTDC_H
#define PINBALL_TESTDC_H

void testDC() {
    PWM testPWM;
    for (uint8_t ii = 0; ii < 100; ii++) {
        testPWM.set(0, ii);
        dly(50);
    }
}

#endif //PINBALL_TESTDC_H
