//
// Created by Scott Zhao on 2020-02-04.
//

#ifndef PINBALL_IO_H
#define PINBALL_IO_H

#include "os/arch.h"
#include "os/interface.h"
class io {
    io() {  // ctor sets up all interface / peripheral
        serialInit();
//        ioexpInit();
//        pwmInit();
    }
};


#endif //PINBALL_IO_H
