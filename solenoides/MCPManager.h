#ifndef MCPMANAGER_H
#define MCPMANAGER_H

#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include "settings.h"

class MCPManager {
private:
    Adafruit_MCP23X17* mcpDevices;
    bool solenoidActive[MCP_NUMBER_USED * 16];  // Tableau pour suivre l'état des solénoïdes
    unsigned long solenoidDesactveTime[MCP_NUMBER_USED * 16];  // Tableau pour le temps de fonctionnement max des solenoides

public:
    MCPManager() {
        mcpDevices = new Adafruit_MCP23X17[MCP_NUMBER_USED];
        for (int i = 0; i < MCP_NUMBER_USED; i++) {  // Initialise les MCP
            mcpDevices[i].begin_I2C(MCP_START_ADDRESS + i);
            for (int j = 0; j < 16; j++) {  // Initialise les pins de chaque MCP
                mcpDevices[i].pinMode(j, OUTPUT); // En sortie
                mcpDevices[i].digitalWrite(j, LOW);  // Désactive la sortie
                solenoidActive[i * 16 + j] = false;  // Initialise les solénoïdes comme inactifs
                solenoidDesactveTime[i * 16 + j] = 0;  // Initialise le temps d'activation à zéro
            }
        }
    }

    void setPin(uint16_t globalPin, uint8_t state) {
        uint8_t deviceIndex = globalPin / 16;
        uint8_t localPin = globalPin % 16;
        if (deviceIndex < MCP_NUMBER_USED) {
            mcpDevices[deviceIndex].digitalWrite(localPin, state);
            if (state == HIGH) {
                solenoidActive[globalPin] = true;  // Marquer le solénoïde comme actif
                solenoidDesactveTime[globalPin] = millis()+TIME_ACTIVE_MAX;  // Enregistrer le temps ou il faudra le desactiver
            } else {
                solenoidActive[globalPin] = false;  // Marquer le solénoïde comme inactif
                solenoidDesactveTime[globalPin] = 0;  // Réinitialiser le temps d'activation
            }
        }
    }

    void update() {
        unsigned long currentTime = millis();
        for (int i = 0; i < MCP_NUMBER_USED * 16; i++) {
            if (solenoidActive[i]) {
                if (currentTime> solenoidDesactveTime[i]) {//si le solenoide est actif depuis trop longtemps
                    uint8_t deviceIndex = i / 16;
                    uint8_t localPin = i % 16;
                    mcpDevices[deviceIndex].digitalWrite(localPin, LOW);  // Désactiver la sortie
                    solenoidActive[i] = false;  // Marquer comme inactif
                    solenoidDesactveTime[i] = 0;  // Réinitialiser le temps d'activation
                }
            }
        }
    }
};

#endif
