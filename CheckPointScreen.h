#ifndef CheckPointScreen_h
#define CheckPointScreen_h
#include "CheckpointBaseScreen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "TextInputField.h"
#include "TimeInputField.h"
#include "Label.h"

class CheckPointScreen: public CheckpointBaseScreen{
public:
    CheckPointScreen();
    CheckPointScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    boolean validateInput();
private:
    TimeInputField cpTimeInput;
    TextInputField commentInput;
    
    InputField inputArr[3];
};
#endif
