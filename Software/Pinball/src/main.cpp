//
// Created by Scott Zhao on 2020-01-30.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "os/thread.h"
#include "os/interrupt.h"
#include "os/flags.h"
#include "pwm.h"

volatile int threadID;

int main() {
    SERIAL_SETUP(115200);
    threadID = threads.addThread(serialCommander);
    PWM pwmTest;

    while (true) {
        LOG(threads.getState(threadID));
        threads.delay(200);
        pwmTest.set(0, 10);
    }
}