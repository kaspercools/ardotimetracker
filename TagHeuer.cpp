#include "TagHeuer.h"
#include "structs.cpp"
#include "Globals.h"
#include "MemoryFree.h"

TagHeuer::TagHeuer(){

 Serial1.begin(9600);

}

void TagHeuer::readData(){
  struct ChronoData data[15];
  String input;
  byte m,pos = 0;

  while (Serial1.available() > 0) {
    input = Serial1.readStringUntil('\r');
    input.trim();

    if(input.length()>0){
      m = input.indexOf('M');

      input = input.substring(m+2,28);

      input.trim();
      if(input.length()!=0){
        if(input.length()==5){
          input = "00:00:0"+input;
        }else if(input.length()==6){
          input = "00:00:"+input;
        }else if(input.length()==8){
          input = "00:0"+input;
        }else if(input.length()== 9){
          input = "00:"+input;
        }else if(input.length()==11){
          input = "0"+input;
        }

        if(input.length()<12){
         m = input.length();
         for(byte i = 0;i<12-m;i++){
           input +="0";
         }
        }
      }
    }

    input.toCharArray(data[pos].time,sizeof(data[pos].time));
    pos++;
  }

  for(byte j = 0;j<pos;j++){
    Serial.println(freeMemory());
    if(strlen(data[j].time)>0){
      cookaStorage->storeChronoData(data[j]);
    }
  }


}

