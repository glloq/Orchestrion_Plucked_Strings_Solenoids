#ifndef SETTINGS_H
#define SETTINGS_H

#define NUM_STRINGS 4         // Nombre de cordes
#define MCP_START_ADDRESS 0x20 // Adresse de base du premier MCP23017
#define MCP_NUMBER_USED 5 // nombre de MCP23017 a a initialiser 

#define TIME_ACTIVE_MAX 5000 // temps actif maximum 


// Structure pour une corde
struct StringConfig {
  uint8_t midiNote;          // Numéro MIDI de la corde à vide
  uint8_t numFrets;          // Nombre de frettes utilisées sur la corde
  uint8_t firstFretPin;      // Pin PCA de la première frette
  uint8_t pluckSolenoid1Pin; // Pin pour le premier solénoïde de grattage
  uint8_t pluckSolenoid2Pin; // Pin pour le deuxième solénoïde de grattage
};

// Déclaration des cordes dans un tableau
const StringConfig stringConfigs[NUM_STRINGS] = {
  { 40, 5, 0, 10, 11 }, // Exemple pour la première corde
  { 45, 5, 5, 12, 13 }, // Exemple pour la deuxième corde
  { 50, 5, 10, 14, 15 },
  { 55, 5, 15, 16, 17 }
};

#endif
