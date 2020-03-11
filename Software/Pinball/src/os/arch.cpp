//
// Created by Scott Zhao on 2020-02-03.
//
#include "arch.h"
const uint8_t IRQ = 2;

//void setup() {
////    dly(500);  // NOTE: USB Terminal doesn't work if enabled at the beginning of bootup
//}
//
//void loop() {
//    main();
//    while (true) { asm("nop"); }
//}

void vErr(String errMsg) {
    for(;;) {
        LOGERROR(errMsg);
        ESP.println(errMsg);
        vTaskDelay(2000);
#if DEBUG == 0
        return;
#endif
    }
}
