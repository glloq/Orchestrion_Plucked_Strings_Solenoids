#ifndef MIDIHANDLER_H
#define MIDIHANDLER_H

#include <MIDIUSB.h>
#include "instrument.h"

class MidiHandler {
  private:
    Instrument& _instrument;
    void processMidiEvent(midiEventPacket_t midiEvent);
  public:
    MidiHandler(Instrument &instrument);
    void readMidi();
};

#endif // MIDIHANDLER_H
