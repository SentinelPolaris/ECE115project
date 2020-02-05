// Author: Nick Gammon
// Date: 19 February 2011

// Demonstration of an interrupt service routine connected to the MCP23017

#include <Wire.h>

// MCP23017 registers (everything except direction defaults to 0)

#define IODIRA   0x00   // IO direction  (0 = output, 1 = input (Default))
#define IODIRB   0x01
#define IOPOLA   0x02   // IO polarity   (0 = normal, 1 = inverse)
#define IOPOLB   0x03
#define GPINTENA 0x04   // Interrupt on change (0 = disable, 1 = enable)
#define GPINTENB 0x05
#define DEFVALA  0x06   // Default comparison for interrupt on change (interrupts on opposite)
#define DEFVALB  0x07
#define INTCONA  0x08   // Interrupt control (0 = interrupt on change from previous, 1 = interrupt on change from DEFVAL)
#define INTCONB  0x09
#define IOCON    0x0A   // IO Configuration: bank/mirror/seqop/disslw/haen/odr/intpol/notimp
//#define IOCON 0x0B  // same as 0x0A
#define GPPUA    0x0C   // Pull-up resistor (0 = disabled, 1 = enabled)
#define GPPUB    0x0D
#define INFTFA   0x0E   // Interrupt flag (read only) : (0 = no interrupt, 1 = pin caused interrupt)
#define INFTFB   0x0F
#define INTCAPA  0x10   // Interrupt capture (read only) : value of GPIO at time of last interrupt
#define INTCAPB  0x11
#define GPIOA    0x12   // Port value. Write to change, read to obtain value
#define GPIOB    0x13
#define OLLATA   0x14   // Output latch. Write to latch output.
#define OLLATB   0x15


#define port 0x20  // MCP23017 is on I2C port 0x20

#define ISR_INDICATOR 12  // pin 12
#define ONBOARD_LED 13    // pin 13

volatile bool keyPressed;

// set register "reg" on expander to "data"
// for example, IO direction
void expanderWriteBoth (const byte reg, const byte data ) 
{
  Wire.beginTransmission (port);
  Wire.write (reg);
  Wire.write (data);  // port A
  Wire.write (data);  // port B
  Wire.endTransmission ();
} // end of expanderWrite

// read a byte from the expander
unsigned int expanderRead (const byte reg) 
{
  Wire.beginTransmission (port);
  Wire.write (reg);
  Wire.endTransmission ();
  Wire.requestFrom (port, 1);
  return Wire.read();
} // end of expanderRead

// interrupt service routine, called when pin D2 goes from 1 to 0
void keypress ()
{
  digitalWrite (ISR_INDICATOR, HIGH);  // debugging
  keyPressed = true;   // set flag so main loop knows
}  // end of keypress

void setup ()
{
  pinMode (ISR_INDICATOR, OUTPUT);  // for testing (ISR indicator)
  pinMode (ONBOARD_LED, OUTPUT);  // for onboard LED

  Wire.begin ();  
  Serial.begin (115200); 
  Serial.println ("Starting ..."); 

  // expander configuration register
  expanderWriteBoth (IOCON, 0b01100000); // mirror interrupts, disable sequential mode
 
  // enable pull-up on switches
  expanderWriteBoth (GPPUA, 0xFF);   // pull-up resistor for switch - both ports

  // invert polarity
  expanderWriteBoth (IOPOLA, 0xFF);  // invert polarity of signal - both ports
  
  // enable all interrupts
  expanderWriteBoth (GPINTENA, 0xFF); // enable interrupts - both ports
  
  // no interrupt yet
  keyPressed = false;

  // read from interrupt capture ports to clear them
  expanderRead (INTCAPA);
  expanderRead (INTCAPB);
  
  // pin 19 of MCP23017 is plugged into D2 of the Arduino which is interrupt 0
  attachInterrupt(digitalPinToInterrupt(3), keypress, FALLING);
  
}  // end of setup

// time we turned LED on
unsigned long time = 0;
unsigned int keyValue = 0;

// called from main loop when we know we had an interrupt
void handleKeypress ()
{
  
  delay (100);  // de-bounce before we re-enable interrupts
  
  keyPressed = false;  // ready for next time through the interrupt service routine
  digitalWrite (ISR_INDICATOR, LOW);  // debugging
  
  // Read port values, as required. Note that this re-arms the interrupts.
  if (expanderRead (INFTFA))
    {
    keyValue &= 0x00FF;
    keyValue |= expanderRead (INTCAPA) << 8;    // read value at time of interrupt
    }
  if (expanderRead (INFTFB))
    {
    keyValue &= 0xFF00;
    keyValue |= expanderRead (INTCAPB);        // port B is in low-order byte
    }
  
  Serial.println ("Button states");
  Serial.println ("0                   1");
  Serial.println ("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5");
  
  // display which buttons were down at the time of the interrupt
  for (byte button = 0; button < 16; button++)
    {
    // this key down?
    if (keyValue & (1 << button))
      Serial.print ("1 ");
    else
      Serial.print (". ");
    
    } // end of for each button

  Serial.println ();
  
  // if a switch is now pressed, turn LED on  (key down event)
  if (keyValue)
    {
    time = millis ();  // remember when
    digitalWrite (ONBOARD_LED, HIGH);  // on-board LED
    }  // end if
  
}  // end of handleKeypress

void loop ()
{
  // was there an interrupt?
  if (keyPressed)
    handleKeypress ();

  // turn LED off after 500 ms 
 if (millis () > (time + 500) && time != 0)
   {
    digitalWrite (ONBOARD_LED, LOW);
    time = 0;
   }  // end if time up
 
}  // end of loop
