/**
 * Shift Register Example
 * for 74HC595 456shift register
 * http://arduino.cc/en/Tutorial/ShiftOut
 * This sketch turns 8 LEDs on and of based on bytes
 * send to a 74HC595 shift register.
 * 
 * based on Tim Igoes Sketch one by one
 * http://arduino.cc/en/Tutorial/ShftOut12
 *
 * Hardware:
 * * 74HC595 shift register attached to pins 8, 11, and 12 of the Arduino
 * * LEDs attached to each of the outputs of the shift register
 *
 * by Fabian Moron Zirfas 
 *
 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;
//this holds our pattern an array of arrays (matrix)
char vals [8][8] = {
  {'0','1','2','3','4','5','6','0'},
  {'4','2','2','3','5','7','0','3'},
  {'0','5','4','0','2','2','3','6'},
  {'2','7','2','6','6','4','1','4'},
  {'7','4','5','5','6','3','0','3'},
  {'3','3','5','7','7','1','4','3'},
  {'6','2','7','1','0','6','4','2'},
  {'5','1','3','0','0','5','7','6'}

};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

}



void loop() {

for(int i = 0; i < 8;i++){
  for(int j=0; j< 8; j++){
    registerWrite(vals[i][j], HIGH);
    delay(100); // wait a moment
    }  
  }
}

// This method sends bits to the shift register:

void registerWrite(char pin, int whichState) {
    // ASCII '0' through '9' characters are
    // represented by the values 48 through 57.
    // so if the  you send a number from 0 through 7 in ASCII, 
    // you can subtract 48 to get the actual value:
    int bitToSet = pin - 48;

// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, bitToSet, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}
