#ifndef CheckpointInfoControl_h
#define CheckpointInfoControl_h
#include "Adafruit_TFTLCD.h"
#include "structs.cpp"
#include "Translator.h"

class CheckpointInfoControl{
public:
  CheckpointInfoControl();
  CheckpointInfoControl(int originX,int originY);
  CheckpointInfoControl(int originX,int originY,int width, int height);
  void addTime(struct TimesSent timeSent);
  void draw(Adafruit_TFTLCD tft);
  void setDirty();
  void setMessage(struct Message msg);
private:
  int width;
  int height;
  int originX;
  int originY;
  bool isDirty;
  struct TimesSent timeStringsSent[6];
  int timeStringsSentIndex = 0;
  struct Message msg;
};
#endif
