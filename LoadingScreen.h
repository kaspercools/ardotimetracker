#ifndef LoadingScreen_h
#define LoadingScreen_h
#include "Screen.h"

class LoadingScreen: public Screen{
public:
    LoadingScreen();
    LoadingScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    void setLoadingText(String text);
    String getLoadingText();
    void setScreenToBeInvoked(Enumerations::ScreenEnum nxtScrn);
private:
    void drawLogo(Adafruit_TFTLCD tft);
    String loadingText;
};
#endif
