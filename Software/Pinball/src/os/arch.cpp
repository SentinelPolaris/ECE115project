//
// Created by Scott Zhao on 2020-02-03.
//
#include "arch.h"

void setup() {
    dly(500);  // NOTE: USB Terminal doesn't work if enabled at the beginning of bootup
}

void loop() {
    main();
    while (true) { asm("nop"); }
}
