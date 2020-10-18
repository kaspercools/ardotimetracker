#include "CookaPhone.h"
#include <SoftwareSerial.h>
#include "Enums.h"
#include "Globals.h"
#include "Util.h"
#include "MemoryFree.h"


CookaPhone::CookaPhone() {
  hasGPRS = false;
  networkTimeEnabled = false;
  fonaSS.begin(4800);
  connect();
}

bool CookaPhone::sendData(byte checkpointNumber, int vehicleNumber, unsigned long cpTime, unsigned long startTime, unsigned long finishTime, String comment) {
  bool status = true;

  String data = String(checkpointNumber) + F(";") + ((vehicleNumber==0)?"":String(vehicleNumber)) + F(";");

  char bufCpTime[50];
  ltoa(cpTime, bufCpTime, 16);
  String cpTimeString(cpTime);
  data += cpTimeString + F(";");

  char bufStartTime[50];
  ltoa(startTime, bufStartTime, 16);
  String startTimePtrString(startTime);
  data += startTimePtrString + F(";");

  char bufFinishTime[50];
  ltoa(finishTime, bufFinishTime, 16);
  String finishTimePtrString(finishTime);
  data += finishTimePtrString + F("; ");

  data += comment+F(" ");

  Serial.println(data);

  if (!phoneAvailable) return false;
  uint16_t statuscode;
  int16_t length;
  flushSerial();
  char dataToBeSent[data.length()];
  data.toCharArray(dataToBeSent, data.length());

  if (!fona.HTTP_POST_start(ckSettings->checkPointSubmissionUrl, F("text/plain"), (uint8_t *) &dataToBeSent, strlen(dataToBeSent), &statuscode, (uint16_t *)&length)) {
    return false;
  }

  String responseString;
  while (length > 0) {
    while (fona.available()) {
      char c = fona.read();

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
      UDR0 = c;
#else
      responseString += c;
#endif

      length--;
      if (! length) break;
    }
  }


  if (statuscode == 200) {
    Serial.println(statuscode);
    char responseStringArray[responseString.length()];
    responseString.toCharArray(responseStringArray, responseString.length() + 1);

    ckSettings->currentMsg.origin = Enumerations::Server;
    String partialString = Utils::StringMutators::subStr(responseStringArray, ";", 1);
    partialString.trim();
    if(partialString.length()>0){
      partialString.toCharArray(ckSettings->currentMsg.content, partialString.length()+1);
    }

      partialString = Utils::StringMutators::subStr(responseStringArray, ";", 2);

      char timeStampString[16];
      partialString.toCharArray(timeStampString, 16);

      ckSettings->currentMsg.timestamp = atol(timeStampString);

      ckSettings->lastMessageSentOrReceived = ckSettings->currentMsg.timestamp;

  } else if (statuscode == 404) {
    status = false;
    char responseStringArray[responseString.length()];
    responseString.toCharArray(responseStringArray, responseString.length() + 1);

    String partialString = Utils::StringMutators::subStr(responseStringArray, ";", 1);
    partialString.toCharArray(ckSettings->currentMsg.content, partialString.length());

    ckSettings->currentMsg.origin = Enumerations::Server;

    partialString = Utils::StringMutators::subStr(responseStringArray, ";", 2);
    char timeStampString[16];
    partialString.toCharArray(timeStampString, 16);

    ckSettings->currentMsg.timestamp = atol(timeStampString);
    ckSettings->lastMessageSentOrReceived = ckSettings->currentMsg.timestamp;

  } else if (statuscode == 500) {

  }

  fona.HTTP_POST_end();
  return status;
}

struct Message CookaPhone::checkForNewMessage() {

  struct Message msg;
  String data = String(ckSettings->currentCheckpoint) + F(";") + String(ckSettings->lastMessageSentOrReceived);

  if (!phoneAvailable) return msg;
  uint16_t statuscode;
  int16_t length;

  flushSerial();

  char dataToBeSent[data.length()];
  data.toCharArray(dataToBeSent, data.length());


  if (!fona.HTTP_POST_start(ckSettings->messageRetrievalUrl, F("text/plain"), (uint8_t *) &dataToBeSent, strlen(dataToBeSent), &statuscode, (uint16_t *)&length)) {
    //save data to EEPROM
    return msg;
  }

  String responseString = String();

  while (length > 0) {
    while (fona.available()) {
      char c = fona.read();

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
      UDR0 = c;
#else
      responseString += c;
#endif

      length--;
      if (! length) break;
    }
  }

  char responseStringArray[responseString.length()];
  responseString.toCharArray(responseStringArray, responseString.length() + 1);

  strcpy(msg.content, Utils::StringMutators::subStr(responseStringArray, ";", 1));

  char timestmp[16];
  strcpy(timestmp, Utils::StringMutators::subStr(responseStringArray, ";", 2));
  ckSettings->lastMessageSentOrReceived = atol(timestmp);
  msg.timestamp = ckSettings->lastMessageSentOrReceived;
  msg.origin = Enumerations::ControlCenter;


  fona.HTTP_POST_end();
  return msg;
}


int8_t CookaPhone::getSignalStrength() {
  if (!phoneAvailable) return 0;
  flushSerial();
  uint8_t n = fona.getRSSI();
  int8_t r;

  if (n == 0) r = -115;
  if (n == 1) r = -111;
  if (n == 31) r = -52;
  if ((n >= 2) && (n <= 30)) {
    r = map(n, 2, 30, -110, -54);
  }

  dBm = r;

  return dBm;
}

