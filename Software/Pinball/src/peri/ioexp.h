//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_PWM_H
#define PINBALL_PWM_H

#include <os/interface.h>
#include <Adafruit_MCP23017.h>

class DIO {
public:
    DIO() {
        wireLock();  // Locks wire interface
        pinMode(IRQ, INPUT);
        mcp.begin();
        mcp.setupInterrupts(true, false, LOW);

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

    void readInterruptPin() {
        uint8_t pin = mcp.getLastInterruptPin();
        uint8_t val = mcp.getLastInterruptPinValue();
    }
protected:
    Adafruit_MCP23017 mcp;
};

#endif //PINBALL_PWM_H