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
        reset();
    }

    // NOTE: After this called, immediately ISR may be executed
    void initIRQ() {
        mcp.setupInterrupts(true, false, LOW);  // Mirror AB, Not OpenDrain, INTA/B Goes Low when Interrupt
        // TODO: Add more IR definitions
        configureIRGate(1);
        attachInterrupt(IRQ, IOISR, FALLING);  // Put at the very last because ISR may be executed any time from now
    }

    void configureTb() {
        mcp.pinMode(2, OUTPUT);
        mcp.pinMode(3, OUTPUT);
        mcp.pinMode(4, OUTPUT);
        mcp.pinMode(5, OUTPUT);
        mcp.pinMode(6, OUTPUT);
        mcp.pinMode(7, OUTPUT);
    }

    void setTBDirection(bool cw) {
        if(cw) {
            write(2, LOW);
            write(3, LOW);
            write(4, LOW);
            write(5, HIGH);
            write(6, LOW);
            write(7, HIGH);
        }
        else {
            write(2, HIGH);
            write(3, LOW);
            write(4, HIGH);
            write(5, LOW);
            write(6, HIGH);
            write(7, LOW);
        }
    }
    void configureIRGate(uint8_t p) {
        mcp.pinMode(p, INPUT);
        mcp.pullUp(p, LOW);  // turn on a 100K pulldown internally
        mcp.setupInterruptPin(p, RISING);
    }

    void reset() {
        // TODO: Resets IOEXP's reset pin
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
        wireLock();
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
        wireUnlock();
    }

protected:
    Adafruit_MCP23017 mcp;
};

#endif //PINBALL_IOEXP_H