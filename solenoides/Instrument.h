#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "settings.h"
#include "MCPManager.h"
#include "StringControl.h"

class Instrument {
private:
  MCPManager mcpManager;             // Instance de MCPManager
  StringControl* stringControls[NUM_STRINGS]; // Tableau pour gérer chaque corde

public:
  Instrument() {
    
    // Initialiser chaque corde
    for (int i = 0; i < NUM_STRINGS; i++) {
        stringControls[i] = new StringControl(stringConfigs[i], &mcpManager);
    }
  }

  void noteOn(int midiNote, int velocity) {
    // Sélectionner la corde appropriée
    int corde = selectString(midiNote);
    if(corde!=-1){// si on peut jouer la note sur une corde
      stringControls[corde]->noteOn(midiNote);
    }
  }

  void noteOff(int midiNote) {
    for (int i=0; i<NUM_STRINGS;i++){
      if(stringControls[i]->noteOff(midiNote)) {// si ca retourne true alors on a trouvé et arreté la note en cours
      return;// on arrete la boucle 
      }
    }
    // si on arrive ici alors la note off est pas trouvé
  }

  int selectString(int midiNote) {
    for (int i = 0; i < NUM_STRINGS; i++) {
      if (!stringControls[i]->isPlaying() && stringControls[i]->CanItPlay(midiNote)) {
                return i; // Retourner l'index de la première corde qui peut jouer la note
      }
    }
    return -1; // Aucune corde disponible pour jouer la note
  }
  

  void update() {
    mcpManager.update();
  }
};

#endif // INSTRUMENT_H
