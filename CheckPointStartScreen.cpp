#include "CheckPointStartScreen.h"
#include "Fonts.h"
#include "Util.h"
#include "Colors.h"
#include "InputField.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "CookaPhone.h"
#include "ConfirmationDialog.h"


CheckPointStartScreen::CheckPointStartScreen():
CheckpointBaseScreen() {
    selectedInputInd = -1;
}

CheckPointStartScreen::CheckPointStartScreen(String _title, int _width, int _height):
CheckpointBaseScreen(_title, _width, _height) {
  byte offset = 50;
  byte inputHeight = 25;

  cpTimeInput = TimeInputField(_width / 4.2, offset + inputHeight + 10, 160, 25, 5);
  startTimeInput = TimeInputField(_width/4.2,offset+inputHeight*2+10*2,160,25,5);
  commentInput = TextInputField(5, offset + inputHeight * 4+10*5, 269, 75, 5);

  cpTimeInput.setMaxValueLength(5);
  startTimeInput.setMaxValueLength(5);
  commentInput.setMaxValueLength(70);
  commentInput.setText("");

  inputArr[0]=vehicleInput;
  inputArr[1]=cpTimeInput;
  inputArr[2]=startTimeInput;
  inputArr[3]=commentInput;
  selectedInputInd = -1;
}

