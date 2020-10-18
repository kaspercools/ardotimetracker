#include "TimeInputField.h"
#include "Colors.h"
#include "Fonts.h"
#include "Keypad.h"

TimeInputField::TimeInputField():InputField(){
  currentTime = CookaTime();
}

TimeInputField::TimeInputField(int _x, int _y, int _width, int _height,byte _radius)
:InputField(_x,  _y,  _width,  _height, _radius){
  currentTime = CookaTime();
  hasDetails = false;
}

bool TimeInputField::enableDetails(){
  hasDetails=true;
}

void TimeInputField::setValue(String time){

  currentTime.setTimeFromString(time);

  setText(time);
}

void TimeInputField::processInput(char key){
  InputField::processInput(key);
  String val="";
  byte valLength=0;

  if(key != NO_KEY){
    switch(key){
      case '<':
      val = getText();
      setValue(val.substring(0,val.length()-1));
      break;
      case '0'...'9':

      val = getText();
      if((!hasDetails && val.length()<5) || hasDetails){

        if(val.length() == 2 || (val.length() == 5 && hasDetails)){
          val+=F(":");
        }

        if(val.length() == 8){
          val+=F(".");
        }

        val+=key;
        valLength=val.length();
        setValue(val);
      }
      break;
    }
  }
}

CookaTime TimeInputField::getTime(){
  return currentTime;
}
