//
// Created by Scott Zhao on 2020-02-03.
//
#include "arch.h"

void setup() {}

void loop() {
    main();
    while (true) { asm("nop"); }
}
