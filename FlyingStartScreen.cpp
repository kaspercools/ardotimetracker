#include "FlyingStartScreen.h"
#include "Fonts.h"
#include "Util.h"
#include "Colors.h"
#include "InputField.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "CookaPhone.h"
#include "ConfirmationDialog.h"


FlyingStartScreen::FlyingStartScreen():
CheckpointBaseScreen() {
  _isChronoEnabled = true;
}

FlyingStartScreen::FlyingStartScreen(String _title, int _width, int _height):
CheckpointBaseScreen(_title, _width, _height) {
  byte offset = 50;
  byte inputHeight = 25;

  flyingStartTimeInput = TimeInputField(_width/4.2,offset+inputHeight+15,160,25,5);
  commentInput = TextInputField(5, offset + inputHeight * 2+15 + 25 * 2, 269, 75, 5);

  flyingStartTimeInput.setMaxValueLength(12);
  flyingStartTimeInput.enableDetails();
  commentInput.setMaxValueLength(70);
  commentInput.setText(F(""));

  inputArr[0]=vehicleInput;
  inputArr[1]=flyingStartTimeInput;
  inputArr[2]=commentInput;
  selectedInputInd=-1;
  _isChronoEnabled = true;
}

void FlyingStartScreen::redrawChronoIcon(Adafruit_TFTLCD tft){


  tft.drawCircle(tft.width()-15,tft.height()-15,10,Colors::DarkBlue);
  tft.drawLine(tft.width()-15,tft.height()-24,tft.width()-15,tft.height()-16,Colors::Orange);
  tft.drawLine(tft.width()-14,tft.height()-15,tft.width()-6,tft.height()-15,Colors::Orange);

  if(!_isChronoEnabled){
    tft.setTextColor(Colors::Red);
  }else{
     tft.setTextColor(Colors::White);
  }
    tft.setTextSize(3);
    tft.setCursor(tft.width()-22,tft.height()-28);
    tft.print("x");
}

