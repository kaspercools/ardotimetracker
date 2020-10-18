#ifndef CheckPointSelectionScreen_h
#define CheckPointSelectionScreen_h
#include "Screen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "Label.h"

class CheckPointSelectionScreen: public Screen{
public:
    CheckPointSelectionScreen();
    CheckPointSelectionScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    boolean validateInput();

private:
    byte selectedItem;
    byte previouslySelectedItem;
    Enumerations::Language lang;
    NumericInputField checkPointInput;
    Label errorLabel;
};
#endif
