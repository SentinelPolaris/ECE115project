//
// Created by Scott Zhao on 2020-02-27.
//

#ifndef PINBALL_PERI_H
#define PINBALL_PERI_H
#include "ioexp.h"
#include "pwm.h"
#include "Audio.h"

typedef struct {
    DIO ioexp;
    PWM motor;
    Audio speaker;
}peri;

#endif //PINBALL_PERI_H
