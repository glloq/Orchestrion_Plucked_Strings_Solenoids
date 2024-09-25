# Orchestrion_Plucked_Strings_Solenoids

> [!IMPORTANT]
> le code compile et devrais fonctionner mais rien n'est testé !

Le projet permet de controller un instrument à cordes grattée (guitare, basse, ukulele, etc ...) en utilisant des solenoides pour actionner les frettes et gratter les cordes.
le code se veut adaptable pour touts les cas d'utilisations il suffira d'adapter les paramettres du fichier settings.h en fonction du branchement choisis.

le code est contruit autour de carte pcm23017 controlé via i2c, la partie puissance pourra etre faite avec des uln2803 (5-32v 500mA max par solenoide) ou des mofset pour les plus grosse puisssances.


### les accords
il faut placer des systemes de doigts entre les frettes qui viendrons tirer la corde vers le manche et faire l'accord voulu. 
il faudra absolument penser a utiliser des systeme pour amortir les deplacement ON/OFF de chaque solenoide pour limiter les bruits mecanique  
<img src="https://github.com/glloq/OneStringGuitar/blob/main/img/fingers%20solenoides.png" alt="Your image title" width=80% height=80%/>

### grattage 
la technique choisie est d'utiliser deux solenoides opposé l'un a l'autre et d'alterner l'activation des deux solenoides pour gratter la corde.   
<img src="https://github.com/glloq/OneStringGuitar/blob/main/img/grattage%202%20solenoides.png" alt="grattage 2 solenoides" width=80% height=80%/>  
une fois le solenoide de grattage desactivé le pick vient contre la corde pour etouffer la note.


## configuration de l'instrument 

le code permet de s'adapter a tout les cas d'utilisations, il suffit d'indiquer le nombre de cordes de l'instrument, le nombre de mcp utilisé et aussi le temps maximum actif d'un solenoide (afin de limiter la chauffe) 
```
#define NUM_STRINGS 4         // Nombre de cordes
#define MCP_NUMBER_USED 4      // Nombre de MCP23017 à initialiser
#define TIME_ACTIVE_MAX 5000   // Temps actif maximum en millisecondes

```

la definition de chaque corde est faite dans le tableau de cordes stringConfigs[NUM_STRINGS]
il suffira d'ajouter le meme nombre de lignes que de nombre de corde  avec les differentes informations de chaque corde
```
struct StringConfig {
  uint8_t midiNote;          // Numéro MIDI de la corde à vide
  uint8_t numFrets;          // Nombre de frettes utilisées sur la corde
  uint8_t firstFretPin;      // Pin PCA de la première frette
  uint8_t pluckSolenoid1Pin; // Pin pour le premier solénoïde de grattage
  uint8_t pluckSolenoid2Pin; // Pin pour le deuxième solénoïde de grattage
};
```
### Exemples  

voici les paramettres a prendre pour un systeme de ukulele 4 cordes avec 12 doigts par corde.

```
#define NUM_STRINGS 4         // Nombre de cordes
#define MCP_NUMBER_USED 4      // Nombre de MCP23017 à initialiser
const StringConfig stringConfigs[NUM_STRINGS] = {
  { 60, 12, 0, 14, 15 },  // Première corde (G), 12 frettes
  { 64, 12, 16, 30, 31 }, // Deuxième corde (C), 12 frettes
  { 67, 12, 32, 46, 47 }, // Troisième corde (E), 12 frettes
  { 72, 12, 48, 62, 63 }  // Quatrième corde (A), 12 frettes
};
```
- midiNote : C'est la note MIDI de la corde à vide. Les valeurs choisies ici correspondent aux cordes standards d'un ukulélé soprano :
   - G (première corde) : 60
   - C (deuxième corde) : 64
   - E (troisième corde) : 67
   - A (quatrième corde) : 72
- numFrets : Nombre de frettes par corde (ici 12, pour correspondre aux 12 solénoïdes par corde).
- firstFretPin : Le numéro du premier pin du MCP23017 pour les frettes. Chaque corde a un ensemble de 12 pins, un pour chaque solénoïde qui contrôle les frettes.
- pluckSolenoid1Pin et pluckSolenoid2Pin : Les pins des solénoïdes utilisés pour gratter la corde sont mis aux deux derniers pins de chaque mcp 
