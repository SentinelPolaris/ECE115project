#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#define HWSERIAL Serial4

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav2;     //xy=258,253
AudioPlaySdWav           playWav1;     //xy=265,150
AudioMixer4              mixer2;         //xy=479,252
AudioMixer4              mixer1;         //xy=482,160
AudioOutputI2S           audioOutput;           //xy=652,213
AudioConnection          patchCord1(playWav2, 0, mixer1, 1);
AudioConnection          patchCord2(playWav2, 1, mixer2, 1);
AudioConnection          patchCord3(playWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playWav1, 1, mixer2, 0);
AudioConnection          patchCord5(mixer2, 0, audioOutput, 1);
AudioConnection          patchCord6(mixer1, 0, audioOutput, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=656,333
// GUItool: end automatically generated code
uint8_t currentBGMIndex = -1;  // -1 so the first time it goes to 0
uint8_t avilBGM[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   1

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // Volume for playWav2
  mixer1.gain(1, 0.9);
  mixer2.gain(1, 0.9);
}

void playFile1(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(10);
}

void playFile2(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav2.play(filename);

  // A brief delay for the library read WAV info
  delay(10);
}

void switchBGM() {
  currentBGMIndex = (currentBGMIndex + 1) % 10;
  char filename[20];
  sprintf(filename, "BGM%d.WAV", avilBGM[currentBGMIndex]);
  playFile1(filename);  // filenames are always uppercase 8.3 format
}

void loop() {
  // Current BGM ended or haven't started
  if (!playWav1.isPlaying()) {
    switchBGM();
  }
  if (!playWav2.isPlaying()) {
    mixer1.gain(0, 0.9);
    mixer2.gain(0, 0.9);
  }
  if (HWSERIAL.available() > 0) {
    char incomingByte = HWSERIAL.read();
    if (incomingByte == 0) {  // Game over
      switchBGM();
    }
    char filename[20];
    sprintf(filename, "%d.wav", incomingByte);
    Serial.println(filename);
    mixer1.gain(0, 0.1);
    mixer2.gain(0, 0.1);
    playFile2(filename);
  }

}
