// Configuration Macros
// Created by Scott Zhao on 2020-02-06.
//

#ifndef PINBALL_CONFIG_H
#define PINBALL_CONFIG_H
#define DEBUG 1
#define IOIRQ_SW_DEBOUNCE 1 // See note in ioexp.h
#define IOIRQ_SW_DEBOUNCE_MS 50 // This significantly limits IRQ maximum no-lose-frequency
#define WIRE_LOCK_TIMEOUT_MS 50
#define IR_TRG_PINS_AMOUNT 3
#define RGB_PANEL Serial1
#define ESP Serial2
#define SPEAKER_TEENSY Serial4


extern char IR2WAV[IR_TRG_PINS_AMOUNT];
extern uint32_t IR2SCORE[IR_TRG_PINS_AMOUNT];
#endif //PINBALL_CONFIG_H
