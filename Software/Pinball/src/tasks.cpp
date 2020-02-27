//
// Created by Scott Zhao on 2020-02-26.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/peri.h"

extern xQueueHandle IREventQueue;
extern xQueueHandle testQueue;

void get_task_state() {
    // Credit: https://blog.csdn.net/zhzht19861011/article/details/50717549?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task
#define MAX_TASK_NUM 30
    const char task_state[] = {'r', 'R', 'B', 'S', 'D'};
    volatile UBaseType_t uxArraySize, x;
    uint32_t ulTotalRunTime, ulStatsAsPercentage;
    TaskStatus_t pxTaskStatusArray[MAX_TASK_NUM];

/* 获取任务总数目 */
    uxArraySize = uxTaskGetNumberOfTasks();
    if (uxArraySize > MAX_TASK_NUM) {
        LOGWARNING("TOO MUCH TASKS！\n");
    }

/*获取每个任务的状态信息 */
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
    LOG("\n\n------------------Task Report -----------------------");
    PRINTLN("TaskName\tStatus\tID\tPriority\tStack\tCPU Usage");
    /* 避免除零错误 */
    if(ulTotalRunTime <= 0)
        ulTotalRunTime = 1;
    if( ulTotalRunTime > 0 )
    {
        /* 将获得的每一个任务状态信息部分的转化为程序员容易识别的字符串格式 */
        for( x = 0; x < uxArraySize; x++ )
        {
            char tmp[128];

            /* 计算任务运行时间与总运行时间的百分比。*/
            ulStatsAsPercentage =(uint64_t)(pxTaskStatusArray[ x ].ulRunTimeCounter)*100 / ulTotalRunTime;

            if( ulStatsAsPercentage > 0UL )
            {

                sprintf(tmp,"%-20s\t%-1c\t%-6d\t%-8d\t%-8d\t%d%%",pxTaskStatusArray[ x].pcTaskName,task_state[pxTaskStatusArray[ x ].eCurrentState],
                        pxTaskStatusArray[ x ].xTaskNumber,pxTaskStatusArray[ x].uxCurrentPriority,
                        pxTaskStatusArray[ x ].usStackHighWaterMark,ulStatsAsPercentage);
            }
            else
            {
                /* 任务运行时间不足总运行时间的1%*/
                sprintf(tmp,"%-20s\t%-1c\t%-6d\t%-8d\t%-8d\tt<1%%",pxTaskStatusArray[x ].pcTaskName,task_state[pxTaskStatusArray[ x ].eCurrentState],
                        pxTaskStatusArray[ x ].xTaskNumber,pxTaskStatusArray[ x].uxCurrentPriority,
                        pxTaskStatusArray[ x ].usStackHighWaterMark);
            }
            PRINTLN(tmp);
        }
    }
    PRINTLN("\nTask Status:   r-Running  R-Ready  B-Block  S-Suspend  D-Deleted");
}

void vHeartBeatTask(void *arg) {
//    char buf[200];
    for(;;) {
        get_task_state();
//        // vTaskGetRunTimeStats kinda broken
//        // https://www.freertos.org/rtos-run-time-stats.html
//        // https://github.com/discord-intech/FreeRTOS-Teensy4/issues/3
//        vTaskGetRunTimeStats(buf);
//        LOG(buf);
        dly(5000);
    }
}

void vIOUnstuckTask(void* arg) {
    DIO ioexp = (*((peri *)arg)).ioexp;
    for(;;){
        ioexp.clearInterrupt();
        dly(500);
    }
}

void vIOTask(void* arg) {
    DIO ioexp = (*((peri *)arg)).ioexp;
    ioexp.initIRQ();  // NOTE: Delayed init interrupt here because ISR is only safe after this task has been started
    for(;;) {
        // Block task while waiting for notification from ISR.
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        uint16_t irqInfo = ioexp.IOIRQHandler();
        uint8_t irqVal = (irqInfo & 0xFFu); // Lower 8 bit is value
        uint8_t irqPin = (irqInfo >> 8u);   // Upper 8 bit is pin
        if(xQueueSend(IREventQueue, (void *)&irqPin, ms(1)) != pdPASS) {
            LOGWARNING("Failed to enqueue IRQ Pin. Full?");
        }
    }
}

void vWheelTask(void* arg) {
    PWM motor = (*((peri *)arg)).motor;
    DIO ioexp = (*((peri *)arg)).ioexp;
    for(;;) {
        ioexp.setTBDirection(true);
        dly(1000);
        ioexp.setTBDirection(false);
        dly(1000);
    }
}

void vScoreTask(void* arg) {
    uint8_t *irPin;
    for(;;) {
        if(xQueueReceive(IREventQueue, irPin, portMAX_DELAY)) {
            LOGA("ScoreTask Received from Queue:");
            PRINTLN(*irPin);
            // TODO: Talk to Arduino
        } else
            LOGWARNING("Time out receiving IRPin from Queue. This should not happen.");
    }
}
void vPingTestTask(void* arg) {
    uint8_t irqPin = 5;
    for(;;) {
        irqPin++;
        LOG("Sending on queue");
        if(xQueueSend(testQueue, (void *)&irqPin, ms(1)) != pdPASS) {
            LOGWARNING("Failed to enqueue IRQ Pin. Full?");
        }
        dly(200);
    }
}

void vPongTestTask(void* arg) {
    uint8_t *irPin;
    for(;;) {
        if(xQueueReceive(testQueue, irPin, portMAX_DELAY)) {
            LOGA("ScoreTask Received from Queue:");
            PRINTLN(*irPin);
            // TODO: Talk to Arduino
        } else
            LOGWARNING("Time out receiving IRPin from Queue. This should not happen.");
    }
}