void CookaPhone::connect() {
  if (!phoneAvailable) return;
  flushSerial();
  //check if fona is responding.
  phoneAvailable=false;
  while(!phoneAvailable){
     phoneAvailable = fona.begin(fonaSS);
     if(!phoneAvailable){
       Serial.println("phone not availabl");
       delay(15000);
     }
  }

  Serial.println(F("Found phone, now what?"));

  uint8_t imeiLen = getIMEI();

  //make sure that we have to correct settings, cfr proximus data network
  fona.setGPRSNetworkSettings(F("internet.proximus.be"));
}

uint8_t CookaPhone::getIMEI(){
  return fona.getIMEI(ckSettings->imei);
}

bool CookaPhone::unlockPhone() {
  flushSerial();
  return true;
}

Enumerations::PhoneStatus CookaPhone::getNetworkStatus() {
  if (!phoneAvailable) return Enumerations::Searching;
  flushSerial();
  uint8_t n = fona.getNetworkStatus();
  networkStatus = (Enumerations::PhoneStatus)n;
}

void CookaPhone::flushSerial() {
  while (Serial.available())
    Serial.read();
}

bool CookaPhone::turnOnGPRS() {
  if (!phoneAvailable) return false;
  if (hasGPRS) {
    return true;
  }

  unlockPhone();
  flushSerial();

  if (getGSMLOC()) {
    hasGPRS = true;
    return hasGPRS;
  }

  flushSerial();
  hasGPRS = fona.enableGPRS(true);

  return hasGPRS;
}

String CookaPhone::getBatteryLevel() {
  String result = F("VPct = ");
  uint16_t vbat;
  if (! fona.getBattPercent(&vbat)) {

  } else {
    result += String(vbat) + "%";
  }

  return result;
}

bool CookaPhone::hasGPRSTurnedOn() {
  if (!phoneAvailable) return false;

  return hasGPRS;
}

bool CookaPhone::getGSMLOC() {
  if (!phoneAvailable) return false;
  flushSerial();
  char replybuffer[255];
  uint16_t returncode;
  //get current phone location
  if (fona.getGSMLoc(&returncode, replybuffer, 250)) {
    //replybuffer contains data
    String location = replybuffer;
    location = String(ckSettings->currentCheckpoint) + "," + location + ',' + String(ckSettings->imei);

    //send data;
    uint16_t statuscode;
    int16_t length;

    flushSerial();

    char dataToBeSent[location.length()+1];
    location.toCharArray(dataToBeSent, location.length()+1);

    if (!fona.HTTP_POST_start(ckSettings->locationSubmissionUrl, F("text/plain"), (uint8_t *) &dataToBeSent, strlen(dataToBeSent), &statuscode, (uint16_t *)&length)) {

      //save data to EEPROM
      return false;
    }

    while (length > 0) {
      while (fona.available()) {
        char c = fona.read();

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
        UDR0 = c;
#else
        Serial.write(c);
#endif

        length--;
        if (! length) break;
      }
    }

    fona.HTTP_POST_end();

  } else {
    return false;
  }

  return (returncode == 0);
}

byte CookaPhone::getDeviceInd(){
  byte ind = 255;

  if (!phoneAvailable) return ind;
  uint16_t statuscode;
  int16_t length;

  flushSerial();
  char bigArray[61];
  bigArray[0] = '\0';
  strcat(bigArray,ckSettings->deviceIdUrl);
  strcat(bigArray,ckSettings->imei);
  if (!fona.HTTP_GET_start(bigArray, &statuscode, (uint16_t *)&length)) {
    //save data to EEPROM
    return ind;
  }

  String responseString = String();

  while (length > 0) {
    while (fona.available()) {
      char c = fona.read();

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
      UDR0 = c;
#else
      responseString += c;
#endif

      length--;
      if (! length) break;
    }
  }

  fona.HTTP_GET_end();
  return responseString.toInt();
}

bool CookaPhone::loadCheckpointData() {
  if (!phoneAvailable) return false;

  uint16_t statuscode;
  int16_t length;
  Checkpoint info;
  int pos=0;
  cookaStorage->clearEEPROM();
  flushSerial();

  if (!fona.HTTP_GET_start(ckSettings->checkPointDataUrl, &statuscode, (uint16_t *)&length)) {
     Serial.println(F("Failed!"));
     return false;
   }

   bool done = false;
   char part[length];
   char c;
   while (length>0 && !done) {
     while (fona.available()) {
       //get the first checkpoint
        part[pos++]=fona.read();
       length--;
       if (! length) break;
     }
   }

   char *p = part;
   pos=0;
   char *str;
   char *subStr;
   while ((str = strtok_r(p, ";", &p)) != NULL) // delimiter is the semicolon
   {
       while ((subStr = strtok_r(str, ",", &str)) != NULL){
         switch(pos++){
           case 0:
             info.number = atoi(subStr);
             break;
           case 1:
             strcpy(info.name,subStr);
             break;
           case 2:
             info.type = atoi(subStr);
             cookaStorage->storeCheckpointInfo(info);
             pos=0;
           break;
       }
     }
   }

  return true;
}

bool CookaPhone::enableNetworkTime() {
  flushSerial();
  if (!networkTimeEnabled && fona.enableNetworkTimeSync(true)) {
    networkTimeEnabled = true;
  }

  return networkTimeEnabled;
}

CookaTime CookaPhone::getTime() {
  flushSerial();
  CookaTime currentTime = CookaTime();
  if (enableNetworkTime() && networkTimeEnabled) {
    char buffer[23];
    fona.getTime(buffer, 23);  // make sure replybuffer is at least 23 bytes!
    String time = String(buffer).substring(10, 18);

    currentTime.setTimeFromString(time);
    currentTime.setSeconds(0);
  }

  return currentTime;
}


