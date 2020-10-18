
#ifndef ShakedownScreen_h
#define ShakedownScreen_h
#include "Screen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "TextInputField.h"
#include "TimeInputField.h"
#include "Label.h"

class ShakedownScreen: public Screen{
public:
    ShakedownScreen();
    ShakedownScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    boolean validateInput();
private:
    int selectedInputInd=-1;
    NumericInputField vehicleInput;
    TimeInputField cpTimeInput;
    TextInputField commentInput;
    Label errorLabel;
    InputField* selectedInput;
    InputField inputArr[3];
};
#endif
