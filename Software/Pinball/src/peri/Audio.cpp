//
// Created by Scott Zhao on 2020-02-08.
//

#include "Audio.h"

void Audio::init() {
    patchCord1 = new AudioConnection(playWav1, 0, audioOutput, 0);
    patchCord2 = new AudioConnection(playWav1, 1, audioOutput, 1);
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
        LOGERROR("Audio Shield: Unable to read SD Card! Audio will be disabled!");
        disabled = true;
    }
}
void Audio::play(const char *filename) {
    if(!disabled) {
        if(DEBUG) {
            LOGA("Playing Audio: "); PRINTLN(filename);
        }
//        wireLock();
        LOG("Playing now");
        LOG(playWav1.play(filename));
        dly(5);
//        wireUnlock();
    }
}

void Audio::playFile(const char *filename)
{
    Serial.print("Playing file: ");
    Serial.println(filename);

    // Start playing the file.  This sketch continues to
    // run while the file plays.
    playWav1.play(filename);

    // A brief delay for the library read WAV info
    delay(5);

    // Simply wait for the file to finish playing.
    while (playWav1.isPlaying()) {
        // uncomment these lines if you audio shield
        // has the optional volume pot soldered
        //float vol = analogRead(15);
        //vol = vol / 1024;
        // sgtl5000_1.volume(vol);
    }
}