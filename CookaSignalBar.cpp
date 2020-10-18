#include "CookaSignalBar.h"
#include "CookaPhone.h"
#include "Colors.h"

CookaSignalBar::CookaSignalBar(){

}

CookaSignalBar::CookaSignalBar(int _x,int _y){
  x = _x;
  y = _y;
}

void CookaSignalBar::draw(Adafruit_TFTLCD tft){
  dBm = cookaPhone->getSignalStrength();
  byte barWidth = 6;
  byte barHeight = 20;
  byte margin = 2;

  if(dBm >= -100){
    tft.fillRect(x,y-barHeight/5,barWidth, (barHeight/5),Colors::Orange);
  }

  if(dBm >= -99){
   tft.fillRect(x+(barWidth+margin),y-(barHeight/5*2),barWidth, (barHeight/5*2),Colors::Orange);
  }

  if(dBm >= -89){
   tft.fillRect(x+(barWidth*2+margin*2),y-(barHeight/5*3),barWidth, (barHeight/5*3),Colors::Orange);
  }

  if(dBm >= -84){
   tft.fillRect(x+(barWidth*3+margin*3),y-(barHeight/5*4),barWidth, (barHeight/5*4),Colors::Orange);
  }

  if(dBm >= -79){
   tft.fillRect(x+(barWidth*4+margin*4),y-(barHeight/5*5),barWidth, (barHeight/5*5),Colors::Orange);
  }
}
