#define SER 8
#define RCLK 9
#define SRCLK 10
#define IR A0

uint8_t LUT[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11100110};
uint8_t REV_MASK = B11111111;
uint8_t digitPins[] = {2, 3, 4, 5};
uint32_t score = 0;
uint8_t released = 1;

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(IR, INPUT);
  for (int ii = 0; ii < 4; ii++) {
    pinMode(digitPins[ii], OUTPUT);
  }
  digitalWrite(RCLK, LOW); // Force register clock to 0
  shiftOut(SER, SRCLK, LSBFIRST, LUT[0]); // Internally load serial data
  digitalWrite(RCLK, HIGH);// Rising edge to update outputs
}
void loop() {
  if (analogRead(IR) < 50 && released == 1) {
    score += 5;
    released = 0;
  }
  if(analogRead(IR) > 50)
    released = 1;
//  Serial.print
  for (int ii = 0; ii < 4; ii++) {
    showNum(score, ii);
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
