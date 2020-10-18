#ifndef Label_h
#define Label_h
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"


class Label{

public:
    Label();
    Label(int _x, int _y, int _width, int _height,byte _radius);
    void draw(Adafruit_TFTLCD tft);
    void setText(String _text);
    String getText();
    void setMaxValueLength(byte _length);
    
protected:
    String value;
    boolean isDirty;
    int x,y;
    int width,height;
    byte radius;
    byte maxValueLength;
};
#endif
