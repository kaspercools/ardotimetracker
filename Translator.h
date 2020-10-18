#ifndef Translator_h
#define Translator_h
#include "arduino.h"

class Translator{
  public:
    static String getLoadingCheckpoint();
    
    
    /* checkpoint selection screen */
    static String getCheckpointSelectionTitle();
    static String getCheckpointSelectionLabel();
    static String getCheckpointSelectionErrorText();
    
    /* the other screens */
    static String getVehicleLabelText();
    static String getCheckpointLabelText();
    static String getStartLabelText();
    static String getFinishLabelText();
    static String getControlekamerLabelText();
     static String getCommentLabelText();
    static String getComputingOfficeLabelText();
    static String getYourMessageLabelText();
    
    /* error labels */
    static String getVehicleErrorText();
    static String getCheckpointErrorText();
    static String getStartErrorText();
    static String getFinishErrorText();
    
    /* Confirm dialog */
    static String getSendText();
    static String getCancelText();
    static String getConfirmationText();
    static String getMessageSendingText();
    
    
};
#endif
