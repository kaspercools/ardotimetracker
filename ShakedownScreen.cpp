#include "ShakedownScreen.h"
#include "Fonts.h"
#include "InputField.h"
#include "Util.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Colors.h"


ShakedownScreen::ShakedownScreen():
Screen(){
}

ShakedownScreen::ShakedownScreen(String _title,int _width, int _height):
Screen(_title,_width,_height){
  byte offset = 50;
  byte  inputHeight = 25;
  vehicleInput = NumericInputField(_width/4.2,offset,160,25,5);
  cpTimeInput = TimeInputField(_width/4.2,offset+inputHeight+15,160,25,5);
  commentInput = TextInputField(10,offset+inputHeight*3+25*3,260,75,5);
  errorLabel = Label(10,offset+inputHeight*6.3+25*3,265,25,5);


  vehicleInput.setMaxValueLength(3);
  cpTimeInput.setMaxValueLength(12);

  commentInput.setMaxValueLength(140);

  inputArr[0]=vehicleInput;
  inputArr[1]=cpTimeInput;

  inputArr[2]=commentInput;
  selectedInputInd = 0;
}

void ShakedownScreen::drawScreen(Adafruit_TFTLCD tft){

  if(isDirty){
    width=tft.width();
    height=tft.height();
    Screen::drawScreen(tft);

    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);
    setCursorPosition(6,55);
    tft.setCursor(cursorX,cursorY);
    String carLabel ="Wagen nr:";
    Utils::StringMutators::printWithMargin(carLabel,cursorX,cursorY,30,10,width,tft);

    setCursorPosition(6,95);
    tft.setCursor(cursorX,cursorY);
    String checkPointLabel ="CP tijd:";
    Utils::StringMutators::printWithMargin(checkPointLabel,cursorX,cursorY,30,10,width,tft);

    setCursorPosition(6,135);
    tft.setCursor(cursorX,cursorY);
    String opmerking ="Opmerking:";
    Utils::StringMutators::printWithMargin(opmerking,cursorX,cursorY,30,10,width,tft);

    tft.drawLine(width/1.75,40,width/1.75,height,Colors::DarkBlue);
    selectedInput->removeFocus();
  }

  vehicleInput.draw(tft);
  cpTimeInput.draw(tft);

  commentInput.draw(tft);
  errorLabel.draw(tft);
  isDirty=false;
}

void ShakedownScreen::processScreen(Adafruit_TFTLCD tft){
  int originalySelected = selectedInputInd;
  selectedInputInd = (selectedInputInd<0)?0:selectedInputInd;
  boolean requestHandled;
  char key = ckKeypad.processInput();

  if(vehicleInput.hasCursor()){
    vehicleInput.processInput(key);
  }

  if(cpTimeInput.hasCursor()){
    cpTimeInput.processInput(key);
  }


  if(commentInput.hasCursor()){
    commentInput.processInput(key);
  }

  if(key != NO_KEY){
    if(key =='<' && !goBack){
      goBack=true;
      timer = micros();
    }

    if(key !='<'){
      goBack=false;
    }

    if(key=='>'){
      validateInput();
    }

    if(key == '+'){
      selectedInputInd++;
      if(selectedInputInd >3){
        selectedInputInd=0;
      }
    }

    if(key == '-'){
      selectedInputInd--;
      if(selectedInputInd < 0){
        selectedInputInd=3;
      }
    }
  }


  if(originalySelected!=selectedInputInd){
    selectedInput->removeFocus();
    selectedInput->noCursor(tft);

    switch(selectedInputInd){
      case 0:
      selectedInput = &vehicleInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 1:
      selectedInput = &cpTimeInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 2:
      selectedInput = &commentInput;
      ckKeypad.enableAlphaNumerics();

      break;
    }
  }
  selectedInput->setFocus();

  if (ckKeypad.getState()==HOLD){
    if(goBack && (micros() - timer >= interval)){
      nextScreen = Enumerations::CheckPointSelectionScreen;
      hasFinished=true;
      goBack=false;
    }
  }
}

boolean ShakedownScreen::validateInput(){
  boolean valid =true;
  int vehicleNumber = vehicleInput.getValue();
  if(vehicleNumber <= 0 || vehicleNumber > 500){
    valid=false;
    errorLabel.setText("Wagennr niet geldig");
  }else if(!cpTimeInput.getTime().receivedValidInput()){
    errorLabel.setText("CP tijd niet geldig");
  }else
  {
    errorLabel.setText("");
  }
  return valid;
}
