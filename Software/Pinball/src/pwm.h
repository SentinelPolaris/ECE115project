//
// Created by Scott Zhao on 2020-01-30.
//

#ifndef PINBALL_PWM_H
#define PINBALL_PWM_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <os/interface.h>

class PWM {
public:
    PWM() {
        wireStart();  // Locks wire interface
        pwm.begin();
        pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
        pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
        Wire.setClock(400000);
        wireEnd();
    }

    void set(uint8_t port, uint8_t dutyCycle) {
        uint16_t endTime = (4095 * dutyCycle) / 100;
        wireStart();
        pwm.setPWM(port, 0, endTime);
        wireEnd();
    }

protected:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
};

#endif //PINBALL_PWM_H