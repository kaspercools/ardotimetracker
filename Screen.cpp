#include "Screen.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "Colors.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "CookaPhone.h"


Screen::Screen(){
  hasFinished=false;
  _isChronoEnabled = false;
  isDirty=false;
  ckKeypad = AlphanumericKeypad();
  inputValidator = InputValidation();
  cookaSignalBar = CookaSignalBar();
  clockTimer = micros();
  currentTime=CookaTime(0);
}

Screen::Screen(String _title,int _height,int _width){
  ckKeypad = AlphanumericKeypad();
  hasFinished=false;
  isDirty=true;
  setCursorPosition(0,0);
  title=_title;
  width=_width;
  height=_height;
  cookaSignalBar = CookaSignalBar(440,31);
  clockTimer = micros();
  currentTime = CookaTime(0);
}

void Screen::setTitle(String _title){
  title=_title;
}

void Screen::drawScreen(Adafruit_TFTLCD tft){

  if(isDirty){
    tft.fillRect(0,0,tft.width(),tft.height(),Colors::White);
    tft.fillRect(0,0,tft.width(),40,Colors::DarkBlue);

    tft.setCursor(5,10);
    tft.setTextColor(Colors::White);
    tft.setTextSize(TITLE_FONT_SIZE);
    tft.setTextWrap(true);
    tft.print(title);
    drawClock(tft);
  }

}

void Screen::drawClock(Adafruit_TFTLCD tft){

      tft.fillRect(400,0,0,40,Colors::DarkBlue);

      tft.setCursor(tft.width()-125,10);
      cookaSignalBar.draw(tft);

}
void Screen::setCursorPosition(int x, int y){
  cursorX = x;
  cursorY = y;
}

void Screen::processScreen(Adafruit_TFTLCD tft){

}

void Screen::processTagHeuerData(){
  //do nothing with this data, leave it up to my children instead!
}

Enumerations::ScreenEnum Screen::getScreenToBeInvoked(){
  if(hasFinished){
    return nextScreen;
  }else
  {
    return Enumerations::NoScreen;
  }
}

boolean Screen::isFinished(){
  return hasFinished;
}

void Screen::setIsDirty(){
  isDirty=true;
}

boolean Screen::isScreenDirty(){
  return isDirty;
}

bool Screen::isChronoEnabled(){
  return _isChronoEnabled;
}

