//
// Created by Scott Zhao on 2020-02-28.
//
#include "os/arch.h"

// IR Pin -> Wave file LUT
char IR2WAV[IR_TRG_PINS_AMOUNT] = {0, 1, 2};
// IR Pin -> Increase score LUT
uint32_t IR2SCORE[IR_TRG_PINS_AMOUNT] = {5, 10, 15};