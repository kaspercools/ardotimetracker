#ifndef FlyingStartScreen_h
#define FlyingStartScreen_h
#include "CheckpointBaseScreen.h"
#include "InputField.h"
#include "NumericInputField.h"
#include "TextInputField.h"
#include "TimeInputField.h"

class FlyingStartScreen: public CheckpointBaseScreen{
public:
    FlyingStartScreen();
    FlyingStartScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    virtual void processTagHeuerData();
    void redrawChronoIcon(Adafruit_TFTLCD tft);
    boolean validateInput();
private:
    TimeInputField flyingStartTimeInput;
    InputField inputArr[3];
    unsigned long chronoTimer;
    unsigned long chronoTimerInterval = 2.0 * 1000000UL;
    bool holdChronoSwitch = false;
};
#endif
