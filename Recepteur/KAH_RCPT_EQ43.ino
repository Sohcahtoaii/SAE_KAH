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
#define Servomoteur_Pin              12
#define Moteur_Pin                    5
#define Buzzer_Pin                   11
#define LedBleue_Pin                  4
#define LedVerte_Pin                  6
#define NumeroEquipe               0x43



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
  analogWrite(Servomoteur_Pin,Direction);
}

void PiloterMoteur(uint8_t Vitesse) { // génère un signal PWM
  analogWrite(Moteur_Pin,Vitesse);
}

void PiloterBuzzer(uint8_t EtatBuzzer) { // génère un signal carré à 4kHz si EtatBuzzer = 1
if (EtatBuzzer == 1){
  tone(11,4000);
  }
else {
  noTone();
}

void PiloterLedBleue(uint8_t EtatLedBleue) { // génère un signal binaire
if (EtatLedBleue == 1){
  digitalWrite(4,LOW);
  delay(333);
  }
else {
  digitalWrite(4,HIGH);
}

void PiloterLedVerte(uint8_t EtatLedVerte) { // génère un signal binaire
digitalWrite(6,LOW);
}

// definition des fonctions principales
void setup(void) {
  pinMode (12,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (11,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (6,OUTPUT);
}

void loop(void) {
  uint8_t Donnee;
  uint8_t Adresse;
  uint8_t Vitesse;
  uint8_t Direction;
  uint8_t Klaxon;
  uint8_t Erreur;
  PiloterServomoteur(Direction);
  PiloterMoteur(Vitesse);
  PiloterBuzzer(Klaxon);
  PiloterLedBleue(LedB);
  PiloterLedVerte(1);
}
