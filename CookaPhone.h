#ifndef CookaPhone_h
#define CookaPhone_h
#include "arduino.h"
#include "Adafruit_FONA.h"
#include "Enums.h"
#include <SoftwareSerial.h>
#include "CookaStorage.h"
#include "CookaTime.h"

#define FONA_RX 2
#define FONA_TX 10
#define FONA_RST 4


class CookaPhone{
public:
	CookaPhone();
	int8_t getSignalStrength();
	bool sendData(byte checkpointNumber, int vehicleNumber, unsigned long cpTime,unsigned long startTime,unsigned long finishTime, String comment);
	bool loadCheckpointData();
	bool turnOnGPRS();
	bool hasGPRSTurnedOn();
	bool getGSMLOC();
	bool unlockPhone();
        byte getDeviceInd();
        uint8_t getIMEI();
        struct Message checkForNewMessage();
	Enumerations::PhoneStatus getNetworkStatus();
        String getBatteryLevel();
        bool enableNetworkTime();
        CookaTime getTime();
private:
	void flushSerial();
	void connect();
        bool networkTimeEnabled;
	SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
	Enumerations::PhoneStatus networkStatus;
	bool hasGPRS;
	bool phoneAvailable = true;
	Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
	int8_t dBm;
};

extern CookaPhone* cookaPhone;
#endif


