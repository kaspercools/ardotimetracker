#ifndef Alphanumeric_h
#define Alphanumeric_h
#include "arduino.h";
#include "Keypad.h"

class AlphanumericKeypad{
public:
	AlphanumericKeypad();
	char processInput();
	char getKey();
	KeyState getState();
	void enableAlphaNumerics();
	void disableAlphaNumerics();
private:
	boolean proccessAlphanumerics;
};
#endif
