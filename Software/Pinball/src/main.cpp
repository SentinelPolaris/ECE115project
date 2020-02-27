//
// Created by Scott Zhao on 2020-01-30.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/ioexp.h"
#include "peri/pwm.h"
#include "peri/Audio.h"

SemaphoreHandle_t sem;
TaskHandle_t xHeartBeatTask = NULL, xIOTask = NULL, xIOUnstuckTask = NULL, xWheelTask = NULL, xSolenoidTask = NULL,
                xScoreTask = NULL, xSpeakerTask = NULL;

extern void vHeartBeatTask(void *arg);
extern void vIOUnstuckTask(void *arg);
extern void vWheelTask(void *arg);
extern void vIOTask(void *arg);

//extern void vSolenoidTask(void *arg);
//extern void vScoreTask(void *arg);
//extern void vSpeakerTask(void *arg);


DIO ioexp;
PWM motor;
Audio speaker;

int main() {
    // MCU inits
    serialInit();
    ioexp.init();
    motor.init();
    speaker.init();

    // FREERTOS tasks
    portBASE_TYPE s1, s2, s3, s4, s5, s6, s7;
    s1 = xTaskCreate(vHeartBeatTask, "HeartBeat",          1024, NULL,              0, &xHeartBeatTask);
    s2 = xTaskCreate(vIOUnstuckTask, "IOGuard",            1024, (void *) &ioexp,   0, &xIOUnstuckTask);
//    s3 = xTaskCreate(vWheelTask,     "DCMotor",            1024, (void *) &motor,   1, &xWheelTask);
//    s4 = xTaskCreate(vIOTask,        "IOEXP",              1024, (void *) &ioexp,   3, &xIOTask);
//    s5 = xTaskCreate(vSolenoidTask,  "SolenoidController", 1024, (void *) &motor,   2, &xSolenoidTask);
//    s6 = xTaskCreate(vScoreTask,     "Score",              1024, NULL,              2, &xScoreTask);
//    s7 = xTaskCreate(vSpeakerTask,   "Speaker",            1024, (void *) &speaker, 2, &xSpeakerTask);

    // Check for creation errors
    if (sem == NULL || s1 != pdPASS || s2 != pdPASS){// || s3 != pdPASS || s4 != pdPASS) || s5 != pdPASS || s6 != pdPASS ||
//        s7 != pdPASS) {
        LOGERROR("Tasks creation error!");
    }
    LOG("Starting the scheduler !");
    vTaskStartScheduler();

    // Should not reach here
    LOGERROR("Insufficient RAM");
}