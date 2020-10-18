#ifndef CookaStorage_h
#define CookaStorage_h
#include "structs.cpp"
#include <EEPROM.h>

#define TIMEREGDATAIND 2000
#define MAXTIMEREGDATA 15

#define CHRONODATAINPUTIND 1800

class CookaStorage{
public:
	CookaStorage();
	struct Checkpoint getCheckpointInfo(byte number);
	bool storeCheckpointInfo(struct Checkpoint checkpointData);
	void clearEEPROM();
        void clearTimeRegEEPROM();
        void clearChronoDataEEPROM();
	bool activateTimeRegistrationStorage();
	bool storeTimeRegistration(struct TimeRegistration timeRegistrationData);
        bool storeChronoData(struct ChronoData chronoData);
        struct ChronoData readNextChronoValue();
        struct TimeRegistration getTimeRegistration(byte index);
        byte getNumberOfStoredItems();
private:
	byte tmpCheckpointStorageIndex = 0;
        byte tmpChronoDataStorageIndex = 0;
};

extern CookaStorage* cookaStorage;
#endif
