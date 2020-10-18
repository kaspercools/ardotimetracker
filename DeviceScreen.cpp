#include "DeviceScreen.h"
#include "Colors.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "LoadingScreen.h"
#include "CookaPhone.h"
#include "Util.h"
#include "Fonts.h"

DeviceScreen::DeviceScreen(){

}

DeviceScreen::DeviceScreen(String _title,int _width,int _height):
Screen(_title,_width,_height){

}


void DeviceScreen::drawScreen(Adafruit_TFTLCD tft){
  Screen::drawScreen(tft);
  if(isDirty){
    width=tft.width();

     tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(10,65);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("IMEI:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,65);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(String(ckSettings->imei),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(10,95);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(F("NR:"),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(150,95);
    tft.setCursor(cursorX,cursorY);

    Utils::StringMutators::printWithMargin(String(cookaPhone->getDeviceInd()),cursorX,cursorY,30,10,width,tft);

  }

  isDirty=false;
}

void DeviceScreen::processScreen(Adafruit_TFTLCD tft){

  //process keystrokes
  //check button select
  char key = ckKeypad.processInput();

 if(key =='*' && !goBack){
    nextScreen = Enumerations::LanguageScreen;
    hasFinished=true;
    goBack=false;
    return;
    /*goBack=true;
    timer = micros();*/
  }
}
