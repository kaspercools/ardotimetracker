#ifndef Util_h
#define Util_h
#include "arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"

namespace Utils{
	
	class StringMutators{
	public:
		static byte printWithMargin(String text,int xOrigin,int yOrigin, byte lineHeight, byte margin,int maxWidth,Adafruit_TFTLCD tft);
                static char* subStr (char* input_string, char *separator, byte segment_number);
	};
}
#endif



