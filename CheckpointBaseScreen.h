#ifndef CheckpointBaseScreen_h
#define CheckpointBaseScreen_h
#include "Screen.h"
#include "NumericInputField.h"
#include "Screen.h"
#include "TextInputField.h"
#include "Label.h"
#include "CheckpointInfoControl.h"
#include "ConfirmationDialog.h"

class CheckpointBaseScreen:public Screen{
public:
    CheckpointBaseScreen();
    CheckpointBaseScreen(String _title,int _width, int _height);
    virtual void drawScreen(Adafruit_TFTLCD tft);
    virtual void processScreen(Adafruit_TFTLCD tft);
    virtual boolean validateInput();
protected:
    int selectedInputInd = -1;
    InputField* selectedInput;
    NumericInputField vehicleInput;
    TextInputField commentInput;
    Label errorLabel;
    char currentKeyboardChar;
    bool confirmationDialogWasActivated = false;
    CheckpointInfoControl checkpointInfoCtrl;
    long msgTimer = 0;
    long msgInterval = 5.0 * 60 * 1000000UL;
    ConfirmationDialog confirmationDialog;
};
#endif

    
