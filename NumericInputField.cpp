#include "NumericInputField.h"
#include "Colors.h"
#include "Fonts.h"
#include "Keypad.h"

NumericInputField::NumericInputField():InputField(){
  
}

NumericInputField::NumericInputField(int _x, int _y, int _width, int _height,byte _radius)
:InputField(_x,  _y,  _width,  _height, _radius){

}

void NumericInputField::processInput(char key){
  InputField::processInput(key);
  String val="";
  if(key != NO_KEY){
    switch(key){
      case '<':
      val = getText();
      setText(val.substring(0,val.length()-1));
      break;
      case '0'...'9':
      val = getText();
      val+=key;
      setText(val);
      break;
    }
  }
}

int NumericInputField::getValue(){
  return getText().toInt();
}
