#ifndef FlyingFinishScreen_h
#define FlyingFinishScreen_h
#include "CheckpointBaseScreen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "TextInputField.h"
#include "TimeInputField.h"
#include "Label.h"

class FlyingFinishScreen: public CheckpointBaseScreen{
public:
    FlyingFinishScreen();
    FlyingFinishScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    virtual void processTagHeuerData();
    bool validateInput();
    void redrawChronoIcon(Adafruit_TFTLCD tft);
protected:
    TimeInputField flyingFinishTimeInput;
    InputField inputArr[3];
    bool confirmationDialogWasActivated = false;
    unsigned long chronoTimer;
    unsigned long chronoTimerInterval = 2.0 * 1000000UL;
    bool holdChronoSwitch = false;
};
#endif
