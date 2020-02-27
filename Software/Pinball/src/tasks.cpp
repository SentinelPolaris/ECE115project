//
// Created by Scott Zhao on 2020-02-26.
//
#pragma clang diagnostic ignored "-Wmissing-noreturn" // Disable clang inf loop warning

#include "os/arch.h"
#include "peri/ioexp.h"
#include "peri/pwm.h"
#include "peri/Audio.h"

void get_task_state() {
    // Credit: https://blog.csdn.net/zhzht19861011/article/details/50717549?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task
#define MAX_TASK_NUM 10
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
    for(;;) {
        get_task_state();
//        char buf[1000];
//        LOG(buf);
        dly(200);
    }
}

void vIOUnstuckTask(void* arg) {
    DIO ioexp = *((DIO *)arg);
    for(;;){
//        ioexp.clearInterrupt();
        dly(500);
    }
}

void vIOTask(void* arg) {
    DIO ioexp = *((DIO *) arg);
    for(;;) {
        // Block task while waiting for notification from ISR.
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        ioexp.IOIRQHandler();
    }
}

void vWheelTask(void* arg) {
    PWM motor = *((PWM *) arg);
    // FIXME Not Implemented
}