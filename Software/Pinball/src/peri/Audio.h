//
// Created by Scott Zhao on 2020-02-08.
//

#ifndef PINBALL_AUDIO_H
#define PINBALL_AUDIO_H
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

#include "os/interface.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class Audio {
public:
    Audio() = default;

    void init();
    void play(const char *filename);
    void playFile(const char *filename);

protected:
    bool disabled = false;
    AudioPlaySdWav playWav1;
    AudioOutputI2S audioOutput;
    AudioControlSGTL5000 sgtl5000_1;
    AudioConnection *patchCord1;
    AudioConnection *patchCord2;
};


#endif //PINBALL_AUDIO_H
