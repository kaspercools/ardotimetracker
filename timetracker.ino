#include <EEPROM.h>
#include <AltSoftSerial.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "CookaPhone.h"
#include "Keypad.h"
#include "Colors.h"
#include "Screen.h"
#include "ScreenFactory.h"
#include "Enums.h"
#include "MemoryFree.h"
#include "Globals.h"
#include "TagHeuer.h"f
#include "LoadingScreen.h"
#include "DeviceScreen.h"
#include "InfoScreen.h"


//LCD inits
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

//app inits
Settings* ckSettings = new Settings();
CookaPhone* cookaPhone;
CookaStorage* cookaStorage;

//create the TFTLCD instancem
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//def of screen factory
ScreenFactory* screenFactory = new ScreenFactory();
//screen itself
Screen* currentScreen;
//definition of available screens for temporary reference
LanguageScreen languageScreen;
CheckPointScreen checkpointScreen;
CheckPointSelectionScreen checkpointSelectionScreen;
CheckPointStartScreen checkpointStartScreen;
FlyingFinishScreen flyingFinishScreen;
FlyingStartScreen flyingStartScreen;
DeviceScreen deviceScreen;
LoadingScreen loadingScreen;
InfoScreen infoScreen;
TagHeuer *chrono;

void setup(){

//  ckSettings->currentMsg.origin = Enumerations::User;
  Serial.begin(9600);

  //init screen
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(Colors::White);
  tft.setRotation(1);
  //draw logo while booting
  drawLogo();

  loadingScreen = LoadingScreen(F("loadingscreen"),tft.width(),tft.height());
  loadingScreen.setLoadingText(F("Initialising phone.."));

  currentScreen = &loadingScreen;
  ckSettings->lang=-99;
  //init phone
  Serial.println(F("init phone"));
  cookaPhone = new CookaPhone();

  cookaStorage = new CookaStorage();

  chrono = new TagHeuer();
}

bool phoneUnlocked=false;

void loop(){
  if(currentScreen->isChronoEnabled()){
    chrono->readData();
    currentScreen->processTagHeuerData();
  }

  if(currentScreen->isFinished()){

    Enumerations::ScreenEnum nextScreen = currentScreen->getScreenToBeInvoked();
    switch(nextScreen){
      case Enumerations::LanguageScreen:
      currentScreen=NULL;
      languageScreen = screenFactory->createLanguageScreen(tft.width(),tft.height());
      currentScreen = &languageScreen;
      break;
      case Enumerations::CheckPointSelectionScreen:
      currentScreen=NULL;
      checkpointSelectionScreen = screenFactory->createCheckPointSelectionScreen(tft.width(),tft.height());
      currentScreen = &checkpointSelectionScreen;
      break;
      case Enumerations::CheckPointScreen:
      currentScreen=NULL;
      checkpointScreen = screenFactory->createCheckPointScreen(tft.width(),tft.height());
      currentScreen = &checkpointScreen;
      break;
      case Enumerations::CheckPointStartScreen:
      currentScreen=NULL;
      checkpointStartScreen = screenFactory->createCheckPointStartScreen(tft.width(),tft.height());
      currentScreen = &checkpointStartScreen;
      break;
      case Enumerations::FlyingFinishScreen:
      currentScreen=NULL;
      flyingFinishScreen = screenFactory->createFlyingFinishScreen(tft.width(),tft.height());
      currentScreen = &flyingFinishScreen;
      break;
      case Enumerations::DeviceScreen:
      currentScreen=NULL;
      deviceScreen = screenFactory->createDeviceScreen(tft.width(),tft.height());
      currentScreen = &deviceScreen;
      break;
      case Enumerations::FlyingStartScreen:
      currentScreen=NULL;
      flyingStartScreen = screenFactory->createFlyingStartScreen(tft.width(),tft.height());
      currentScreen = &flyingStartScreen;
      break;
    }
  }

  currentScreen->processScreen(tft);
  currentScreen->drawScreen(tft);

  if(!cookaPhone->hasGPRSTurnedOn()){
    if(cookaPhone->turnOnGPRS()){
      cookaPhone->enableNetworkTime();
      if(cookaStorage->getNumberOfStoredItems()>0){

        loadingScreen.setLoadingText(F("Resending time entries..."));
        loadingScreen.drawScreen(tft);

        struct TimeRegistration datas[cookaStorage->getNumberOfStoredItems()];
        //first get the data
        for(byte i = 0 ;i<cookaStorage->getNumberOfStoredItems();i++){
          datas[i] = cookaStorage->getTimeRegistration(i);
        }
        cookaStorage->clearTimeRegEEPROM();
        bool failed = false;
        byte numberEntriesSent = 0;
        for(byte j = 0;j<cookaStorage->getNumberOfStoredItems();j++){
          bool hasBeenSent = cookaPhone->sendData(
                                      datas[j].checkpointNumber,
                                      datas[j].vehicleNumber,
                                      datas[j].cpTime,
                                      datas[j].startTime,
                                      datas[j].finishTime,
                                      String());

          if(!hasBeenSent){
            cookaStorage->storeTimeRegistration(datas[j]);
            failed=true;
          }else{
            numberEntriesSent++;
            loadingScreen.setLoadingText(String(numberEntriesSent) + '/' +cookaStorage->getNumberOfStoredItems() + F(" entries have been sent"));
            loadingScreen.drawScreen(tft);
          }
        }

        loadingScreen.setLoadingText(String(numberEntriesSent) + F(" entries have been sent"));
        loadingScreen.drawScreen(tft);
      }
      currentScreen=NULL;

      infoScreen = screenFactory->createInfoScreen(tft.width(),tft.height());
      currentScreen = &infoScreen;
    }
  }


}

void drawLogo(){
  float size = .8;
  byte x = tft.width()/2-37;
  byte y = tft.height()/2-(147.5 * size);

  tft.fillRoundRect((x)*size, (y)*size, 62*size, 44*size, 13*size, Colors::Orange);

  tft.fillRoundRect((x+72)*size, (y+33)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);
  tft.fillRoundRect((x-45)*size, (y+57)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);

  tft.fillRoundRect((x+92)*size, (y+123)*size, 92*size, 117*size, 10*size, Colors::DarkBlue);
  tft.fillRoundRect((x-25)*size, (y+186)*size, 95*size, 75*size, 10*size, Colors::DarkBlue);

  tft.fillRoundRect((x+82)*size, (y+251)*size, 64*size, 44*size, 13*size, Colors::Orange);
}
