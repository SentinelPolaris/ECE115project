// Interface related defs / implementations
// Created by Scott Zhao on 2020-02-03.
//

#ifndef PINBALL_INTERFACE_H
#define PINBALL_INTERFACE_H

#include "flags.h"

void wireInit() {
    Wire.setClock(1000000);
}

void serialInit() {
    if (!SERIAL_SET_UP) {
        Serial.begin(115200);
    } else {
        LOGWARNING("Duplicated serialInit invoked! Ignored.");
    }
}

#endif //PINBALL_INTERFACE_H
