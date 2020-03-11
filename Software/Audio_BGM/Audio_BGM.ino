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


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   1

void setup() {
  Serial.begin(9600);

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
}

void playFile1(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(500);

  // Simply wait for the file to finish playing.
  //  while (playWav1.isPlaying()) {
  //    // uncomment these lines if you audio shield
  //    // has the optional volume pot soldered
  //    //float vol = analogRead(15);
  //    //vol = vol / 1024;
  //    // sgtl5000_1.volume(vol);
  //  }
}

void playFile2(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav2.play(filename);

  // A brief delay for the library read WAV info
  delay(500);

  // Simply wait for the file to finish playing.
  //  while (playWav1.isPlaying()) {
  //    // uncomment these lines if you audio shield
  //    // has the optional volume pot soldered
  //    //float vol = analogRead(15);
  //    //vol = vol / 1024;
  //    // sgtl5000_1.volume(vol);
  //  }
}

void loop() {
  // Volumne for playWav1
  mixer1.gain(0, 0.1);
  mixer2.gain(0, 0.1);
  // Volume for playWav2
  mixer1.gain(1, 0.9);
  mixer2.gain(1, 0.9);
  playFile1("0.WAV");  // filenames are always uppercase 8.3 format
  playFile2("1.WAV");
  playFile1("2.WAV");
  playFile2("3.WAV");
}
