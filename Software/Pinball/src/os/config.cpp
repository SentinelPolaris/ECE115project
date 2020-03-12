//
// Created by Scott Zhao on 2020-02-28.
//
#include "os/arch.h"

// IR Pin -> Wave file LUT
char IR2WAV[IR_TRG_PINS_AMOUNT] = {
        0,  // 0 Not Used
        0,  // 1 Not Used
        0,  // 2 Not Used
        0,  // 3 Not Used
        0,  // 4 Not Used
        0,  // 5 Not Used
        0,  // 6 Not Used
        0,  // 7 Not Used
        1,  // 8 Solenoid
        3,  // 9 Top Left
        2,  // 10 Top Right
        4,  // 11 Slide
        0,  // 12 Game over
};