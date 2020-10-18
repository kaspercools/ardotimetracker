#ifndef ScreenFactory_h
#define ScreenFactory_h
#include "Screen.h"
#include "LanguageScreen.h"
#include "CheckPointScreen.h"
#include "CheckPointSelectionScreen.h"
#include "CheckPointStartScreen.h"
#include "FlyingStartScreen.h"
#include "FlyingFinishScreen.h"
#include "ShakedownScreen.h"
#include "DeviceScreen.h"
#include "InfoScreen.h"

class ScreenFactory{
public:
	ScreenFactory();
	LanguageScreen createLanguageScreen(int width, int height);
	CheckPointSelectionScreen createCheckPointSelectionScreen(int width, int height);
	CheckPointScreen createCheckPointScreen(int width, int height);
	CheckPointStartScreen createCheckPointStartScreen(int width, int height);
	FlyingFinishScreen createFlyingFinishScreen(int width, int height);
	FlyingStartScreen createFlyingStartScreen(int width, int height);
	ShakedownScreen createShakedownScreen(int width, int height);
	DeviceScreen createDeviceScreen(int width, int height);
        InfoScreen createInfoScreen(int width, int height);
private:
	String getCheckpointTitle();
};

#endif

