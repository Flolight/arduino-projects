#include <Keypad.h>
#include "LedControl.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
char displayedKey = '0';
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LedControl lc=LedControl(12,10,11,1);
void resetMatrix(){
  lc.clearDisplay(0);
}

void setup() {
  Serial.begin(9600);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  resetMatrix();
}

void writeOnMatrix(char key){
  /* here is the data for the characters */
  byte a[5]={B01111110,
             B10001000,
             B10001000,
             B10001000,
             B01111110};
  byte b[5]={B01100110,
             B10011001,
             B10010001,
             B10010001,
             B11111111};
  byte c[5]={B01000100,
             B10000010,
             B10000010,
             B10000010,
             B01111100};
  byte d[5]={B11111110,
             B00010010,
             B00100010,
             B00100010,
             B00011100};

  switch(key){
      case 'A':
        writeLetter(a);
        break;
      case 'B':
        writeLetter(b);
        break;
      case 'C':
        writeLetter(c);
        break;
      case 'D':
        writeLetter(d);
        break;
      default:
        resetMatrix();
        break;
    }

}

void writeLetter(char l[]){
  lc.setRow(0,0,l[0]);
  lc.setRow(0,1,l[1]);
  lc.setRow(0,2,l[2]);
  lc.setRow(0,3,l[3]);
  lc.setRow(0,4,l[4]);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.print(customKey);
    Serial.print(",");
    displayedKey = customKey;
    Serial.println(displayedKey);
    writeOnMatrix(displayedKey); 
  }
}
