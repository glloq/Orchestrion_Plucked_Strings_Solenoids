#ifndef STRINGCONTROL_H
#define STRINGCONTROL_H

#include "MCPManager.h"
#include "settings.h"

class StringControl {
private:
  const StringConfig& config;
  MCPManager* mcpManager;
  bool puckSide;
  bool isFree;
  int midiNoteOn;//note midi de la note en cours sur la corde 

  void pressFret(uint8_t fret) {
    mcpManager->setPin(config.firstFretPin + fret, HIGH);
  }
  
 void freeFret(uint8_t fret) {
    mcpManager->setPin(config.firstFretPin + fret, LOW);
  }

  void pluck() {
    if (puckSide){
      mcpManager->setPin(config.pluckSolenoid1Pin, HIGH);
      puckSide=false;
    }else{
      mcpManager->setPin(config.pluckSolenoid2Pin, HIGH);
      puckSide=true;
    }
  }

  
public:
  
  StringControl(const StringConfig& stringConfig, MCPManager* manager)
    : config(stringConfig), mcpManager(manager) {
   
    //init the plucking side
    mcpManager->setPin(config.pluckSolenoid1Pin, HIGH);
    delay(50);
    mcpManager->setPin(config.pluckSolenoid1Pin, LOW);
    puckSide=true;
    isFree=true;
  }


  bool isPlaying(){
    return !isFree;
  }

  bool CanItPlay(int midiNote){ 
    if (midiNote>=config.midiNote && midiNote>=(config.midiNote +config.numFrets)){
      return true;
    }
    return false;
  }

  void noteOn(int midiNote){
    int fret = midiNote-config.midiNote;
    if (fret!=0){pressFret(fret);} // on active la frette pour l'accord si c'est pas la corde ouverte
    pluck();
    midiNoteOn=midiNote;  
    isFree=false;
  }

  bool noteOff(int midiNote){
    if(midiNoteOn==midiNote){//si c'est la note que la corde est en train de jouer 
      if(midiNote!=config.midiNote){//si c'est pas la corde ouverte
        int fret = midiNote-config.midiNote;
        freeFret(fret); //on desactive le solenoide
      }
      
      if (puckSide){ //puis on desactive le solenoide de gratage utilisé
        mcpManager->setPin(config.pluckSolenoid1Pin, LOW);
      }else{
        mcpManager->setPin(config.pluckSolenoid2Pin, LOW);
      }
        isFree=true;
        return true; // on indique que la note a été desactivé
      }
    return false; // on indique que c'est pas la note en cours
  }
};

#endif
