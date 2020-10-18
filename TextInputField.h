#ifndef TextInputField_h
#define TextInputField_h
#include "InputField.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"

class TextInputField: public InputField {

public:
	TextInputField();
	TextInputField(int _x, int _y, int _width, int _height,byte _radius);
	virtual void processInput(char key);
	virtual void showCursor(Adafruit_TFTLCD tft);
private:
	
};
#endif
