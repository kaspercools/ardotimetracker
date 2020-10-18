#include "AlphanumericKeypad.h"
#include "Keypad.h"


char lastKey;
char Character;
byte K_count = 0;
unsigned long timer, interval = 0.25 * 1000000UL; // interval = 2 seconds
bool lockout = true;

const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = { 38,40,42,44 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 39,41,43,45 }; //connect to the column pinouts of the keypad

// This array is used to change between the characters in the second array

char Keys[ROWS][COLS] = {
  {
    '1', '2', '3','<'        }
    ,
    {
      '4', '5', '6','-'        }
      ,
      {
        '7', '8', '9','+'        }
        ,
        {
          '*', '0', '#','>'        }
        };

// The following array is what is printed when a key is pressed
// Format: { Number of characters to cycle through, characters to be shown . . .}
        char characterMap[ROWS][COLS][6] = {
          {
            {
              4, '.',',','?','1'              }
              , {
                4, 'a', 'b', 'c', '2'              }
                , {
                  4, 'd', 'e', 'f', '3'              }
                }
                ,
                {
                  {
                    4, 'g', 'h', 'i', '4'              }
                    , {
                      4, 'j', 'k', 'l', '5'              }
                      , {
                        4, 'm', 'n', 'o', '6'              }
                      }
                      ,
                      {
                        {
                          5, 'p', 'q', 'r', 's', '7'              }
                          , {
                            4, 't', 'u', 'v', '8'              }
                            , {
                              5, 'w', 'x', 'y', 'z', '9'              }
                            }
                            ,
                            {
                              {
                                1, '*'              }
                                , {
                                  2,' ', '0'              }
                                  , {
                                    1, '#'              }
                                  }
                                };

  Keypad keypadBase = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);

  AlphanumericKeypad::AlphanumericKeypad(){

  }

  void AlphanumericKeypad::enableAlphaNumerics(){
    proccessAlphanumerics=true;
  }

  void AlphanumericKeypad::disableAlphaNumerics(){
    proccessAlphanumerics=false;
  }

  char AlphanumericKeypad::processInput(){
  char customKey = keypadBase.getKey();
  if(proccessAlphanumerics){
    //Check the key pressed. If the key is different, show it on a new line
    if (customKey && customKey != lastKey)
    {
      lastKey = customKey; // update lastKey
      K_count = 0; // This resets the counter so when a different key is pressed, you only see the NUMBER associated with that key.
    }

    if (customKey)
    {
      timer = micros(); // start a timer, when a key is pressed
      lockout = false; // allow the lockout timer to be checked
      lastKey = customKey; // update lastKey
      switch (customKey)
      {
        case '1':

        case '2':
        case '3':
        K_count = (K_count < (byte)(characterMap[0][(customKey - '0') - 1][0]) ? ++K_count : 1);       // Update the counter if the same key is pressed (counter rolls over)
        Character = characterMap[0][(customKey - '0') - 1][K_count];                                   // Character = '2' - ABC and '3' - DEF
        break;

        case '4'...'6':
        K_count = (K_count < (byte)characterMap[1][(customKey - '0') - 4][0] ? ++K_count : 1);
        Character = characterMap[1][(customKey - '0') - 4][K_count];
        break;

        case '7'...'9':
        K_count = (K_count < (byte)characterMap[2][(customKey - '0') - 7][0] ? ++K_count : 1);
        Character = characterMap[2][(customKey - '0') - 7][K_count];

        break;

        case '*':
        Character = characterMap[3][0][1]; // shows *
        break;

        case '0':

        K_count = (K_count < (byte)(characterMap[3][(customKey - '0') + 1][0]) ? ++K_count : 1);       // Update the counter if the same key is pressed (counter rolls over)
        Character = characterMap[3][(customKey - '0') +1][K_count];            // Character = '2' - ABC and '3' - DEF
        break;

        case '#':
        Character = characterMap[3][2][1]; // shows #
        break;

      default: // if something unexpected happens, set Character to 0
      Character = customKey;
        lastKey = '~'; //dummy character;
        K_count = 0; // Resets the counter
        lockout = true; // lockout is set to true, thus this IF statement does not continue to execute
        return Character;
      }
    }

    if((micros() - timer >= interval) && !lockout) //If a key was pressed and then 2 seconds has past, reset the lastKey and counter.
    {
      lastKey = '~'; //dummy character;
      K_count = 0; // Resets the counter
      lockout = true; // lockout is set to true, thus this IF statement does not continue to execute
      return Character;
    }

    return NO_KEY;
  }
  else{
    return customKey;
  }
}

KeyState AlphanumericKeypad::getState(){
  return keypadBase.getState();
}
