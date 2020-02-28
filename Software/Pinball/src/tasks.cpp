//
// Created by Scott Zhao on 2020-02-26.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/peri.h"

extern xQueueHandle IREventQueue;
extern xQueueHandle testQueue;
extern xQueueHandle speakerQueue;
extern xQueueHandle solenoidQueue;

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
        uint16_t irqInfo;
        uint8_t irqPin, irqVal;
        // FIXME: For now disabled critical section. Sometime freezes and that may be because of this
//        wireLock();
        irqInfo = ioexp.readInterruptPin();
        irqVal = (irqInfo & 0xFFu); // Lower 8 bit is value
        irqPin = (irqInfo >> 8u);   // Upper 8 bit is pin
        if(irqPin == 255) {
            LOGWARNING("Skipped 255 pin in IRQ Task!");
//            wireUnlock();
            continue;
        }
        // Send IRQ Pin right away, but still continue SW debounce process
        if(xQueueSend(IREventQueue, (void *)&irqPin, ms(1)) != pdPASS) {
            LOGWARNING("Failed to enqueue IRQ Pin to IREventQueue. Full?");
        }
        if(xQueueSend(speakerQueue, (void *)&irqPin, ms(1)) != pdPASS) {
            LOGWARNING("Failed to enqueue IRQ Pin to speakerQueue. Full?");
        }
        if(xQueueSend(solenoidQueue, (void *)&irqPin, ms(1)) != pdPASS) {
            LOGWARNING("Failed to enqueue IRQ Pin to solenoidQueue. Full?");
        }
#if IOIRQ_SW_DEBOUNCE == 1
        dly(IOIRQ_SW_DEBOUNCE_MS);  // CRITICAL: Debounce (used to compensate bounce back after IRQ goes back)
#endif
        // CRITICAL: Wait for interrupt signal to go back (so IRQ goes back again)
        // Since IRQ will follow interrupt signal for MCP23017
        while (ioexp.read(irqPin) == irqVal) { yd(); }
#if IOIRQ_SW_DEBOUNCE == 1
        dly(IOIRQ_SW_DEBOUNCE_MS);  // CRITICAL: Debounce (used to compensate bounce back after IRQ goes back)
#endif
//        IO_IRQ_WAITING = false;
//        wireUnlock();
    }
}

void vWheelTask(void* arg) {
    PWM motor = (*((peri *)arg)).motor;
    DIO ioexp = (*((peri *)arg)).ioexp;
    for(;;) {
        motor.set(0, 50);
        motor.set(1, 100);
        ioexp.setTBDirection(true);
        dly(1000);
        motor.set(0, 100);
        motor.set(1, 50);
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


void vSpeakerTask(void *arg) {
    Audio speaker = (*((peri *) arg)).speaker;
#define IR_TRG_PINS_AMOUNT 3
    String music[IR_TRG_PINS_AMOUNT] = {
            "0.wav",
            "1.wav",
            "2.wav"
    };
    uint8_t *irPin;
    for (;;) {
        if (xQueueReceive(speakerQueue, irPin, portMAX_DELAY)) {
            LOGA("Now playing: ");
            PRINTLN(music[*irPin].c_str());
//            speaker.play(music[*irPin].c_str());
        } else
            LOGWARNING("Time out receiving IRPin from Queue. This should not happen.");
    }
}

void vSolenoidTask(void* arg) {
    PWM motor = (*((peri *)arg)).motor;
    uint8_t *irPin;
    for (;;) {
        if (xQueueReceive(solenoidQueue, irPin, portMAX_DELAY)) {
            LOGA("Solenoid Queue RX:");
            PRINTLN(*irPin);
            // TODO: Implement PWM
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

void vTestISRTask(void *arg) {
    DIO ioexp = (*((peri *)arg)).ioexp;
    for(;;) {
        LOG(ioexp.read(0));
        dly(500);
    }
}