#include "ScreenFactory.h"
#include "Globals.h"
#include "CookaStorage.h"
#include "Translator.h"

ScreenFactory::ScreenFactory(){

}

InfoScreen ScreenFactory::createInfoScreen(int width, int height){
  //change settings depending on the language we selected previously

  InfoScreen result = InfoScreen("Basic key info",width,height);

  return result;
}

LanguageScreen ScreenFactory::createLanguageScreen(int width, int height){
  //change settings depending on the language we selected previously

  LanguageScreen result = LanguageScreen("Select your language",width,height);

  return result;
}


CheckPointScreen ScreenFactory::createCheckPointScreen(int width, int height){
  //change settings depending on the language we selected previously

  CheckPointScreen result = CheckPointScreen(getCheckpointTitle(),width,height);

  return result;
}

CheckPointSelectionScreen ScreenFactory::createCheckPointSelectionScreen(int width, int height){
  //change settings depending on the language we selected previously
  CheckPointSelectionScreen result = CheckPointSelectionScreen(Translator::getCheckpointSelectionTitle(),width,height);

  return result;
}

CheckPointStartScreen ScreenFactory::createCheckPointStartScreen(int width, int height){
	//change settings depending on the language we selected previously
  CheckPointStartScreen result = CheckPointStartScreen(getCheckpointTitle(),width,height);

  return result;
}

FlyingFinishScreen ScreenFactory::createFlyingFinishScreen(int width, int height){
	//change settings depending on the language we selected previously
  FlyingFinishScreen result = FlyingFinishScreen(getCheckpointTitle(),width,height);

  return result;
}

FlyingStartScreen ScreenFactory::createFlyingStartScreen(int width, int height){
	//change settings depending on the language we selected previously
  FlyingStartScreen result = FlyingStartScreen(getCheckpointTitle(),width,height);

  return result;
}

DeviceScreen ScreenFactory::createDeviceScreen(int width, int height){
	//change settings depending on the language we selected previously
  DeviceScreen result = DeviceScreen("Device info",width,height);

  return result;
}


ShakedownScreen ScreenFactory::createShakedownScreen(int width, int height){
	//change settings depending on the language we selected previously
  ShakedownScreen result = ShakedownScreen(getCheckpointTitle(),width,height);

  return result;
}

String ScreenFactory::getCheckpointTitle(){
  String title = "Unknown checkpoint";
  struct Checkpoint info;

  if(ckSettings->currentCheckpoint!=-99){

    info = cookaStorage->getCheckpointInfo(ckSettings->currentCheckpoint);


    title=((String(info.number).length()==1)?"0"+String(info.number):String(info.number)) + " - " + info.name;
  }

  return title;
}
