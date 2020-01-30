//
// Created by Scott Zhao on 2020-01-30.
//

#include <Arduino.h>
#include <TeensyThreads.h>
#include "flags.hpp"

void iothread();

void ioTriggeredCb();

void setup() {
    threads.addThread(iothread);
}

void loop()

}

void iothread() {
    while (WIRE_CURRENTLY_USED) {
        threads.yield();
    }
    while (1) {
        WIRE_CURRENTLY_USED = true;
        ioTriggeredCb();
        WIRE_CURRENTLY_USED = false;
    }
}