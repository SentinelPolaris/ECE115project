//// Thread related defs / implementations
//// Created by Scott Zhao on 2020-02-03.
////
//
//#ifndef PINBALL_THREAD_H
//#define PINBALL_THREAD_H
//#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning
//
//#include "flags.h"
//#include "../pwm.h"
//
//void serialCommander() {
//    while (true) {
//        while (!Serial.available())
//            threads.yield();
//        LOG(Serial.available());
//        dly(200);  // FIXME: Not fully working - does not update
//    }
//}
//
//void PWMTestThread() {
//    PWM pwmTest;
//    dly(2000);
//    pwmTest.set(0, 100);
//}
//
//#endif //PINBALL_THREAD_H
