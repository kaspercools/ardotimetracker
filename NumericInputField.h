#ifndef NumericInputField_h
#define NumericInputField_h
#include "InputField.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"

class NumericInputField: public InputField {

public:
	NumericInputField();
	NumericInputField(int _x, int _y, int _width, int _height,byte _radius);
	virtual void processInput(char key);
	int getValue();
private:
	
};
#endif
