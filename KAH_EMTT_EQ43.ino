/*************************************************************************************************************************************/
// Sujet :   Programme de l'émetteur du projet KAH                                                                                   //
// Equipe :  xxxxxxx                                                                                                                    //
// Date :    xx/xx/xxxx                                                                                                              //
// Version : x                                                                                                                  //
/*************************************************************************************************************************************/

// inclusion des fichiers header des bibliothèques de fonctions Arduino
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
  return(analogRead(PotentiometreVitesse_Pin));

}

uint16_t AcquerirPotentiometreDirection(void) {   // retourne une valeur : [ ? ; ? ]
  uint16_t Aq_direction = map(analogRead(PotentiometreDirection_Pin), 0, 1024, 0, 31);             // à compléter
  return Aq_direction;    // à compléter
}

uint8_t AcquerirBoutonPoussoir() {                // retourne : 0 (BP relaché), 1 (BP enfoncé)
   return(digitalRead(BoutonPoussoir_Pin));
}


// definition des fonctions de traitement
uint8_t CalculerDonneeNEC(uint16_t Vitesse, uint16_t Direction) { 
  static int Donnee[8] = {0};// retourne un octet (8 bits) : Vitesse sur les 3 MSB, Direction sur les 5 LSB 
  int drctin = (Vitesse << 5) | (Direction & 0x1F);
  for (int i = 7; i >= 0; i--) {
    Donnee[i] = ((drctin >> i) & 1);
  }
  return Donnee ;    // à compléter+
}

// definition des fonctions de traitement
uint8_t CalculerAdresseNEC(uint8_t Klaxon) { // retourne un octet (8 bits) : Klaxon sur le MSB, NumeroEquipe sur les 7 LSB
  static int Adresse[8] = {0};
  int adrss = (Klaxon << 7) | (NumeroEquipe & 0x7F);
  for (int i = 7; i >= 0; i--) {
    Adresse[i] = ((adrss >> i) & 1);
  }
  return Adresse ;   
}

// definition des fonctions d'action
                    // inclus dans la bibliothèque NEC


// definition des fonctions principales
void setup(void) {
  Serial.begin(9600);
// à compléter
}

void loop(void) {
  uint16_t Vitesse = AcquerirPotentiometreVitesse();
  uint16_t Direction = AcquerirPotentiometreDirection();
  uint8_t Klaxon;
  uint8_t DonneeNEC =  CalculerDonneeNEC(Vitesse,Direction);
  uint8_t AdresseNEC = CalculerAdresseNEC(Klaxon);
//  ...             // à compléter
}
