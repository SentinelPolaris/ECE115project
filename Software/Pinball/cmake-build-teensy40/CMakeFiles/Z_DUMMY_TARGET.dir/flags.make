# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# compile CXX with /Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/bin/arm-none-eabi-g++
CXX_FLAGS =   -D'PLATFORMIO=40100' -D'__IMXRT1062__' -D'TEENSY40' -D'USB_SERIAL' -D'ARDUINO=10805' -D'TEENSYDUINO=148' -D'CORE_TEENSY' -D'F_CPU=600000000' -D'LAYOUT_US_ENGLISH' -std=gnu++14

CXX_DEFINES = 

CXX_INCLUDES = -I/Users/scott/dev/ECE115project/Software/Pinball/include -I/Users/scott/dev/ECE115project/Software/Pinball/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TeensyThreads -I"/Users/scott/dev/ECE115project/Software/Pinball/.pio/libdeps/teensy40/Adafruit PWM Servo Driver Library_ID30" -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Wire -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Wire/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/cores/teensy4 -I"/Users/scott/.platformio/lib/Adafruit Motor Shield V2 Library_ID783" -I"/Users/scott/.platformio/lib/Adafruit Motor Shield V2 Library_ID783/utility" -I/Users/scott/.platformio/lib/TimerOne_ID131 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ADC -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/AccelStepper/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_CC3000 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_CC3000/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_GFX -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_NeoPixel -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_RA8875 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_STMPE610 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_VS1053 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_nRF8001 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Adafruit_nRF8001/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/AltSoftSerial -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Artnet -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Audio -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Audio/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Bounce -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Bounce2 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/CapacitiveSensor -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/CryptoAccel/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/DS1307RTC -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/DmxSimple -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/DogLcd -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/EEPROM -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/EasyTransfer -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/EasyTransferI2C -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Encoder -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Encoder/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Entropy -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Ethernet/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FastCRC -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FastLED -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FlexCAN -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FlexiTimer2 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FreqCount -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FreqMeasure -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FreqMeasureMulti -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/FrequencyTimer2 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ILI9341_t3 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/IRremote -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Keypad/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/LedControl/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/LedDisplay -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/LiquidCrystal/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/LiquidCrystalFast -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/LowPower -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/MFRC522/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/MIDI/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Metro -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/MsTimer2 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/NXPMotionSense -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/NXPMotionSense/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/OSC -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/OctoWS2811 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/OneWire -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/PS2Keyboard -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/PS2Keyboard/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/PWMServo -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Ping -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/PulsePosition -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/RA8875 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/RadioHead -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ResponsiveAnalogRead/src -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SD -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SD/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SPI -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SPIFlash -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ST7565 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ST7735_t3 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SerialFlash -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Servo -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ShiftPWM -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Snooze -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Snooze/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SoftPWM -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/SoftwareSerial -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TFT_ILI9163C -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Talkie -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Time -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TimeAlarms -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TimerOne -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TimerThree -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TinyGPS -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/Tlc5940 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/TouchScreen -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/USBHost_t36 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/USBHost_t36/utility -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/UTFT -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/VirtualWire -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/WS2812Serial -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/XBee -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/XPT2046_Touchscreen -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/i2c_t3 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ks0108 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/openGLCD -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/ssd1351 -I/Users/scott/.platformio/packages/framework-arduinoteensy/libraries/x10 -I/Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include -I/Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include/c++/5.4.1 -I/Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include/c++/5.4.1/arm-none-eabi -I/Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/5.4.1/include -I/Users/scott/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/5.4.1/include-fixed -I/Users/scott/.platformio/packages/tool-unity 

