#ifndef Structs_cpp
#define Structs_cpp
#include "arduino.h"
#include "Enums.h"


struct Checkpoint{
 byte number;
 char name[16];
 byte type;
};

struct TimeRegistration{
  byte checkpointNumber;
  unsigned int vehicleNumber;
  unsigned long cpTime;
  unsigned long startTime;
  unsigned long finishTime;
};

struct TimesSent {
  char time[17];
  bool success;
};

struct Message{
  char content[71];
  Enumerations::MessageOrigin origin;
  long timestamp;
};

struct Settings{
 byte lang;
 char checkPointSubmissionUrl[56] = "http://localhost:3001/api/timeregistrations";
 char locationSubmissionUrl[40] = "http://localhost:3001/api/locations";
 char checkPointDataUrl[57] = "http://localhost:3001/api/events/active-checkpoints";
 char messageRetrievalUrl[40] = "http://localhost:3001/api/messages";
 char deviceIdUrl[40] = "http://localhost:3001/api/devices/";
 byte currentCheckpoint;
 long lastMessageSentOrReceived = 0;
 char imei[18];
 struct Message currentMsg;
};

struct ChronoData{
  char time[13];
};

#endif
