#ifndef TimeInputField_h
#define TimeInputField_h
#include "InputField.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "CookaTime.h"


class TimeInputField: public InputField {

public:
    TimeInputField();
    TimeInputField(int _x, int _y, int _width, int _height,byte _radius);
    virtual void processInput(char key);
    void setValue(String time);
    CookaTime getTime();
    bool enableDetails();
private:
    CookaTime currentTime;
    bool  hasDetails = false;
};
#endif
