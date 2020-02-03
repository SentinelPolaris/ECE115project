// All Interrupt related defs / implementations
// Created by Scott Zhao on 2020-02-03.
//
#include "interrupt.h"

void io0isr() {}

void io1isr() {}

void setupIOIRQ() {
    pinMode(IOEXP_A_IRQ, INPUT);
    pinMode(IOEXP_B_IRQ, INPUT);
    attachInterrupt(IOEXP_A_IRQ, io0isr, RISING);
    attachInterrupt(IOEXP_B_IRQ, io1isr, RISING);
}
