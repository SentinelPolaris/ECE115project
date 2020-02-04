// Interface related defs / implementations
// Created by Scott Zhao on 2020-02-03.
//

#ifndef PINBALL_INTERFACE_H
#define PINBALL_INTERFACE_H

#include "flags.h"
#include "thread.h"

void wireStart() {
    // TODO: Implement timeout warnings
    while(WIRE_CURRENTLY_USED) {threads.yield();}
    WIRE_CURRENTLY_USED = true;
}

void wireEnd() {
    // TODO: Assert true
    WIRE_CURRENTLY_USED = false;
}
#endif //PINBALL_INTERFACE_H
