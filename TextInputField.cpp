#include "TextInputField.h"
#include "Colors.h"
#include "Fonts.h"
#include "Keypad.h"


TextInputField::TextInputField():InputField(){
  isDirty=true;
}

TextInputField::TextInputField(int _x, int _y, int _width, int _height,byte _radius)
:InputField(_x,  _y,  _width,  _height, _radius){
  blinkEnabled = false;
  isDirty=true;
}

void TextInputField::processInput(char key){
  InputField::processInput(key);
  String val="";

  if(key != NO_KEY){
    switch(key){
      case '<':
      val = getText();
      setText(val.substring(0,val.length()-1));
      break;
      case '-':
      case '+':
      case '>':
      case '#':
      case '*':
      break;
      default:
      val = getText();
      val+=key;
      setText(val);
      break;
    }
  }
}


void TextInputField::showCursor(Adafruit_TFTLCD tft){

  tft.drawRoundRect(x,y,width,height,radius,Colors::Orange);


}
