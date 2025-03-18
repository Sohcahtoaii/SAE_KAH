/*************************************************************************************************************************************/
// Sujet :   Programme de l'émetteur du projet KAH                                                                                   //
// Equipe :  EQ43                                                                                                                //
// Date :    xx/xx/xxxx                                                                                                              //
// Version : 1                                                                                                                  //
/*************************************************************************************************************************************/

// inclusion des fichiers header des bibliothèques de fonctions Arduino
#include <stdint.h>
#include <arduino.h>
#include "NEC.h"


// definition des constantes du projet
#define Servomoteur_Pin               5       // à modifier
#define Moteur_Pin                    6       // à modifier
#define Buzzer_Pin                   11       // à modifier
#define LedBleue_Pin                 10       // à modifier
#define NumeroEquipe               0x52       // à modifier



// definition des fonctions d'acquisition
                    // inclus dans la bibliothèque NEC

// definition des fonctions de traitement
uint8_t ExtraireNumeroEquipe(uint8_t Adresse) { // retourne une valeur : [ ? ; ? ]
//  ...             // à compléter
//  return ... ;    // à compléter
}

// definition des fonctions de traitement
uint8_t CalculerDirectionServomoteur(uint8_t Donnee) { // retourne une valeur : [ ? ; ? ]
//  ...             // à compléter
//  return ... ;    // à compléter
}

// definition des fonctions de traitement
uint8_t CalculerVitesseMoteur(uint8_t Donnee) { // retourne une valeur : [ ? ; ? ]
//  ...             // à compléter
//  return ... ;    // à compléter
}

// definition des fonctions de traitement
uint8_t ExtraireEtatBuzzer(uint8_t Adresse) { // retourne : 0 (inactif), 1 (actif)
//  ...             // à compléter
//  return ... ;    // à compléter
}


// definition des fonctions d'action
void PiloterServomoteur(uint8_t Direction) { // génère un signal PWM
//                  // à compléter
//  return ... ;    // à compléter
}

void PiloterMoteur(uint8_t Vitesse) { // génère un signal PWM
//  ...             // à compléter
//  return ... ;    // à compléter
}

void PiloterBuzzer(uint8_t EtatBuzzer) { // génère un signal carré à 4kHz si EtatBuzzer = 1
// if (EtatBuzzer == 1){ // à compléter
// tone(4000)  // à compléter
//  return;    // à compléter
}

void PiloterLedBleue(uint8_t EtatLedBleue) { // génère un signal binaire
//  ...             // à compléter
//  return ... ;    // à compléter
}


// definition des fonctions principales
void setup(void) {
//  ...             // à compléter
}

void loop(void) {
  uint8_t Donnee;
  uint8_t Adresse;
  uint8_t Vitesse;
  uint8_t Direction;
  uint8_t Klaxon;
//  ...             // à compléter
}