void FlyingStartScreen::drawScreen(Adafruit_TFTLCD tft) {

  CheckpointBaseScreen::drawScreen(tft);
  if (isDirty) {

    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(6, 95);
    tft.setCursor(cursorX, cursorY);

    setCursorPosition(6,95);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(Translator::getStartLabelText(),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(6,135);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(Translator::getCommentLabelText(),cursorX,cursorY,30,10,width,tft);

    redrawChronoIcon(tft);
  }

  if(!confirmationDialogWasActivated){
    flyingStartTimeInput.draw(tft);
    commentInput.draw(tft);
    errorLabel.draw(tft);
  }

  isDirty = false;

}

void FlyingStartScreen::processScreen(Adafruit_TFTLCD tft) {
  int originalySelected = selectedInputInd;
  selectedInputInd = (selectedInputInd < 0) ? 0 : selectedInputInd;
  boolean requestHandled;
  currentKeyboardChar = ckKeypad.processInput();

  CheckpointBaseScreen::processScreen(tft);

  if(confirmationDialogWasActivated){
    if(currentKeyboardChar != NO_KEY){

      if(currentKeyboardChar =='<'){
        isDirty=true;
        confirmationDialogWasActivated=false;
        confirmationDialog.reset();

        vehicleInput.setDirty();
        flyingStartTimeInput.setDirty();
        commentInput.setDirty();
        checkpointInfoCtrl.setDirty();
        return;
      }

      if (currentKeyboardChar == '>') {
        if(validateInput()){
          confirmationDialog.setHasFinished();
          confirmationDialog.drawScreen(tft);
          bool hasBeenSent = cookaPhone->sendData(ckSettings->currentCheckpoint,vehicleInput.getText().toInt(),0,0,flyingStartTimeInput.getTime().getTotalTimeInMilliseconds(),commentInput.getText());

          if(!hasBeenSent && ckSettings->currentMsg.origin != Enumerations::Server){
            struct TimeRegistration timeRegistrationData;
            timeRegistrationData.checkpointNumber = ckSettings->currentCheckpoint;
            timeRegistrationData.vehicleNumber = vehicleInput.getText().toInt();
            timeRegistrationData.cpTime=0;
            timeRegistrationData.startTime = 0;
            timeRegistrationData.finishTime = flyingStartTimeInput.getTime().getTotalTimeInMilliseconds();
            cookaStorage->storeTimeRegistration(timeRegistrationData);
          }

          if(vehicleInput.getText().toInt()>0){
          String timeString = vehicleInput.getText();
          if(timeString.length()==1) timeString = "00"+timeString;
          else if(timeString.length()==2) timeString = "0"+timeString;
          timeString += " "+flyingStartTimeInput.getText();
          struct TimesSent t;
          timeString.toCharArray(t.time,timeString.length()+1);
          t.success=hasBeenSent;
          checkpointInfoCtrl.addTime(t);
          }

          if(ckSettings->lastMessageSentOrReceived == ckSettings->currentMsg.timestamp){
            checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }else
           if(commentInput.getText().length()>0){
            commentInput.getText().toCharArray(ckSettings->currentMsg.content,commentInput.getText().length()+1);
            ckSettings->currentMsg.timestamp = ckSettings->lastMessageSentOrReceived;
            checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }

          vehicleInput.setText(F(""));
          commentInput.setText(F(""));
          errorLabel.setText(F(""));
          checkpointInfoCtrl.setDirty();
          vehicleInput.setText(F(""));
          flyingStartTimeInput.setValue(F(""));
          flyingStartTimeInput.setDirty();
          commentInput.setDirty();
          checkpointInfoCtrl.setDirty();
          selectedInputInd=-1;
          confirmationDialogWasActivated=false;
          isDirty=true;
          confirmationDialog.reset();
          return;
        }
      }
    }
  }else{
    if (currentKeyboardChar == '+') {
        selectedInputInd++;
                    if(selectedInputInd == 1 && _isChronoEnabled) selectedInputInd++;
        if (selectedInputInd > 2) {
          selectedInputInd = 0;
        }
      }

      if (currentKeyboardChar == '-') {
        selectedInputInd--;

            if(selectedInputInd == 1 && _isChronoEnabled) selectedInputInd--;
        if (selectedInputInd < 0) {
          selectedInputInd = 2;
        }
      }

    if(currentKeyboardChar =='#' && !holdChronoSwitch){
      holdChronoSwitch=true;
    }else{
      if(!holdChronoSwitch){
        chronoTimer = micros();
      }
    }

    if (flyingStartTimeInput.hasCursor() && !_isChronoEnabled) {
      flyingStartTimeInput.processInput(currentKeyboardChar);
    }
    if (commentInput.hasCursor()) {
      commentInput.processInput(currentKeyboardChar);
    }


  }



  if(currentKeyboardChar=='>'){
    if(validateInput()){
      confirmationDialog.drawScreen(tft);
      confirmationDialogWasActivated = true;
      selectedInputInd=0;
    }
  }

  if (originalySelected != selectedInputInd) {
    selectedInput->removeFocus();
    selectedInput->noCursor(tft);

    switch(selectedInputInd){
      case 0:
      selectedInput = &vehicleInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 1:
      selectedInput = &flyingStartTimeInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 2:
      selectedInput = &commentInput;
      ckKeypad.enableAlphaNumerics();

      break;
    }
  }
  if(selectedInputInd != 1 || (selectedInputInd == 1 && !_isChronoEnabled)) {
    selectedInput->setFocus();
  }
}

void FlyingStartScreen::processTagHeuerData(){
  String time = cookaStorage->readNextChronoValue().time;
  if(time.length()>0){
    flyingStartTimeInput.setValue(time);
  }
}


boolean FlyingStartScreen::validateInput() {
 errorLabel.setText("");
 boolean valid = true;
 if(vehicleInput.getText().length() == 0 && flyingStartTimeInput.getText().length() == 0 && commentInput.getText().length()>0){
   return true;
 }
 if(!flyingStartTimeInput.getTime().receivedValidInput() || flyingStartTimeInput.getText().length()<12){
    errorLabel.setText(Translator::getStartErrorText());
    valid=false;
  }

  valid &= CheckpointBaseScreen::validateInput();
  return valid;
}

