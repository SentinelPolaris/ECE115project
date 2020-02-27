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
//        mcp.setupInterrupts(true, false, LOW);  // Mirror AB, Not OpenDrain, INTA/B Goes Low when Interrupt
//        configureIRGate(0);
        attachInterrupt(IRQ, IOISR, FALLING);  // Put at the very last because ISR may be executed any time from now
    }

    void configureTb() {
        mcp.pinMode(4, OUTPUT);
        mcp.pinMode(5, OUTPUT);
        mcp.pinMode(6, OUTPUT);
        mcp.pinMode(7, OUTPUT);
    }

    void setTBDirection(bool cw) {
        if(cw) {
            write(4, LOW);
            write(5, HIGH);
            write(6, LOW);
            write(7, HIGH);
        }
        else {
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
            LOGWARNING("Manually Cleared an existing Interrupt@");
            PRINT(pin);
            PRINT(":");
            PRINTLN(val);
        }
#else
        mcp.getLastInterruptPinValue();
#endif
        wireUnlock();
    }

    uint16_t IOIRQHandler() {
        // NOTE: Caller don't worry about locking
        uint16_t irqInfo;
        uint8_t irqPin, irqVal;
        wireLock();
        irqInfo = readInterruptPin();
        irqVal = (irqInfo & 0xFFu); // Lower 8 bit is value
        irqPin = (irqInfo >> 8u);   // Upper 8 bit is pin
#if IOIRQ_SW_DEBOUNCE == 1
        dly(IOIRQ_SW_DEBOUNCE_MS);  // CRITICAL: Debounce (used to compensate bounce back after IRQ goes back)
#endif
        // CRITICAL: Wait for interrupt signal to go back (so IRQ goes back again)
        // Since IRQ will follow interrupt signal for MCP23017
        while (read(irqPin) == irqVal) { yd(); }
#if IOIRQ_SW_DEBOUNCE == 1
        dly(IOIRQ_SW_DEBOUNCE_MS);  // CRITICAL: Debounce (used to compensate bounce back after IRQ goes back)
#endif
        IO_IRQ_WAITING = false;
        wireUnlock();
        return irqInfo;
    }

protected:
    Adafruit_MCP23017 mcp;
};

#endif //PINBALL_IOEXP_H