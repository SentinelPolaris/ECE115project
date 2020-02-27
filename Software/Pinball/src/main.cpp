//
// Created by Scott Zhao on 2020-01-30.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/peri.h"

TaskHandle_t xHeartBeatTask = NULL, xIOTask = NULL, xIOUnstuckTask = NULL, xWheelTask = NULL, xSolenoidTask = NULL,
                xScoreTask = NULL, xSpeakerTask = NULL;

TaskHandle_t xPingTestTask = NULL, xPongTestTask = NULL;
xQueueHandle IREventQueue = NULL;
xQueueHandle testQueue = NULL;

extern void vHeartBeatTask(void *arg);
extern void vIOUnstuckTask(void *arg);
extern void vWheelTask(void *arg);
extern void vIOTask(void *arg);

//extern void vSolenoidTask(void *arg);
//extern void vScoreTask(void *arg);
//extern void vSpeakerTask(void *arg);

extern void vPingTestTask(void *arg);
extern void vPongTestTask(void *arg);

peri teensyperi;

int main() {
    // MCU init
    serialInit();
    teensyperi.ioexp.init();
    teensyperi.motor.init();
    teensyperi.speaker.init();

    // FREERTOS tasks
    IREventQueue = xQueueCreate(20, sizeof(uint8_t));
    testQueue = xQueueCreate(20, sizeof(uint8_t));

    portBASE_TYPE s1, s2, s3, s4, s5, s6, s7;
    s1 = xTaskCreate(vHeartBeatTask, "HeartBeat",          1024, NULL,              0, &xHeartBeatTask);
    s2 = xTaskCreate(vIOUnstuckTask, "IOGuard",            1024, (void *) &teensyperi,   0, &xIOUnstuckTask);
    s3 = xTaskCreate(vWheelTask,     "DCMotor",            1024, (void *) &teensyperi,   1, &xWheelTask);
//    s4 = xTaskCreate(vIOTask,        "IOIntr",             1024, (void *) &teensyperi,   3, &xIOTask);
//    s5 = xTaskCreate(vSolenoidTask,  "SoleCtrl",           1024, (void *) &teensyperi,   2, &xSolenoidTask);
//    s6 = xTaskCreate(vScoreTask,     "Score",              1024, NULL,                   2, &xScoreTask);
//    s7 = xTaskCreate(vSpeakerTask,   "Speaker",            1024, (void *) &teensyperi,   2, &xSpeakerTask);
    xTaskCreate(vPingTestTask, "PingTest", 512, NULL, 0, &xPingTestTask);
    xTaskCreate(vPongTestTask, "PongTest", 512, NULL, 0, &xPongTestTask);

    // Check for creation errors
    if (s1 != pdPASS || s2 != pdPASS || s3 != pdPASS){// || s4 != pdPASS) || s5 != pdPASS || s6 != pdPASS ||
//        s7 != pdPASS) {
        LOGERROR("Tasks creation error!");
    }
    LOG("Starting the scheduler!");
    vTaskStartScheduler();

    // Should not reach here
    LOGERROR("Insufficient RAM");
}