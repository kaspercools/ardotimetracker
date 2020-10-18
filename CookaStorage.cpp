#include "CookaStorage.h"

CookaStorage::CookaStorage(){
  tmpCheckpointStorageIndex = 0;

  tmpChronoDataStorageIndex = 0;

  activateTimeRegistrationStorage();
}

void CookaStorage::clearChronoDataEEPROM(){
  for (int i = CHRONODATAINPUTIND; i < TIMEREGDATAIND - 1 ; i++){
    EEPROM.write(i, 0);
  }
}

void CookaStorage::clearEEPROM(){

  for (int i = 0; i < 4000; i++){
    EEPROM.write(i, 0);
  }
}

void CookaStorage::clearTimeRegEEPROM(){

  for (int i = TIMEREGDATAIND; i < TIMEREGDATAIND+2000; i++){
    EEPROM.write(i, 0);
  }
}

struct Checkpoint CookaStorage::getCheckpointInfo(byte number){
  struct Checkpoint checkpointData;

  eeprom_read_block(&checkpointData, (void *)((number-1) * sizeof(checkpointData)), sizeof(checkpointData));    // read 'em back

  return checkpointData;
}

bool CookaStorage::storeCheckpointInfo(struct Checkpoint checkpointData){
  eeprom_write_block(&checkpointData, (void *)((checkpointData.number-1) * sizeof(checkpointData)), sizeof(checkpointData));
}

bool CookaStorage::storeTimeRegistration(struct TimeRegistration timeRegistrationData){

  eeprom_write_block(&timeRegistrationData, (void *)(TIMEREGDATAIND+(tmpCheckpointStorageIndex * sizeof(timeRegistrationData))), sizeof(timeRegistrationData));

  if(tmpChronoDataStorageIndex<120){
    tmpCheckpointStorageIndex++;
  }else{
    tmpCheckpointStorageIndex = 0;
  }
}

struct TimeRegistration CookaStorage::getTimeRegistration(byte index){
  struct TimeRegistration timeRegistrationData;

  eeprom_read_block(&timeRegistrationData, (void *)(TIMEREGDATAIND+(index * sizeof(timeRegistrationData))), sizeof(timeRegistrationData));
  return timeRegistrationData;
}

struct ChronoData CookaStorage::readNextChronoValue(){
  struct ChronoData chronoData;

  eeprom_read_block((char *)&chronoData, (void *)(CHRONODATAINPUTIND), sizeof(chronoData));

  struct ChronoData tmpChronoData;
  for(byte i= 1;i<MAXTIMEREGDATA;i++){
    eeprom_read_block((char *)&tmpChronoData, (void *)(CHRONODATAINPUTIND+(i * sizeof(tmpChronoData))), sizeof(tmpChronoData));
    if(strlen(tmpChronoData.time)==0){
      for(int j=CHRONODATAINPUTIND+((i-1)*sizeof(tmpChronoData));j<CHRONODATAINPUTIND+((i)*sizeof(tmpChronoData));j++){
          EEPROM.write(j,0);
      }

      tmpChronoDataStorageIndex = i-1;
      break;
    }else
      eeprom_write_block(&tmpChronoData, (void *)(CHRONODATAINPUTIND+((i-1) * sizeof(tmpChronoData))), sizeof(tmpChronoData));

  }

  return chronoData;
}

bool CookaStorage::storeChronoData(struct ChronoData chronoData){
  eeprom_write_block(&chronoData, (void *)(CHRONODATAINPUTIND+(tmpChronoDataStorageIndex * sizeof(chronoData))), sizeof(chronoData));

  if(tmpChronoDataStorageIndex<MAXTIMEREGDATA){
    tmpChronoDataStorageIndex++;
  }
  else{

    tmpChronoDataStorageIndex = 0;
  }

  return true;
}

bool CookaStorage::activateTimeRegistrationStorage(){
  bool mayHaveMore=true;

  struct TimeRegistration timeRegData;
  while(mayHaveMore){
    eeprom_read_block(&timeRegData, (void *)(TIMEREGDATAIND+(tmpCheckpointStorageIndex * sizeof(timeRegData))), sizeof(timeRegData));    // read 'em back

    if(timeRegData.checkpointNumber == 0){
      mayHaveMore = false;
    }else{
      if(tmpCheckpointStorageIndex<120){
        tmpCheckpointStorageIndex++;
      }else{
        tmpCheckpointStorageIndex = -1;
      }
    }
  }
}

byte CookaStorage::getNumberOfStoredItems(){
  return tmpCheckpointStorageIndex;
}
