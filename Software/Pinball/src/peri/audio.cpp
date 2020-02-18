//
// Created by Scott Zhao on 2020-02-08.
//

#include "audio.h"

audio::audio() {
    wireLock();
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.1);
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
        LOGERROR("Audio Shield: Unable to read SD Card! Audio will be disabled!");
        disabled = true;
    }
    wireUnlock();
}

void audio::play(const char *filename) {
    if(!disabled) {
        if(DEBUG) {
            LOGA("Playing audio: "); PRINT(filename);
        }
        wireLock();
        playWav1.play(filename);
        wireUnlock();
    }
}