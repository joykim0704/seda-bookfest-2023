#include "SevenSeg.h";
SevenSeg dispTen(2,3,4,5,6,7,8);
SevenSeg dispOne(2,3,4,5,6,7,8);
const int numofDigitsTen = 1;
const int numofDigitsOne = 1;
int digitPinsTen[1] = {A1};
int digitPinsOne[1] = {A2};
void setup() {
  dispTen.setDigitPins(numofDigitsTen, digitPinsTen);
  dispTen.setDigitDelay(1667);
  dispOne.setDigitPins(numofDigitsOne, digitPinsOne);
  dispOne.setDigitDelay(1667);
  
}
int digitWrite[2] = {0,0};
void loop() {
  dispTen.write(digitWrite[0]);
  dispTen.clearDisp();
  dispOne.write(digitWrite[1]);
  dispOne.clearDisp();
}
void addCounter() {
  if(digitWrite[1] == 9) {
    if(digitWrite[0] == 9) {
      digitWrite[0] = 0;
      digitWrite[1] = 0;
    }
    digitWrite[0] = digitWrite[0] + 1;
    digitWrite[1] = 0;
  } else {
    digitWrite[1] = digitWrite[1] + 1;
  }
}
void clearCounter() {
  digitWrite[0] = 0;
  digitWrite[1] = 0;
}

