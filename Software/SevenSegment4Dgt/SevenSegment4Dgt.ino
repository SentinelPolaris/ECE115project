#define SER 8
#define RCLK 9
#define SRCLK 10

uint8_t LUT[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11100110};
uint8_t REV_MASK = B11111111;
uint8_t digitPins[] = {2, 3, 4, 5};


void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  for (int ii = 0; ii < 4; ii++) {
    pinMode(digitPins[ii], OUTPUT);
  }
  digitalWrite(RCLK, LOW); // Force register clock to 0
  shiftOut(SER, SRCLK, LSBFIRST, LUT[0]); // Internally load serial data
  digitalWrite(RCLK, HIGH);// Rising edge to update outputs
}
void loop() {
  //  for (int ii = 0; ii < 10; ii++) {
  //    setSR(ii);
  //    delay(300);
  //  }
  //  showNum(5000, 2);
  for (int jj = 0; jj < 10000; jj++) {
    uint32_t timeStart = millis();
    while (millis() - timeStart < 5) {
      for (int ii = 0; ii < 4; ii++) {
        showNum(jj, ii);
      }
    }
  }
}

void showNum(uint32_t number, uint8_t digit) {
  // Get displayed digit
  uint8_t num = (number / (int) pow(10, digit)) % 10;
  // TODO: Assert digit within 0 and 9
  setSR(num);
  for (int ii = 0; ii < 4; ii++) {
    digitalWrite(digitPins[ii], LOW);
  }
  digitalWrite(digitPins[digit], HIGH);
}

inline void setSR(uint8_t number) {
  digitalWrite(RCLK, LOW); // Force register clock to 0
  shiftOut(SER, SRCLK, LSBFIRST, LUT[number] ^ REV_MASK); // Internally load serial data
  digitalWrite(RCLK, HIGH);// Rising edge to update outputs
}
