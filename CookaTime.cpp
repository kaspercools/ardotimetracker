#include "CookaTime.h"

CookaTime::CookaTime(){
  hours=0;
  minutes=0;
  seconds=0;
  milliseconds=0;
}

CookaTime::CookaTime(byte _hours,byte _minutes,byte _seconds){
  hours=_hours;
  minutes=_minutes;
  seconds=_seconds;
  milliseconds = 0;
}

CookaTime::CookaTime(long _milliseconds){
  seconds = (_milliseconds / 1000LL) % 60;
  minutes = ((_milliseconds / (1000LL*60)) % 60);
  hours   = ((_milliseconds / (1000LL*60*60)) % 24);
  milliseconds = (_milliseconds % 1000LL);
}

byte CookaTime::getHours(){
  return hours;
}

byte CookaTime::getMinutes(){
  return minutes;
}

byte CookaTime::getSeconds(){
  return seconds;
}

byte CookaTime::getMilliseconds(){
  return milliseconds;
}

void CookaTime::setHours(byte _hours){
  isValidHour = _hours<24;

  hours = _hours;
}

void CookaTime::setMinutes(byte _minutes){
  isValidMinute = _minutes<60;
  minutes=_minutes;
}

void CookaTime::setSeconds(byte _seconds){
  isValidSecond=_seconds<60;
  seconds=_seconds;
}

void CookaTime::setMilliseconds(int mill){
 milliseconds =mill;
}

boolean CookaTime::receivedValidInput(){
  return isValidHour && isValidMinute && isValidSecond;
}

unsigned long CookaTime::getTotalTimeInMilliseconds(){
  return (hours*60*60*1000LL)+(minutes*60*1000LL)+(seconds*1000LL)+(milliseconds);
}

void CookaTime::setTimeFromString(String time){
  if(time.length()>=2){
    setHours(time.substring(0,2).toInt());
  }

  if(time.length()>=5){
    setMinutes(time.substring(3,5).toInt());
  }

  if(time.length()>=6){
    setSeconds(time.substring(6,8).toInt());
  }

  if(time.length()>=9){
    setMilliseconds(time.substring(9,time.length()).toInt());
  }
}

byte CookaTime::addHours(byte _hours){
  hours+=_hours;

  if(hours>23){
    hours-=24;
  }
}

String CookaTime::printTime(){
  return ((String(getHours()).length()==1)?"0":"")+String(getHours())+":"+((String(getMinutes()).length()==1)?"0":"")+String(getMinutes());
}

String CookaTime::getFormattedString(){

  String mills = "";
  byte milLength = String(getMilliseconds()).length();
  if(milLength==1){
    mills+="00";
  }else if(milLength ==2){
    mills+="0";
  }

  mills+=String(getMilliseconds());

  return ((String(getHours()).length()==1)?"0":"")+String(getHours())
            +((String(getMinutes()).length()==1)?"0":"")+String(getMinutes())
            +((String(getSeconds()).length()==1)?"0":"")+String(getSeconds());
}
