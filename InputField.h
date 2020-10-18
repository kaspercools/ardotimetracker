#ifndef InputField_h
#define InputField_h
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "AlphanumericKeypad.h"


class InputField{

public:
    InputField();
    InputField(int _x, int _y, int _width, int _height,byte _radius);
    void draw(Adafruit_TFTLCD tft);
    void setCursorPosition(int x, int y);
    virtual void showCursor(Adafruit_TFTLCD tft);
    void noCursor(Adafruit_TFTLCD tft);
    void blinkCursor(Adafruit_TFTLCD tft);
    void setCursorEnabled(boolean enableCursor);
    void setText(String _text);
    String getText();
    void setMaxValueLength(byte _length);
    boolean hasCursor();
    virtual void processInput(char key);
    void setFocus();
    void removeFocus();
    void setDirty();

protected:
    boolean blinkEnabled = true;
    String value;
    boolean isDirty;
    int x,y;
    int width,height;
    byte radius;
    boolean isCursorEnabled;
    boolean hasDetails = false;
    int cursorX;
    int cursorY;
    byte maxValueLength;
    AlphanumericKeypad ckKeypad;
    boolean hasFocus = false;
    byte numberOfLines=0;
};
#endif