void CheckPointStartScreen::drawScreen(Adafruit_TFTLCD tft) {

  CheckpointBaseScreen::drawScreen(tft);
  if (isDirty) {
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(6,95);
    tft.setCursor(cursorX,cursorY);
    //calculate font size
    Utils::StringMutators::printWithMargin(Translator::getCheckpointLabelText(),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(6,130);
    tft.setCursor(cursorX,cursorY);
    //calculate font size
    Utils::StringMutators::printWithMargin(Translator::getStartLabelText(),cursorX,cursorY,30,10,width,tft);

    setCursorPosition(6,170);
    tft.setCursor(cursorX,cursorY);
    Utils::StringMutators::printWithMargin(Translator::getCommentLabelText(),cursorX,cursorY,30,10,width,tft);

  }


  //DRAW TEXTBOX
  if(!confirmationDialogWasActivated){
    commentInput.draw(tft);
    cpTimeInput.draw(tft);
    startTimeInput.draw(tft);
    errorLabel.draw(tft);
  }

  isDirty = false;

}

void CheckPointStartScreen::processScreen(Adafruit_TFTLCD tft) {
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
        cpTimeInput.setDirty();
        startTimeInput.setDirty();
        commentInput.setDirty();
        checkpointInfoCtrl.setDirty();
        return;
      }

      if (currentKeyboardChar == '>') {
        if(validateInput()){
          confirmationDialog.setHasFinished();
          confirmationDialog.drawScreen(tft);
          bool hasBeenSent = cookaPhone->sendData(ckSettings->currentCheckpoint,vehicleInput.getText().toInt(),cpTimeInput.getTime().getTotalTimeInMilliseconds(),startTimeInput.getTime().getTotalTimeInMilliseconds(),0,commentInput.getText());

          if(!hasBeenSent && ckSettings->currentMsg.origin != Enumerations::Server){
            struct TimeRegistration timeRegistrationData;
            timeRegistrationData.checkpointNumber = ckSettings->currentCheckpoint;
            timeRegistrationData.vehicleNumber = vehicleInput.getText().toInt();
            timeRegistrationData.cpTime = cpTimeInput.getTime().getTotalTimeInMilliseconds();
            timeRegistrationData.startTime = startTimeInput.getTime().getTotalTimeInMilliseconds();
            timeRegistrationData.finishTime = 0;
            cookaStorage->storeTimeRegistration(timeRegistrationData);
          }

                    if(vehicleInput.getText().toInt()>0){
          String timeString = vehicleInput.getText();
          if(timeString.length()==1) timeString = "00"+timeString;
          else if(timeString.length()==2) timeString = "0"+timeString;
          timeString += " "+cpTimeInput.getText();
          timeString += " "+startTimeInput.getText();
          struct TimesSent t;
          timeString.toCharArray(t.time,timeString.length()+1);
          t.success=hasBeenSent;
          checkpointInfoCtrl.addTime(t);
                    }

          //check if we need to add a new message to our checkpointCtrl
          if(ckSettings->lastMessageSentOrReceived == ckSettings->currentMsg.timestamp){
            //if the times are equel it means we already changed it before in cookaPhone
            checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }else
           if(commentInput.getText().length()>0){
            //only the comment field is filled in, add it to our checkpointinfoctrl
            commentInput.getText().toCharArray(ckSettings->currentMsg.content,commentInput.getText().length());
            ckSettings->currentMsg.timestamp = 001234323;
            checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }

          //check if we need to add a new message to our checkpointCtrl
          if(commentInput.getText().length()>0){
            //only the comment field is filled in, add it to our checkpointinfoctrl

            commentInput.getText().toCharArray(ckSettings->currentMsg.content,commentInput.getText().length()+1);
            ckSettings->currentMsg.timestamp = ckSettings->lastMessageSentOrReceived;
            checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }

          vehicleInput.setText("");
          cpTimeInput.setValue("");
          startTimeInput.setValue("");
          commentInput.setText("");
          errorLabel.setText("");
          selectedInputInd=-1;
          confirmationDialogWasActivated=false;
          isDirty=true;
          checkpointInfoCtrl.setDirty();
          commentInput.setDirty();
          confirmationDialog.reset();
         return;
        }
      }
    }
  }else{
   if (currentKeyboardChar == '+') {
      selectedInputInd++;
      if (selectedInputInd > 3) {
        selectedInputInd = 0;
      }
    }

    if (currentKeyboardChar == '-') {
      selectedInputInd--;
      if (selectedInputInd < 0) {
        selectedInputInd = 3;
      }
    }

    if (cpTimeInput.hasCursor()) {
      cpTimeInput.processInput(currentKeyboardChar);
    }

    if (startTimeInput.hasCursor()) {
      startTimeInput.processInput(currentKeyboardChar);
    }

    if (commentInput.hasCursor()) {
      commentInput.processInput(currentKeyboardChar);
    }
  }

  if(currentKeyboardChar=='>'){
    if(validateInput()){
      confirmationDialog = ConfirmationDialog(F("Are you sure?"),tft.height()/3,tft.width()/4*3);
      confirmationDialog.drawScreen(tft);
      confirmationDialogWasActivated = true;
      selectedInputInd=0;
    }
  }

  if (originalySelected != selectedInputInd) {
    selectedInput->removeFocus();
    selectedInput->noCursor(tft);

    switch (selectedInputInd) {
      case 0:
      selectedInput = &vehicleInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 1:
      selectedInput = &cpTimeInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 2:
      selectedInput = &startTimeInput;
      ckKeypad.disableAlphaNumerics();
      break;
      case 3:
      selectedInput = &commentInput;
      ckKeypad.enableAlphaNumerics();
      break;
    }
  }
  selectedInput->setFocus();

}

boolean CheckPointStartScreen::validateInput() {
 errorLabel.setText("");
 boolean valid = true;

 if(vehicleInput.getText().length() == 0 && cpTimeInput.getText().length() == 0  && startTimeInput.getText().length() == 0 && commentInput.getText().length()>0){
   return true;
 }

 //make sure the time is valid and check the length aswell
 if (!cpTimeInput.getTime().receivedValidInput() || cpTimeInput.getText().length() < 5) {
    errorLabel.setText(Translator::getCheckpointErrorText());
    valid = false;
  }else if(!startTimeInput.getTime().receivedValidInput()|| startTimeInput.getText().length() < 5){
    errorLabel.setText(Translator::getStartErrorText());
    valid=false;
  }

  valid &= CheckpointBaseScreen::validateInput();
  return valid;
}

