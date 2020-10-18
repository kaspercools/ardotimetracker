#ifndef CookaSignalBar_h
#define CookaSignalBar_h
#include "Adafruit_TFTLCD.h"

class CookaSignalBar{
public:
  CookaSignalBar();
  CookaSignalBar(int _x,int _y);
  void draw(Adafruit_TFTLCD tft);

private:
  int x,y;
  int8_t dBm = -999;
};

#endif
