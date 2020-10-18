#include "CheckPointSelectionScreen.h"
#include "Fonts.h"
#include "Util.h"
#include "Globals.h"
#include "Colors.h"
#include "LoadingScreen.h"
#include "CookaStorage.h"
#include "CookaPhone.h"


CheckPointSelectionScreen::CheckPointSelectionScreen():
Screen(){

}

CheckPointSelectionScreen::CheckPointSelectionScreen(String _title,int _width, int _height):
Screen(_title,_width,_height){
  checkPointInput = NumericInputField(10,100,200,25,5);
  checkPointInput.setMaxValueLength(3);
  errorLabel = Label(10,150,200,25,5);
  ckKeypad.disableAlphaNumerics();
  checkPointInput.setFocus();

}

void CheckPointSelectionScreen::drawScreen(Adafruit_TFTLCD tft){
  Screen::drawScreen(tft);
  if(isDirty){
    width=tft.width();
    //first we print our main screen

    tft.setTextSize(Fonts::fontSize);
    //if page is 1 then draw language
    tft.setTextColor(Colors::DarkBlue);
    setCursorPosition(10,65);
    tft.setCursor(cursorX,cursorY);
    //calculate font size

    Utils::StringMutators::printWithMargin(Translator::getCheckpointSelectionLabel(),cursorX,cursorY,30,10,width,tft);
  }

  //DRAW TEXTBOX
  if(!hasFinished){
    checkPointInput.draw(tft);
    errorLabel.draw(tft);
    isDirty=false;
  }
}

void CheckPointSelectionScreen::processScreen(Adafruit_TFTLCD tft){
  char key= ckKeypad.processInput();

  checkPointInput.processInput(key);

  if(key != NO_KEY){
    if(key=='>' && validateInput()){

      struct Checkpoint info;
      info = cookaStorage->getCheckpointInfo(checkPointInput.getText().toInt());


      ckSettings->currentCheckpoint = info.number;
      switch(info.type){
        case 1: case 7:
        nextScreen = Enumerations::CheckPointScreen;
        break;
        case 2:
        nextScreen = Enumerations::CheckPointScreen;
        break;
        case 3:
        nextScreen = Enumerations::CheckPointStartScreen;
        break;
        case 4:
        nextScreen = Enumerations::FlyingFinishScreen;
        break;
        case 5:
        nextScreen = Enumerations::FlyingFinishScreen;
        break;
        case 6:
        nextScreen = Enumerations::FlyingStartScreen;
        break;
        default:
        errorLabel.setText(Translator::getCheckpointSelectionErrorText());
        return;
        break;

      }

      LoadingScreen scrn = LoadingScreen(F("ProcessingData"),tft.width(),tft.height());
      scrn.setLoadingText(Translator::getLoadingCheckpoint());
      scrn.drawScreen(tft);
      cookaPhone->getGSMLOC();
      hasFinished=true;
      return;
    }

    if(key =='*' && !goBack){
      nextScreen = Enumerations::LanguageScreen;
      hasFinished=true;
      goBack=false;
      return;
    }
  }


}

boolean CheckPointSelectionScreen::validateInput(){
  //validate some fields and build error message
  boolean valid = true;
  if(checkPointInput.getValue() <= 0 || checkPointInput.getValue()>60){
    errorLabel.setText(Translator::getCheckpointSelectionErrorText());
    valid=false;
  }
  return valid;
}
