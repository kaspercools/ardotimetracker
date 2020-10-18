#ifndef Screen_h
#define Screen_h
#include "Arduino.h"
#include "Enums.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "Keypad.h"
#include "AlphanumericKeypad.h"
#include "InputValidation.h"
#include "CookaSignalBar.h"
#include "CookaTime.h"
#include "Translator.h"

class Screen{
public:
    Screen();
    Screen(String _title,int _width,int _height);
    void setTitle(String _title);
    void setIsDirty();
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    virtual void processTagHeuerData();
    void setCursorPosition(int x, int y);
    void showCursor(Adafruit_TFTLCD tft);
    void noCursor(Adafruit_TFTLCD tft);
    void blinkCursor(Adafruit_TFTLCD tft);
    void setCursorEnabled(boolean enableCursor);
    boolean isFinished();
    Enumerations::ScreenEnum getScreenToBeInvoked();
    boolean isScreenDirty();
    void drawClock(Adafruit_TFTLCD tft);
    bool isChronoEnabled();
protected:
    boolean blinkEnabled=true;
    String title;
    boolean isDirty;
    static const byte TITLE_FONT_SIZE = 3;
    int cursorX;
    int cursorY;
    boolean isCursorEnabled;
    boolean hasFinished;
    Enumerations::ScreenEnum nextScreen;
    AlphanumericKeypad ckKeypad;
    unsigned long timer, interval = 2.0 * 1000000UL;
    boolean goBack=false;
    int width,height;
    InputValidation inputValidator;
    CookaSignalBar cookaSignalBar;
    long clockTimer;
    long clockInterval = 1.0 * 1000000UL;
    CookaTime currentTime;
    bool _isChronoEnabled;
};
#endif
