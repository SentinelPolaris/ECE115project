//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_IOEXP_H
#define PINBALL_IOEXP_H

#include <os/interface.h>
#include <Adafruit_MCP23017.h>

class DIO {
public:
    DIO() {
        wireLock();  // Locks wire interface
        pinMode(IRQ, INPUT);
        attachInterrupt(IRQ, IOISR, FALLING);
        mcp.begin();
        mcp.setupInterrupts(true, false, LOW);  // Mirror AB, Not OpenDrain, INTA/B Goes Low when Interrupt

        mcp.pinMode(7, INPUT);
        mcp.pullUp(7, HIGH);  // turn on a 100K pullup internally
        mcp.setupInterruptPin(7, RISING);
        wireUnlock();
        reset();
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