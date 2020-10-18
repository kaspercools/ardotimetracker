#ifndef DeviceScreen_h
#define DeviceScreen_h

#include "Screen.h"
#include "Globals.h"

class DeviceScreen: public Screen{
public:
    DeviceScreen();
    DeviceScreen(String _title,int width,int height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
};

#endif
