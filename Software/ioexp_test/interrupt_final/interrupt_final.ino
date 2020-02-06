#include <Adafruit_MCP23017.h>
Adafruit_MCP23017 mcp;
volatile boolean IRQ_FLAG = false;
volatile uint32_t FLAG_COUNT = 0;
volatile boolean IRQ_SKIPPED = false;
uint8_t IRQ = 3;


void isr() {
  //  Serial.println("ISR");
  if (IRQ_FLAG) {
    Serial.print(".");
    IRQ_SKIPPED = true;
  }
  else {
    IRQ_FLAG = true;
    FLAG_COUNT++;
    Serial.println(FLAG_COUNT);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IRQ, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  mcp.begin();
  mcp.setupInterrupts(true, false, LOW);


  mcp.pinMode(7, INPUT);
  mcp.pullUp(7, HIGH);  // turn on a 100K pullup internally
  mcp.setupInterruptPin(7, RISING);

  //  mcp.pinMode(6, INPUT);
  //  mcp.pullUp(6, HIGH);  // turn on a 100K pullup internally

  Serial.begin(115200);
  attachInterrupt(3, isr, FALLING);
  mcp.readGPIOAB();

  pinMode(11, INPUT);
}

void loop() {
  //    mcp.readGPIOAB();

  //    uint8_t pin = mcp.getLastInterruptPin();
  //    uint8_t val = mcp.getLastInterruptPinValue();
  //    if (pin != 255) {
  //      Serial.print("##");
  //      Serial.print(pin);
  //      Serial.print(":");
  //      Serial.println(val);
  //    }
  // put your main code here, to run repeatedly:
  if (IRQ_FLAG) {
    delay(100);
    uint8_t pin = mcp.getLastInterruptPin();
    uint8_t val = mcp.getLastInterruptPinValue();
    // TODO: Assert pin
    //    mcp.readGPIOAB();
    //    Serial.print(pin); Serial.print(":"); Serial.println(val);
    // FIXME: Doing random mcp io in this region would cause hang randomly
    for (bool debounceExit = true; debounceExit;) {
      while (mcp.digitalRead(pin) == val) {}
      uint32_t timeStart = millis();
      while (millis() - timeStart < 20) {
        //        if (mcp.digitalRead(pin) == val) {
        //          continue;
        //        }
      }
      debounceExit = false;
    }
    IRQ_FLAG = false;
    //    if(IRQ_SKIPPED) {mcp.getLastInterruptPinValue(); IRQ_SKIPPED = false;}
  }
  else if (digitalRead(11)) {
    Serial.println("Force Clearing flag");
    mcp.readGPIOAB();
  }
}
