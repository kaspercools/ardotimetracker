#ifndef Enums_h
#define Enums_h

namespace Enumerations{
	typedef enum ScreenEnum {
		LanguageScreen=1,
		CheckPointSelectionScreen,
		CheckPointScreen,
		CheckPointStartScreen,
		FlyingFinishScreen,
		FlyingStartScreen,
		LoadingScreen,
                DeviceScreen,
		NoScreen
	};
	
	
	typedef enum Language {
		Dutch,
		French,
		English
	};

	typedef enum PhoneStatus{
		NotRegistered,
		RegisteredHome,
		Searching,
		Denied,
		Unknown,
		RegisteredRoaming
	};
      
        typedef enum MessageOrigin{
          User,
          Server,
          ControlCenter
        };

}
#endif

