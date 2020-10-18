#include "ConfirmationDialog.h"
#include "Util.h"
#include "Colors.h"
#include "Fonts.h"


ConfirmationDialog::ConfirmationDialog():
Screen(){

  hasFinished = false;
}

ConfirmationDialog::ConfirmationDialog(String _title,int _width, int _height):
Screen(_title,_width,_height){
  setCursorPosition(width,height);
  hasFinished = false;
}

void ConfirmationDialog::drawScreen(Adafruit_TFTLCD tft){
  if(isDirty){
    //draw recht with current rectangle center screen
    setCursorPosition((tft.width()/2-width/2),(tft.height()/1.5));
    tft.fillRect(cursorX,cursorY,width,height,Colors::White);
    tft.drawRect(cursorX,cursorY,width,height,Colors::Orange);
    tft.drawRect(cursorX,cursorY,width+1,height+1,Colors::Orange);
    tft.drawRect(cursorX,cursorY,width-1,height-1,Colors::Orange);

    tft.setTextSize(Fonts::fontSize);
    //if page is 1 then draw language
    tft.setTextColor(Colors::DarkBlue);
    if(hasFinished){
      setCursorPosition(200,tft.height()-150);
      setCursorPosition(cursorX-100,cursorY+65);
      drawLogo(tft);
      setCursorPosition(cursorX+75,cursorY+20);
      tft.setCursor(cursorX,cursorY);
      tft.println(Translator::getMessageSendingText());

    }else{
      setCursorPosition(cursorX+10,cursorY+10);
      tft.setCursor(cursorX,cursorY);
      //calculate font size

      Utils::StringMutators::printWithMargin(Translator::getConfirmationText(),cursorX,cursorY,25,15,width,tft);

      //draw icons on the dialog
      //draw rect for ok button
      String okLabel = Translator::getSendText();
      String cancelLabel = Translator::getCancelText();
      byte okWidth = okLabel.length()*(Fonts::fontWidth)+85;
      byte cancelWidth = cancelLabel.length()*Fonts::fontWidth+85;

      setCursorPosition(((tft.width()/2)-((okWidth+cancelWidth+20)/2)),(tft.height()/1.5)+height-40);

      tft.drawRect(cursorX,cursorY,okWidth,25,Colors::DarkBlue);
      tft.setCursor(cursorX+10,cursorY+5);
      tft.print(okLabel);
      tft.drawRect(cursorX+okWidth+10,cursorY,cancelWidth,25,Colors::DarkBlue);
      tft.setCursor(cursorX+okWidth+20,cursorY+5);
      tft.print(cancelLabel);
    }
  }

  isDirty=false;
}

void ConfirmationDialog::processScreen(Adafruit_TFTLCD tft){
  char key= ckKeypad.processInput();

  if(key =='<'){
      //user cancelled
  }

  if(key =='>'){
      //user said ok
  }
}

bool ConfirmationDialog::setHasFinished(){
  hasFinished=true;
  isDirty=true;
}

void ConfirmationDialog::reset(){
  hasFinished=false;
  isDirty=true;
}

void ConfirmationDialog::drawLogo(Adafruit_TFTLCD tft){
  float size = .2;
  int x = cursorX;
  int y = cursorY;

  tft.fillRoundRect((x), (y), 62*size, 44*size, 13*size, Colors::Orange);

  tft.fillRoundRect(x+(72)*size, y+(33)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);
  tft.fillRoundRect(x-(45)*size, y+(57)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);

  tft.fillRoundRect(x+(92)*size, y+(123)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);
  tft.fillRoundRect(x-(25)*size, y+(186)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);

  tft.fillRoundRect(x+(82)*size, y+(251)*size, 64*size, 44*size, 13*size, Colors::Orange);
}


