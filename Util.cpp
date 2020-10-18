#include "Util.h"
#include "arduino.h"
#include "assert.h"
#include "Fonts.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"

byte Utils::StringMutators::printWithMargin(String text,int xOrigin, int yOrigin,byte lineHeight, byte margin,int maxWidth,Adafruit_TFTLCD tft)
{
  char charArr[text.length()];
  
  text.toCharArray(charArr,text.length());
  
  int x=xOrigin;
  int y=yOrigin;
  char *p = charArr;
  char *str;
  byte ln=0;
  byte numberOfLinesWritten=0;
  byte trailing=0;
  byte startIndex=0;
  byte maxLineChars=((maxWidth-margin)/(Fonts::fontWidth*Fonts::fontSize));
  String nextPart="";
  String lineToPrint="";
  tft.setCursor(x,y);

  while ((str = strtok_r(p, " ", &p)) != NULL){ // delimiter is the semicolon
    ln+=trailing;
    trailing=1;
   
    ln+=strlen(str);
    
    //if larger then eg 32 then print previous part
    if(ln>maxLineChars){
      //substract recently added lengths
      ln -= strlen(str);
      ln -= trailing;

      //now print up untill that new length
      nextPart = text.substring(startIndex,(startIndex+ln));
      nextPart.trim();
      
      tft.print(nextPart);
      numberOfLinesWritten+=1;
      tft.setCursor(x,y+(lineHeight*numberOfLinesWritten));

      startIndex +=ln;
      ln=0;
      trailing=1;
      ln=trailing+strlen(str);
    }
  }

  nextPart = text.substring(startIndex,text.length());
  nextPart.trim();
  tft.print(nextPart);
  
  return numberOfLinesWritten;
}

#define MAX_STRING_LEN 90
 char* Utils::StringMutators::subStr (char* input_string, char *separator, byte segment_number) {
 char *act, *sub, *ptr;
 static char copy[MAX_STRING_LEN];
 byte i;
 
 strcpy(copy, input_string);
 
for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
 
 sub = strtok_r(act, separator, &ptr);
 if (sub == NULL) break;
 }
 return sub;
}
