//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_IOEXP_H
#define PINBALL_IOEXP_H

#include <os/interface.h>
#include <Adafruit_MCP23017.h>

class DIO {
public:
    DIO() = default;

    // NOTE: his function should be called in init only once. Doesn't take care of interrupt / Wire locks
    void init() {
        LOG("Initializing IO Expander");
        pinMode(IRQ, INPUT_PULLUP);
        mcp.begin();
        configureTb();
        reset1();
    }

    void init2() {
        LOG("Initializing IO Expander");
        pinMode(IRQ, INPUT_PULLUP);
        mcp.begin(1);
        reset2();
        initLED();
    }
//    void init2() {
//        LOG("Initializing IO Expander with Addr");
//        mcp.begin(1);
//        configureLED();
//        reset2();
//    }
    // NOTE: After this called, immediately ISR may be executed
    void initIRQ() {
        mcp.setupInterrupts(true, false, LOW);  // Mirror AB, Not OpenDrain, INTA/B Goes Low when Interrupt
        // TODO: Add more IR definitions
        configureIRGate(IOEXP_SOLENOID_PIN);
        configureIRGate(IOEXP_TOP_L_PIN);
        configureIRGate(IOEXP_TOP_R_PIN);
        configureIRGate(IOEXP_SLIDE_PIN);
        configureIRGate(IOEXP_GAMEOVER_PIN);
        attachInterrupt(IRQ, IOISR, FALLING);  // Put at the very last because ISR may be executed any time from now
    }

    void initLED() {
        mcp.pinMode(0, OUTPUT);
        mcp.pinMode(1, OUTPUT);
        mcp.pinMode(2, OUTPUT);
        mcp.pinMode(3, OUTPUT);
        mcp.pinMode(6, OUTPUT);
        mcp.pinMode(7, OUTPUT);
    }

    void configureTb() {
        mcp.pinMode(0, OUTPUT);
        mcp.pinMode(1, OUTPUT);
        mcp.pinMode(2, OUTPUT);
        mcp.pinMode(3, OUTPUT);
        mcp.pinMode(6, OUTPUT);
        mcp.pinMode(7, OUTPUT);
        // 6, 7 for solenoid
        write(6, LOW);
        write(7, HIGH);
    }

//    void configureLED() {
//        mcp.pinMode(0, OUTPUT);
//        mcp.pinMode(1, OUTPUT);
//        mcp.pinMode(2, OUTPUT);
//        mcp.pinMode(3, OUTPUT);
//        mcp.pinMode(4, OUTPUT);
//        mcp.pinMode(5, OUTPUT);
//        mcp.pinMode(6, OUTPUT);
//        mcp.pinMode(7, OUTPUT);
//    }

    void setTBDirection(bool cw) {
        if(cw) {
            write(0, LOW);
            write(1, HIGH);
            write(2, LOW);
            write(3, HIGH);
        }
        else {
            write(0, HIGH);
            write(1, LOW);
            write(2, HIGH);
            write(3, LOW);
        }
    }
    void configureIRGate(uint8_t p) {
        mcp.pinMode(p, INPUT);
        mcp.pullUp(p, LOW);  // turn on a 100K pulldown internally
        mcp.setupInterruptPin(p, RISING);
        if(read(p) != 0) {
            vErr("IR Gate Blocked at init @ pin=" + String(p));
        }
    }

    void reset1() {
        digitalWrite(9, LOW);
        dly(200);
        digitalWrite(9, HIGH);
    }

    void reset2() {
        digitalWrite(10, LOW);
        dly(200);
        digitalWrite(10, HIGH);
    }

    uint8_t read(uint8_t p) {
        // TODO: Assert pin defined and init'd
        return mcp.digitalRead(p);
    }

    void write(uint8_t p, uint8_t d) {
        // TODO: Assert pin defined and init'd
        mcp.digitalWrite(p, d);
    }

    uint16_t readInterruptPin() {
        // Returns interrupt pin and value
        // NOTE: Caller has responsibility to lock wire
        uint16_t pinval = mcp.getLastInterruptPin();
        pinval <<= 8;
        pinval |= mcp.getLastInterruptPinValue();
        return pinval;
    }

    inline void clearInterrupt() {
        // NOTE: Caller don't worry about locking
        // NOTE: To be safe, periodically call this to clear potential stuck due to non-cleared interrupt
//        wireLock();
#if DEBUG == 1
        uint8_t pin = mcp.getLastInterruptPin();
        if (pin != 255u) {
            uint8_t val = mcp.getLastInterruptPinValue();
            LOGWARNINGA("Manually Cleared an existing Interrupt@");
            PRINT(pin);
            PRINT(":");
            PRINTLN(val);
        }
#else
        mcp.getLastInterruptPinValue();
#endif
//        wireUnlock();
    }

protected:
    Adafruit_MCP23017 mcp;
};

#endif //PINBALL_IOEXP_H