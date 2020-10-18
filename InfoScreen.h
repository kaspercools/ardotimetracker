#ifndef InfoScreen_h
#define InfoScreen_h

#include "Screen.h"
#include "Globals.h"

class InfoScreen: public Screen{
public:
    InfoScreen();
    InfoScreen(String _title,int width,int height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
};

#endif
