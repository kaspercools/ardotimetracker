#include "Translator.h"
#include "Globals.h"

String Translator::getLoadingCheckpoint(){
  switch(ckSettings->lang){
     case 1:
      return F("Checkpoint laden...");
     case 2:
       return F("Chargement du checkpoint");
     default:
       return F("Loading checkpoint...");
   }
}

String Translator::getCheckpointSelectionErrorText(){
  switch(ckSettings->lang){
     case 1:
       return F("Dit checkpoint bestaat niet");
     case 2:
       return F("Checkpoint inexistant");
     default:
       return F("The selected checkpoint does not exist");
   }
}

 String Translator::getCheckpointSelectionTitle(){
   switch(ckSettings->lang){
     case 1:
       return F("Selecteer checkpoint");
     case 2:
       return F("Selectionnez le CP");
     default:
       return F("Select checkpoint");
   }
 }

 String Translator::getCheckpointSelectionLabel(){
   switch(ckSettings->lang){
     case 1:
       return F("Voer het nummer van uw checkpoint in");
     case 2:
       return F("Inserez le numero de votre checkpoint");
     default:
       return F("Enter the checkpoint number");
   }
 }

 String Translator::getVehicleLabelText(){
   switch(ckSettings->lang){
     case 1:
       return F("wagennr");
     case 2:
       return F("voiture");
     default:
       return F("car no.");
   }
 }

 String Translator::getCheckpointLabelText(){
   switch(ckSettings->lang){
     case 1:
       return F("CP tijd");
     case 2:
       return F("CP temps");
     default:
       return F("CP time");
   }
 }

 String Translator::getStartLabelText(){
   switch(ckSettings->lang){
     case 1:
       return F("Start");
     case 2:
       return F("Depart");
     default:
       return F("Start");
   }
 }

 String Translator::getFinishLabelText(){
   switch(ckSettings->lang){
     case 1:
       return F("Finish");
     case 2:
       return F("Finish");
     default:
       return F("Finish");
   }
 }

 String Translator::getComputingOfficeLabelText(){
   switch(ckSettings->lang){
       case 1:
         return F("Rekenbureel");
       case 2:
       return F("Centre de calcul");
       default:
         return F("Computing off.");
     }
 }

 String Translator::getYourMessageLabelText(){
   switch(ckSettings->lang){
       case 1:
         return F("Uw bericht");
       case 2:
       return F("Votre message");
       default:
         return F("Your message");
     }
 }

 String Translator::getCommentLabelText(){
   switch(ckSettings->lang){
       case 1:
         return F("Opmerking");
       case 2:
       return F("Remarque");
       default:
         return F("Comment");
     }
 }

/* error labels */
 String Translator::getVehicleErrorText(){
   switch(ckSettings->lang){
     case 1:
       return F("Wagennr niet geldig");
     case 2:
       return F("no voiture incorrect");
     default:
       return F("Car no. not valid");
   }
 }

 String Translator::getCheckpointErrorText(){
   switch(ckSettings->lang){
     case 1:
       return F("TC tijd niet geldig");
     case 2:
      return F("Temps TC incorrect");
     default:
       return F("TC time not valid");
   }
 }

 String Translator::getStartErrorText(){
    switch(ckSettings->lang){
     case 1:
       return F("Start niet geldig");
     case 2:
       return F("Start incorrect");
     default:
       return F("Start not valid");
   }
 }

 String Translator::getFinishErrorText(){
   switch(ckSettings->lang){
     case 1:
       return F("Finish niet geldig");
     case 2:
       return F("Finish incorrect");
     default:
       return F("Finish not valid");
   }
 }

  /* Confirm dialog */
 String Translator::getSendText(){
   switch(ckSettings->lang){
     case 1:
       return F("Versturen (D)");
     case 2:
       return F("Envoyer (D)");
     default:
       return F("Send (D)");
   }
 }

 String Translator::getCancelText(){
   switch(ckSettings->lang){
     case 1:
       return F("Annuleer (A)");
     case 2:
       return F("Annuler (A)");
     default:
       return F("Cancel (A)");
   }
 }

 String Translator::getConfirmationText(){
   switch(ckSettings->lang){
     case 1:
       return F("Bent u zeker dat u deze gegevens wenst te versturen?");
     case 2:
       return F("Etes-vous sur de vouloir envoyer ces donnees?");
     default:
       return F("Are you sure you want to send these data?");
   }
 }

 String Translator::getMessageSendingText(){
   switch(ckSettings->lang){
       case 1:
         return F("Versturen...");
       case 2:
       return F("Envoyer..");
       default:
         return F("Sending...");
   }
 }

