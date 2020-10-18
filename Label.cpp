#include "Label.h"
#include "Colors.h"
#include "Fonts.h"

Label::Label(){
  
}

Label::Label(int _x, int _y, int _width, int _height,byte _radius){
  x=_x;
  y=_y;
  width=_width;
  height=_height;
  radius=_radius;
  isDirty=true;
  maxValueLength=0;
}

void Label::setText(String _text){
  value=_text;
  isDirty=true;
}
String Label::getText(){
  return value;
}

void Label::setMaxValueLength(byte _length){
  maxValueLength=_length;
}

void Label::draw(Adafruit_TFTLCD tft){

  if(isDirty){
    tft.fillRoundRect(x+1,y+1,width-2,height-2,5,Colors::White);
    tft.setCursor(x+5,y+radius);
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::Red);
    tft.print(value);
  } 

  isDirty=false;
}
