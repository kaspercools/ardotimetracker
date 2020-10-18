#ifndef LanugageScreen_h
#define LanugageScreen_h

#include "Screen.h"

class LanguageScreen: public Screen{
public:
    LanguageScreen();
    LanguageScreen(String _title,int width,int height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    void drawSelectionArrow(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);

private:
    byte selectedItem;
    byte previouslySelectedItem;
    Enumerations::Language lang;
    bool getData=false;
};

#endif
