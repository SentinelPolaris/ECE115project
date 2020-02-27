//
// Created by Scott Zhao on 2020-02-06.
//
#include "interface.h"

void serialInit() {
    if (!SERIAL_SET_UP) {
        Serial.begin(115200);
    } else {
        LOGWARNING("Duplicated serialInit invoked! Ignored.");
    }
}
