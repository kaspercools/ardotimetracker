#include "CheckPointScreen.h"
#include "Fonts.h"
#include "Util.h"
#include "Colors.h"
#include "InputField.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "Globals.h"
#include "CookaPhone.h"
#include "ConfirmationDialog.h"


CheckPointScreen::CheckPointScreen():
CheckpointBaseScreen() {
    selectedInputInd = -1;
}

CheckPointScreen::CheckPointScreen(String _title, int _width, int _height):
CheckpointBaseScreen(_title, _width, _height) {
  byte offset = 50;
  byte inputHeight = 25;

  cpTimeInput = TimeInputField(_width / 4.2, offset + inputHeight + 15, 160, 25, 5);
  commentInput = TextInputField(5, offset + inputHeight * 2+15 + 25 * 2, 269, 75, 5);

  cpTimeInput.setMaxValueLength(12);
  commentInput.setMaxValueLength(70);
  commentInput.setText("");

  selectedInputInd = -1;

  inputArr[0] = vehicleInput;
  inputArr[1] = cpTimeInput;
  inputArr[2] = commentInput;

  Serial.println(String(selectedInputInd));
}

void CheckPointScreen::drawScreen(Adafruit_TFTLCD tft) {

  CheckpointBaseScreen::drawScreen(tft);
  if (isDirty) {
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);

    setCursorPosition(6, 95);
    tft.setCursor(cursorX, cursorY);

    //calculate font size
    Utils::StringMutators::printWithMargin(Translator::getCheckpointLabelText(), cursorX, cursorY, 16, 10, width, tft);
    setCursorPosition(6, 135);
    tft.setCursor(cursorX, cursorY);

    Utils::StringMutators::printWithMargin(Translator::getCommentLabelText(), cursorX, cursorY, 16, 15, 269, tft);
  }

  //DRAW TEXTBOX
  //draw input fields
  if(!confirmationDialogWasActivated){
    commentInput.draw(tft);
    cpTimeInput.draw(tft);
    errorLabel.draw(tft);
  }

  isDirty = false;

}

void CheckPointScreen::processScreen(Adafruit_TFTLCD tft) {
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
        commentInput.setDirty();
        checkpointInfoCtrl.setDirty();
        return;
      }

      if (currentKeyboardChar == '>') {
        if(validateInput()){

          confirmationDialog.setHasFinished();
          confirmationDialog.drawScreen(tft);
          bool hasBeenSent = cookaPhone->sendData(ckSettings->currentCheckpoint,vehicleInput.getText().toInt(),cpTimeInput.getTime().getTotalTimeInMilliseconds(),0,0,commentInput.getText());

          if(!hasBeenSent && ckSettings->currentMsg.origin != Enumerations::Server){
            struct TimeRegistration timeRegistrationData;
            timeRegistrationData.checkpointNumber = ckSettings->currentCheckpoint;
            timeRegistrationData.vehicleNumber = vehicleInput.getText().toInt();
            timeRegistrationData.cpTime = cpTimeInput.getTime().getTotalTimeInMilliseconds();
            timeRegistrationData.startTime = 0;
            timeRegistrationData.finishTime = 0;
            cookaStorage->storeTimeRegistration(timeRegistrationData);
          }

          if(vehicleInput.getText().toInt()>0){
            //add timestring entry to CheckpointInfoCtrl
            String timeString = vehicleInput.getText();
            if(timeString.length()==1) timeString = "00"+timeString;
            else if(timeString.length()==2) timeString = "0"+timeString;
            timeString += " "+cpTimeInput.getText();
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
              commentInput.getText().toCharArray(ckSettings->currentMsg.content,commentInput.getText().length()+1);
              ckSettings->currentMsg.timestamp = ckSettings->lastMessageSentOrReceived;
              checkpointInfoCtrl.setMessage(ckSettings->currentMsg);
          }


          vehicleInput.setText("");
          cpTimeInput.setValue("");
          commentInput.setText("");
          errorLabel.setText("");
          selectedInputInd=-1;
          confirmationDialogWasActivated=false;
          isDirty=true;
          checkpointInfoCtrl.setDirty();
          confirmationDialog.reset();
          return;
        }
      }
    }
  }else{

    if (currentKeyboardChar == '+') {
        selectedInputInd++;
        if (selectedInputInd > 2) {
          selectedInputInd = 0;
        }
      }

      if (currentKeyboardChar == '-') {
        selectedInputInd--;
        if (selectedInputInd < 0) {
          selectedInputInd = 2;
        }
      }

    if (cpTimeInput.hasCursor()) {
      cpTimeInput.processInput(currentKeyboardChar);
    }

    if (commentInput.hasCursor()) {
      commentInput.processInput(currentKeyboardChar);
    }
  }

  if(currentKeyboardChar=='>'){
    if(validateInput()){
      confirmationDialog.drawScreen(tft);
      confirmationDialogWasActivated = true;
      selectedInputInd = 0;
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
      selectedInput = &commentInput;
      ckKeypad.enableAlphaNumerics();
      break;
    }
  }

  selectedInput->setFocus();
}

boolean CheckPointScreen::validateInput() {
 errorLabel.setText(F(""));
 boolean valid = true;

 if(vehicleInput.getText().length() == 0 && cpTimeInput.getText().length() == 0 && commentInput.getText().length()>0){
   return true;
 }
 if (!cpTimeInput.getTime().receivedValidInput() || cpTimeInput.getText().length() < 5) {
    errorLabel.setText(Translator::getCheckpointErrorText());
    valid = false;
  }

  valid &= CheckpointBaseScreen::validateInput();
  return valid;
}
