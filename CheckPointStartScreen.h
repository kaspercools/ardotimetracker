#ifndef CheckPointStartScreen_h
#define CheckPointStartScreen_h
#include "CheckpointBaseScreen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "TextInputField.h"
#include "TimeInputField.h"
#include "Label.h"

class CheckPointStartScreen: public CheckpointBaseScreen{
public:
    CheckPointStartScreen();
    CheckPointStartScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    virtual boolean validateInput();
private:
    Enumerations::Language lang;
    TimeInputField cpTimeInput;
    TimeInputField startTimeInput;
    InputField inputArr[4];
};
#endif
