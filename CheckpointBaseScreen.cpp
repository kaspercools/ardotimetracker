#include "CheckpointBaseScreen.h"
#include "Colors.h"
#include "Fonts.h"
#include "Util.h"
#include "CheckpointInfoControl.h"
#include "CookaPhone.h"
#include "ConfirmationDialog.h"
#include "Globals.h"

CheckpointBaseScreen::CheckpointBaseScreen():Screen(){
  isDirty=true;
  checkpointInfoCtrl = CheckpointInfoControl();
  confirmationDialog = ConfirmationDialog(F("Are you sure?"),width/3,height/4*3);
}

CheckpointBaseScreen::CheckpointBaseScreen(String _title,int _width, int _height):Screen(_title,_width,_height){
  isDirty=true;
  byte offset = 50;
  byte inputHeight = 25;
  vehicleInput = NumericInputField(_width / 4.2, offset, 160, 25, 5);
  errorLabel = Label(10, offset + inputHeight * 6.3 + 25 * 3, 265, 25, 5);
  confirmationDialog = ConfirmationDialog(F(""),width/3,height/4*3);

  vehicleInput.setMaxValueLength(3);

  checkpointInfoCtrl = CheckpointInfoControl(height/1.75+1,40,height-height/1.75,width-40);

  //start timing
  msgTimer = micros();
}

void CheckpointBaseScreen::drawScreen(Adafruit_TFTLCD tft){
  width = tft.width();
  height = tft.height();
  Screen::drawScreen(tft);
  if(isDirty){
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(6, 55);
    tft.setCursor(cursorX, cursorY);
    //calculate font size

    Utils::StringMutators::printWithMargin(Translator::getVehicleLabelText(), cursorX, cursorY, 30, 10, width, tft);
    tft.drawLine(width / 1.75, 40, width / 1.75, height, Colors::DarkBlue);
  }

  if(!confirmationDialogWasActivated){
    checkpointInfoCtrl.draw(tft);
    vehicleInput.draw(tft);
  }
}

void CheckpointBaseScreen::processScreen(Adafruit_TFTLCD tft){
  if(!confirmationDialogWasActivated){
    if (vehicleInput.hasCursor()) {
      vehicleInput.processInput(currentKeyboardChar);
    }
    if (currentKeyboardChar != NO_KEY) {
      if (currentKeyboardChar == '*' && !goBack) {
        nextScreen = Enumerations::CheckPointSelectionScreen;
        hasFinished=true;
        goBack=false;

        return;
      }

      if (currentKeyboardChar != '<') {
        goBack = false;
      }

    }

    if(micros() - msgTimer > msgInterval){

      ckSettings->currentMsg = cookaPhone->checkForNewMessage();
      if(ckSettings->currentMsg.timestamp>0){
        checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
        checkpointInfoCtrl.setDirty();
      }

      msgTimer=micros();
    }
  }
}

boolean CheckpointBaseScreen::validateInput(){
  boolean valid = true;
  int vehicleNumber = vehicleInput.getValue();
  if (!inputValidator.validateVehicleNumber(vehicleNumber)) {
    errorLabel.setText(Translator::getVehicleErrorText());
    valid = false;
  }

  return valid;
}
