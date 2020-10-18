#include "LanguageScreen.h"
#include "Colors.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "LoadingScreen.h"
#include "CookaPhone.h"

LanguageScreen::LanguageScreen(){

}

LanguageScreen::LanguageScreen(String _title,int _width,int _height):
Screen(_title,_width,_height){
  selectedItem=1;

  interval = 5.0 * 1000000UL;
}

void LanguageScreen::drawSelectionArrow(Adafruit_TFTLCD tft){

  tft.fillRect(0,40,29,tft.height()-40, Colors::White);

  byte lineHeight=40;
  cursorY=tft.height()/8*3;

  tft.fillTriangle(cursorX,(cursorY+20)+(lineHeight*(selectedItem-1)),cursorX,cursorY+(lineHeight*(selectedItem-1)),cursorX+10,(cursorY+10)+(lineHeight*(selectedItem-1)),Colors::Orange);
}

void LanguageScreen::drawScreen(Adafruit_TFTLCD tft){
  if(isDirty){
    Screen::drawScreen(tft);
    tft.setTextSize(TITLE_FONT_SIZE);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(30,tft.height()/8*3);
    tft.setCursor(cursorX,cursorY);
    tft.print(F("Nederlands"));

    cursorY+=40;
    tft.setCursor(cursorX,cursorY);
    tft.print(F("Francais"));
    cursorY+=40;
    tft.setCursor(cursorX,cursorY);

    tft.print(F("English"));

    setCursorPosition(15,tft.height()/8*3);
    drawSelectionArrow(tft);
  }

  isDirty=false;
}

void LanguageScreen::processScreen(Adafruit_TFTLCD tft){

  char key = ckKeypad.processInput();
  if(key != NO_KEY){

    if(key=='-'){
      selectedItem--;
      if(selectedItem<1){selectedItem=3;}
      drawSelectionArrow(tft);
    }
    else if(key=='+'){
      selectedItem++;
      if(selectedItem>3){selectedItem=1;}
      drawSelectionArrow(tft);
    }else if(key=='>'){
      nextScreen = Enumerations::CheckPointSelectionScreen;
      ckSettings->lang=selectedItem;
      hasFinished=true;
    }

    if(key =='*' && !getData){
      getData=true;
      timer = micros();
    }

    if(key !='*'){
      getData=false;
    }

    if(key =='#'){
      nextScreen = Enumerations::DeviceScreen;
      hasFinished=true;
      goBack=false;
      return;
    }
  }

  if (ckKeypad.getState()==HOLD){
    if(getData && (micros() - timer >= interval)){
      LoadingScreen scrn = LoadingScreen(F("Processing data"),tft.width(),tft.height());
      scrn.setLoadingText(F("Getting data.."));
      scrn.drawScreen(tft);
      cookaPhone->loadCheckpointData();
      isDirty=true;

      timer=0;
      getData=false;
    }
  }
}
