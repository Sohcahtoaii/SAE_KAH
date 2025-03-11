/*************************************************************************************************************************************/
// Sujet :   Programme de l'émetteur du projet KAH                                                                                   //
// Equipe :  xxxxxxx                                                                                                                    //
// Date :    xx/xx/xxxx                                                                                                              //
// Version : x                                                                                                                  //
/*************************************************************************************************************************************/

// inclusion des fichiers hearrder des bibliothèques de fonctions Arduino
#include <stdint.h>
#include <arduino.h>
#include "NEC.h"


// definition des constantes du projet
#define PotentiometreVitesse_Pin     A0       // à modifier
#define PotentiometreDirection_Pin   A1       // à modifier
#define BoutonPoussoir_Pin            8       // à modifier
#define LEDInfrarouge_Pin             9       // à modifier
#define NumeroEquipe               0x52       // à modifier


// definition des fonctions d'acquisition
uint16_t AcquerirPotentiometreVitesse(void) {     // retourne une valeur : [ ? ; ? ]
//  ...             // à compléter
//  return ... ;    // à compléter
}

uint16_t AcquerirPotentiometreDirection(void) {   // retourne une valeur : [ ? ; ? ]
  uint16_t direction = map(analogRead(PotentiometreDirection_Pin), 0, 1024, 0, 2);             // à compléter
  return direction ;    // à compléter
}

uint8_t AcquerirBoutonPoussoir() {                // retourne : 0 (BP relaché), 1 (BP enfoncé)
//  ...             // à compléter
//  return ... ;    // à compléter
}


// definition des fonctions de traitement
uint8_t CalculerDonneeNEC(uint16_t Vitesse, uint16_t Direction) { // retourne un octet (8 bits) : Vitesse sur les 4 MSB, Direction sur les 4 LSB
//  ...             // à compléter
//  return ... ;    // à compléter
}

// definition des fonctions de traitement
uint8_t CalculerAdresseNEC(uint8_t Klaxon) { // retourne un octet (8 bits) : Klaxon sur le MSB, NumeroEquipe sur les 7 LSB
//  ...             // à compléter
//  return ... ;    // à compléter
}

// definition des fonctions d'action
                    // inclus dans la bibliothèque NEC


// definition des fonctions principales
void setup(void) {
//  ...             // à compléter
}

void loop(void) {
  uint16_t Vitesse;
  uint16_t Direction;
  uint8_t Klaxon;
  uint8_t DonneeNEC;
  uint8_t AdresseNEC;
//  ...             // à compléter
}
