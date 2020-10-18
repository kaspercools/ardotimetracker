#ifndef Time_h
#define Time_h
#include "arduino.h";

class CookaTime{

public:
    CookaTime();
    CookaTime(byte _hours,byte _minutes,byte _seconds);
    CookaTime(long _milliseconds);

    byte getHours();
    byte getMinutes();
    byte getSeconds();
    byte getMilliseconds();

    void setHours(byte hours);
    void setMinutes(byte minutes);
    void setSeconds(byte seconds);
    void setMilliseconds(int mill);
    void setTimeFromString(String time);
    boolean receivedValidInput();
    unsigned long getTotalTimeInMilliseconds();
    String getFormattedString();
    byte addHours(byte  hours);
    String printTime();
private:
    byte hours;
    byte minutes;
    byte seconds;
    int milliseconds;
    boolean isValidHour = true;
    boolean isValidMinute = true;
    boolean isValidSecond = true;
};
#endif
