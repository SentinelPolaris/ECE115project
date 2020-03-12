#include <Arduino.h>
#include <SPI.h>
#include <gfxfont.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/4.h>
#include <Fonts/FreeMono9pt7b.h>


// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>
// IR Pin -> Increase score LUT
bool updateScoreFlag = false;
uint8_t lastArrow = 31;
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

void updateScore() {
    if (updateScoreFlag) {
        matrix.fillRect(7, 27, 26, 31, 0);
        // updateScoreFlag = false;
    }
    matrix.setCursor(7, 31);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 0, 0));
//    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.println(score);
}

void flashScore() {
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    for(uint8_t i=0; i<4; i++) {
        matrix.setCursor(7, 31);    // start at top left, with one pixel of spacing
        matrix.setTextColor(0);
        matrix.println(score);
        delay(100);
        matrix.setCursor(7, 31);    // start at top left, with one pixel of spacing
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.println(score);
        delay(500);
    }
}

void LCDIRGateL(){
    matrix.fillRect(7,0,3,15,matrix.Color333(7,0,0));
    delay(200);
    matrix.fillRect(7,0,3,15,0); 
}

void LCDIRGateR(){
    matrix.fillRect(15,0,3,15,matrix.Color333(7,2,4));
    delay(200);
    matrix.fillRect(15,0,3,15,0);
    
}

void solenoidCallback(){
    // Serial.println("solenoid");
    score += 20;
    updateScoreFlag = true;
    updateScore();
}

void IRGateCallbackR(){
    // Serial.println("IRGateR");
    score += 10;
    updateScoreFlag = true;
    updateScore();
    LCDIRGateR();
}
void IRGateCallbackL(){
    // Serial.println("IRGateL");
    score += 10;
    updateScoreFlag = true;
    updateScore();
    LCDIRGateL();
}

void slideCallback(){
    // Serial.println("slide");
    score += 5;
    updateScoreFlag = true;
    updateScore();
}

void LCDGameOver(){
    // matrix.fillScreen(0);
    for (int i = 0; i < 10; i++){
        matrix.fillCircle(16,5,3+i,matrix.ColorHSV((i / 70.0) * 150*i, 255, 255, true));
        delay(50);
    }
    for (int i = 0; i < 10; i++){
        matrix.fillCircle(16,5,3+i,0);
        delay(50);
    }

    matrix.setFont();
    matrix.setCursor(0, 1);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
    matrix.setTextColor(matrix.Color333(7, 7, 6));
    matrix.println("GAME");
    matrix.println("OVER");
    delay(1000);
    srand(micros());
    for(uint16_t i=0; i<5000; i++) {
        uint16_t xClear = rand() % 32;
        uint16_t yClear = rand() % 22;
        matrix.drawPixel(xClear, yClear, 0);
    }
    matrix.setFont(&Picopixel09edit4pt7b);
    flashScore();
    matrix.fillScreen(0);
}

void gameOver(){
    // Serial.println("game over");
    LCDGameOver();
    score = 0;
    updateScoreFlag = true;
    updateScore();
}
void setup() {
    Serial.begin(9600);

    Serial.setTimeout(1000);

    matrix.begin();
    matrix.setFont(&Picopixel09edit4pt7b);
    updateScore();
}



void loop() {
    uint8_t currentArrow = (millis() / 100) % 100;
    currentArrow = 31 - currentArrow%32;
    if(currentArrow != lastArrow) {
        lastArrow = currentArrow;
        matrix.fillRect(28,0,4,32,0);
        matrix.drawChar(28,currentArrow,'^',matrix.ColorHSV((currentArrow*10)%256, 255, 255, true),1,1);
    }


    if(Serial.available()) {
        // char scoreAddition = Serial.read();
        // score+=IR2SCORE[scoreAddition];
        // updateScoreFlag = true;
        String scoreAddition = Serial.readStringUntil('|');
        if(scoreAddition.equals("12")){
            gameOver();
        }
        else if(scoreAddition.equals("8") || scoreAddition.equals("9") || scoreAddition.equals("10") || scoreAddition.equals("11")){
            scoreAddition.remove(scoreAddition.indexOf('|'));
            int scoreOption = scoreAddition.toInt() - 8;

            switch (scoreOption)
            {
            case 0:
                solenoidCallback();
                break;
            case 1:
                IRGateCallbackL();
                break;
            case 2:
                IRGateCallbackR();
                break;
            case 3:
                slideCallback();
            default:
                break;
            }
            
        }
        else{

        }


    }
    int8_t currentSecond = (millis()/1000)%32;
//    matrix.drawChar(28,((-currentSecond)%32)+1,'^',0,1,1);
//     delay(50);
//     // updateScore();
// //    matrix.swapBuffers(false);
}



