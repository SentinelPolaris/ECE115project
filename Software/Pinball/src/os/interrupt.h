//
// Created by Scott Zhao on 2020-02-03.
//

#ifndef PINBALL_INTERRUPT_H
#define PINBALL_INTERRUPT_H

#include "arch.h"
void io0isr();
void io1isr();
void setupIOIRQ();

#endif //PINBALL_INTERRUPT_H
