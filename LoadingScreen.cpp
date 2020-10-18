#include "LoadingScreen.h"
#include "Fonts.h"
#include "Util.h"
#include "Colors.h"

LoadingScreen::LoadingScreen(){
  
}

LoadingScreen::LoadingScreen(String _title,int _width, int _height){
  isDirty=true;
}

void LoadingScreen::drawScreen(Adafruit_TFTLCD tft){
  if(isDirty){
    tft.fillScreen(Colors::White);
    drawLogo(tft);
    tft.setCursor(tft.width()/2-60,tft.height()-170);
    tft.setTextSize(Fonts::fontSize);
    tft.setTextColor(Colors::Black);

    Utils::StringMutators::printWithMargin(loadingText,tft.width()/2-60,tft.height()-170,16,5,300,tft);
  }
  
  isDirty=false;
  
}

void LoadingScreen::processScreen(Adafruit_TFTLCD tft){
  
}

void LoadingScreen::drawLogo(Adafruit_TFTLCD tft){
  float size = .6;
  int x = tft.width()/2-135;
  int y = tft.height()/2-(90 * size);

  tft.fillRoundRect((x)*size, (y)*size, 62*size, 44*size, 13*size, Colors::Orange);
  
  tft.fillRoundRect((x+72)*size, (y+33)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);
  tft.fillRoundRect((x-45)*size, (y+57)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);
  
  tft.fillRoundRect((x+92)*size, (y+123)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);  
  tft.fillRoundRect((x-25)*size, (y+186)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);
  
  tft.fillRoundRect((x+82)*size, (y+251)*size, 64*size, 44*size, 13*size, Colors::Orange);
}

void LoadingScreen::setLoadingText(String text){
  loadingText = text;
  isDirty=true;
}

String LoadingScreen::getLoadingText(){
  return loadingText;
}

void LoadingScreen::setScreenToBeInvoked(Enumerations::ScreenEnum nxtScrn){
  nextScreen = nxtScrn;
}
