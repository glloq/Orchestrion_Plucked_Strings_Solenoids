
#include <MIDIUSB.h>
#include "instrument.h"
#include "midiHandler.h"
#include "Arduino.h"

Instrument* instrument= nullptr;
MidiHandler* midiHandler= nullptr;

void setup() {
  Serial.begin(115200);
 // while (!Serial) {
  //  delay(10); // Attendre que la connexion série soit établie
  //}
  Serial.println("init");
  instrument= new Instrument();
  midiHandler = new MidiHandler(*instrument);
  Serial.println("fin init");
}

void loop() {
  midiHandler->readMidi();
  instrument->update();
}