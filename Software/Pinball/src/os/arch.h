// Architecture related defs / implementations
// Created by Scott Zhao on 2020-02-02.
//

#ifndef PINBALL_ARCH_H
#define PINBALL_ARCH_H

#include <Arduino.h>
//#include <TeensyThreads.h>
#include <FreeRTOS_TEENSY4.h>
#include <Wire.h>
#include "config.h"

// Handy macros
// do{..multiline statement}while(0) is a hack to make sure this works as single statement
// for example below an if without {}

#define LOGGER                  Serial
#define PRINT_LINE              LOGGER.print(__FILE__);LOGGER.print(":");LOGGER.print(__LINE__);LOGGER.print(" ");
#define PRINT_MILLIS            LOGGER.print("[");LOGGER.print(millis());LOGGER.print("] ");
#define LOG(param)              do{PRINT_MILLIS PRINT_LINE LOGGER.println(param);}while(0)
#define LOGA(param)             do{PRINT_MILLIS PRINT_LINE LOGGER.print(param);}while(0)
#define LOGERROR(param)         do{LOGGER.print("[ERROR]@"); LOG(param);}while(0)
#define LOGWARNING(param)       do{LOGGER.print("[WARN]@"); LOG(param);}while(0)
#define LOGWARNINGA(param)      do{LOGGER.print("[WARN]@"); LOGA(param);}while(0)
#define PRINT(msg)              LOGGER.print(msg)
#define PRINTLN(msg)            LOGGER.println(msg)
#define TIMER_START             __timer_temp = micros();
#define TIMER_END               LOG(micros() - __timer_temp);

#if DEBUG==1
#define ASSERT_FATAL(cond, msg) do{if(!cond){LOGERROR(msg);}}while(0)
#define ASSERT_WARN(cond, msg)  do{if(!cond){LOGWARNING(msg);}}while(0)
#else
#define ASSERT_FATAL(cond, msg) do{}while(0)  // Do nothing for assert
#define ASSERT_WARN(cond, msg)  do{}while(0)  // Do nothing for assert
#endif

// NOTE: Doing millis() with Serial.printf on thread will cause thread error, and halts thread
//#define SERIAL_SOFTWARE_VER()   LOG("compiled on %s %s, gcc %d.%d.%d", __DATE__, __TIME__, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
//#define LOG(fmt, ...)           Serial.printf("[%8lu]  " __BASE_FILE__ ":%u " fmt "\n", millis(), __LINE__, ##__VA_ARGS__)
//#define LOGERROR(fmt, ...)      Serial.printf("[ERROR]\t[%8lu]\t" __BASE_FILE__ ":%u " fmt "\n", millis(), __LINE__, ##__VA_ARGS__)

// All Arduino Core
extern int main();

void setup();

void loop();

// IRQ Pin Defs
extern const uint8_t IRQ;

// Arch Implement Specific Delays / Yields
// MCU Arch Delay
inline void dly(uint32_t ms) {
    delay(ms);
}
// RTOS Delay
inline void vDelay(uint32_t ms) {
    vTaskDelay((ms * configTICK_RATE_HZ) / 1000L);
}
// RTOS Yield (force switching context)
inline void vYield() {
    portYIELD()
}

// Convert ms to system ticks
inline portTickType ms(uint32_t ms) {
    return ((ms * configTICK_RATE_HZ) / 1000L);
}


//void __attribute__((__noreturn__)) os_panic(void) {
//    LOGERROR("Panic handler called from 0x%08x !!!", __builtin_return_address(0));
//    while (true) {
//        asm("nop");
//    }
//}

#endif //PINBALL_ARCH_H
