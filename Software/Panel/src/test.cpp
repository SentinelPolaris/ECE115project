#include <Arduino.h>
#include <SPI.h>
#include <gfxfont.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/4.h>
// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>
// IR Pin -> Increase score LUT
uint32_t IR2SCORE[] = {5, 10, 15, 20};
bool updateScoreFlag = false;
// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int score = 0;
void setup() {
    Serial.begin(9600);

    matrix.begin();
    matrix.setFont(&Picopixel09edit4pt7b);
}
void updateScore() {
    if (updateScoreFlag) {
        matrix.fillRect(0, 0, 20, 20, 0);
        updateScoreFlag = false;
    }
    matrix.setCursor(10, 10);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 0, 0));
//    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.println(score);
}
void loop() {
    // Do nothing -- image doesn't change
//    matrix.fillScreen(0);
//    for (int i = 0; i < 10; i++) {
//        matrix.drawCircleHelper(10, 10, (i-1)%10, 0x4, 0);
//        matrix.drawCircleHelper(10, 10, i, 0x4, matrix.ColorHSV((i / 20.0) * 1536, 255, 255, true));
//        delay(50);
//    }
    if(Serial.available()) {
        char scoreAddition = Serial.read();
        score+=IR2SCORE[scoreAddition];
        updateScoreFlag = true;
    }
//    matrix.drawChar(27,20-score%20,'^',matrix.Color333(7,0,0),1,1);
    delay(50);
    updateScore();
//    matrix.swapBuffers(false);
}
