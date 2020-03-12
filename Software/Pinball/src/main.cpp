//
// Created by Scott Zhao on 2020-01-30.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/peri.h"

TaskHandle_t xHeartBeatTask = NULL, xIOTask = NULL, xIOUnstuckTask = NULL, xWheelTask = NULL, xSolenoidTask = NULL,
                xScoreTask = NULL, xSpeakerTask = NULL;

TaskHandle_t xPingTestTask = NULL, xPongTestTask = NULL, xTestISRTask = NULL;
xQueueHandle IREventQueue = NULL;
xQueueHandle testQueue = NULL;
xQueueHandle speakerQueue = NULL;
xQueueHandle solenoidQueue = NULL;
extern void vHeartBeatTask(void *arg);
extern void vIOUnstuckTask(void *arg);
extern void vWheelTask(void *arg);
extern void vIOTask(void *arg);

extern void vSolenoidTask(void *arg);
extern void vScoreTask(void *arg);
extern void vSpeakerTask(void *arg);

extern void vPingTestTask(void *arg);
extern void vPongTestTask(void *arg);
extern void vTestISRTask(void *arg);

peri teensyperi;

int main() {
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    // MCU init
    Serial.begin(115200);
    RGB_PANEL.begin(9600);
    ESP.begin(9600);
    SPEAKER_TEENSY.begin(9600);
    // Wait for USB set up
    delay(2000);
    LOG("System initializing...");
    i2cCheck();
    teensyperi.ioexp.init();
    teensyperi.ioexp2.init2();
    teensyperi.motor.init();


    // FREERTOS tasks
    IREventQueue = xQueueCreate(20, sizeof(uint8_t));
    testQueue = xQueueCreate(20, sizeof(uint8_t));
    speakerQueue = xQueueCreate(20, sizeof(uint8_t));
    solenoidQueue = xQueueCreate(20, sizeof(uint8_t));

    portBASE_TYPE s1, s2, s3, s4, s5, s6, s7;
    s1 = xTaskCreate(vHeartBeatTask, "HeartBeat",          1024, NULL,                   0, &xHeartBeatTask);
    s2 = xTaskCreate(vIOUnstuckTask, "IOGuard",            1024, (void *) &teensyperi,   0, &xIOUnstuckTask);
    s3 = xTaskCreate(vWheelTask,     "DCMotor",            1024, (void *) &teensyperi,   1, &xWheelTask);
    s4 = xTaskCreate(vIOTask,        "IOIntr",             1024, (void *) &teensyperi,   3, &xIOTask);
    s5 = xTaskCreate(vSolenoidTask,  "SoleCtrl",           1024, (void *) &teensyperi,   4, &xSolenoidTask);
    s6 = xTaskCreate(vScoreTask,     "Score",              1024, (void *) &teensyperi,   2, &xScoreTask);
    s7 = xTaskCreate(vSpeakerTask,   "Speaker",            1024, (void *) &teensyperi,   2, &xSpeakerTask);

    // Tests
    xTaskCreate(vPingTestTask, "PingTest", 512, (void *) &teensyperi, 0, &xPingTestTask);
//    xTaskCreate(vPongTestTask, "PongTest", 512, NULL, 0, &xPongTestTask);
//    xTaskCreate(vTestISRTask, "ISRTest", 512, (void *) &teensyperi, 0, &xTestISRTask);

    // Check for creation errors
    if (s1 != pdPASS || s2 != pdPASS || s3 != pdPASS || s4 != pdPASS || s5 != pdPASS || s6 != pdPASS ||
        s7 != pdPASS) {
        LOGERROR("Tasks creation error!");
    }
    LOG("Starting the scheduler!");
    vTaskStartScheduler();

    // Should not reach here
    LOGERROR("Insufficient RAM");
}