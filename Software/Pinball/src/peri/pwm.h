//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_PWM_H
#define PINBALL_PWM_H

#include <os/interface.h>
#include <Adafruit_PWMServoDriver.h>

class PWM {
public:
    PWM() {
        wireLock();  // Locks wire interface
        pwm.begin();  // NOTE: Assume default I2C bus on platform
        pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
        pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
        wireUnlock();
        stop();
    }

    void stop() {
        wireLock();
        for(uint8_t index = 0; index < 16; index++) {
            pwm.setPWM(index, 0, 0);
        }
        wireUnlock();
    }

    void set(uint8_t port, uint8_t dutyCycle) {
        uint16_t endTime = (4095 * dutyCycle) / 100;
        wireLock();
        pwm.setPWM(port, 0, endTime);
        LOG("Set");
        wireUnlock();
        LOG("Done");
    }

protected:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
};

#endif //PINBALL_PWM_H