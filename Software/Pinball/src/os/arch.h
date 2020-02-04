// Architecture related defs / implementations
// Created by Scott Zhao on 2020-02-02.
//

#ifndef PINBALL_ARCH_H
#define PINBALL_ARCH_H

#include <Arduino.h>

#define SERIAL_SETUP(baudRate)  Serial.begin(baudRate)
#define PRINT_LINE              Serial.print(__FILE__);Serial.print(":");Serial.print(__LINE__);Serial.print(" ");
#define PRINT_MILLIS            Serial.print("[");Serial.print(millis(),8);Serial.print("] ");
#define LOG(param)              PRINT_MILLIS PRINT_LINE Serial.println(param)
#define LOGERROR(param)         Serial.print("[ERROR]@"); LOG(param)
#define PRINT(msg)              Serial.print(msg)

// NOTE: Doing millis() with Serial.printf on thread will cause thread error, and halts thread
//#define SERIAL_SOFTWARE_VER()   LOG("compiled on %s %s, gcc %d.%d.%d", __DATE__, __TIME__, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
//#define LOG(fmt, ...)           Serial.printf("[%8lu]  " __BASE_FILE__ ":%u " fmt "\n", millis(), __LINE__, ##__VA_ARGS__)
//#define LOGERROR(fmt, ...)      Serial.printf("[ERROR]\t[%8lu]\t" __BASE_FILE__ ":%u " fmt "\n", millis(), __LINE__, ##__VA_ARGS__)

// All Arduino Core
extern int main();
void setup();
void loop();

// IRQ Pin Defs
const uint8_t IOEXP_A_IRQ = 0;
const uint8_t IOEXP_B_IRQ = 1;

//void __attribute__((__noreturn__)) os_panic(void) {
//    LOGERROR("Panic handler called from 0x%08x !!!", __builtin_return_address(0));
//    while (true) {
//        asm("nop");
//    }
//}

#endif //PINBALL_ARCH_H
