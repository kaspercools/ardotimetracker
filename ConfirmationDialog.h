#ifndef ConfirmationDialog_h
#define ConfirmationDialog_h
#include "Screen.h"

class ConfirmationDialog:Screen{
public:
	ConfirmationDialog();
	ConfirmationDialog(String _title,int _width, int _height);
	virtual void drawScreen(Adafruit_TFTLCD tft);
	virtual void processScreen(Adafruit_TFTLCD tft);
        bool setHasFinished();
        void reset();
        
private:
	bool hasFinished;
        void drawLogo(Adafruit_TFTLCD tft);
};

#endif
