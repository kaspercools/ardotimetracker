#include "InputField.h"
#include "Colors.h"
#include "Fonts.h"
#include "Util.h"

InputField::InputField(){

}

InputField::InputField(int _x, int _y, int _width, int _height,byte _radius){
  ckKeypad = AlphanumericKeypad();
  x=_x;
  y=_y;
  width=_width;
  height=_height;
  isDirty=true;
  isCursorEnabled=true;
  radius=_radius;

  cursorX = x+radius;
  cursorY=y+(radius);
}

void InputField::setText(String _text){
  if(maxValueLength==0 || _text.length()<=maxValueLength){
    value=_text;
    isDirty=true;
  }
}
String InputField::getText(){
  return value;
}

void InputField::setMaxValueLength(byte _length){
  maxValueLength=_length;
}

void InputField::draw(Adafruit_TFTLCD tft){

  if(isDirty){

    tft.fillRoundRect(x,y,width,height,radius,Colors::White);
    tft.drawRoundRect(x,y,width,height,radius,Colors::LightGray);
    tft.setCursor(cursorX,y+radius);
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::DarkBlue);
    numberOfLines = Utils::StringMutators::printWithMargin(value,cursorX,cursorY,16,0,width-(radius),tft);
  }

  if(hasFocus && blinkEnabled){
    tft.drawRoundRect(x,y,width,height,radius,Colors::Orange);
    blinkCursor(tft);
  }else if(hasFocus){
    showCursor(tft);
  }else{
    tft.drawRoundRect(x,y,width,height,radius,Colors::LightGray);
  }

  isDirty=false;
}

void InputField::setDirty(){
  isDirty=true;
}

void InputField::setCursorPosition(int x, int y){
  cursorX = x;
  cursorY = y;
}

void InputField::showCursor(Adafruit_TFTLCD tft){
  //move to position based on current value
  byte maxCharsPerLine = ((width)/(Fonts::fontWidth*Fonts::fontSize));

  int shiftX = (((value.length()-(numberOfLines*(maxCharsPerLine-5))))*(Fonts::fontSize*(Fonts::fontWidth)));

  //cursor is 2 px wide and 5 px high
  tft.fillRect(cursorX+shiftX,cursorY+(25*numberOfLines),2,15,Colors::Orange);
}

void InputField::noCursor(Adafruit_TFTLCD tft){

  //move to position based on current value
  byte maxCharsPerLine = ((width)/(Fonts::fontWidth*Fonts::fontSize));
  int shiftX = (((value.length()-(numberOfLines*(maxCharsPerLine-5))))*(Fonts::fontSize*(Fonts::fontWidth)));

  tft.fillRect(cursorX+shiftX,cursorY+(25*numberOfLines),2,15,Colors::White);
  tft.drawRoundRect(x,y,width,height,radius,Colors::LightGray);
}

void InputField::blinkCursor(Adafruit_TFTLCD tft){
  //blink rate
  byte blink = millis() / 500;

  if ( blink % 2 ) {
    showCursor(tft);
  }
  else {
    noCursor(tft);
  }
}

void InputField::setCursorEnabled(boolean enableCursor){
  isCursorEnabled=enableCursor;
}

boolean InputField::hasCursor(){
  //check if the inputfield is being focussed at this moment
  //make sure that the cursor is set within the margins of this field
  return hasFocus;
}

void InputField::processInput(char key){

}

void InputField::setFocus(){
  hasFocus=true;
}

void InputField::removeFocus(){
  hasFocus=false;
}
