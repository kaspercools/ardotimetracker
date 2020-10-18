#include "InfoScreen.h"
#include "Colors.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "LoadingScreen.h"
#include "CookaPhone.h"
#include "Util.h"
#include "Fonts.h"

InfoScreen::InfoScreen(){

}

InfoScreen::InfoScreen(String _title,int _width,int _height):
Screen(_title,_width,_height){

}


void InfoScreen::drawScreen(Adafruit_TFTLCD tft){
  Screen::drawScreen(tft);
  if(isDirty){
    width=tft.width();

    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(10,65);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("A:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,65);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Erase",cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,95);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("B:"),cursorX,cursorY,30,10,width,tft);

   setCursorPosition(150,95);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Move cursor up",cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,125);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("C:"),cursorX,cursorY,30,10,width,tft);

       setCursorPosition(150,125);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Move cursor down",cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,155);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("D:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,155);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Confirm/Send",cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,185);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("*:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,185);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Previous screen",cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,215);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("#:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,215);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("Option key/Activate chrono",cursorX,cursorY,30,10,width,tft);

    tft.setTextColor(Colors::Red);
    setCursorPosition(400,300);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin("OK (D)",cursorX,cursorY,30,10,width,tft);
  }


  isDirty=false;
}

void InfoScreen::processScreen(Adafruit_TFTLCD tft){

  char key = ckKeypad.processInput();

 if(key =='*' || key =='>' && !goBack){
    nextScreen = Enumerations::LanguageScreen;
    hasFinished=true;
    goBack=false;
    return;
  }
}
