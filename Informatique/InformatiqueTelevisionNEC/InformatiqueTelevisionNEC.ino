/*********************************************************************/
// Sujet :   Programme de reception NEC pour téléviseur              //
// Auteur :  AUGEREAU F.                                             //
// Date :    04/01/2016                                              //
// Version : 1.0                                                     //
/*********************************************************************/

// inclusion des fichiers header des bibliothèques de fonctions
#include <stdint.h>        // bibliotheque de type de variable
#include <arduino.h>       // bibliotheque de fonctions arduino
#include "NEC.h"           // bibliotheque de fonctions NEC

// definition des constantes du programme
#define RECEPTEUR_INFRAROUGE_Pin      8       // n° de broche du recepteur de trame infrarouge
#define VOLUME_Pin                    5       // n° de broche de l'actionneur de VOLUME
#define CHAINE_TF1_Pin                2       // n° de broche de l'actionneur de CHAINE TF1
#define CHAINE_F2_Pin                 3       // n° de broche de l'actionneur de CHAINE F2
#define CHAINE_F3_Pin                 4       // n° de broche de l'actionneur de CHAINE F3
#define CHAINE_CPLUS_Pin              7       // n° de broche de l'actionneur de CHAINE CPLUS
#define CHAINE_F5_Pin                 8       // n° de broche de l'actionneur de CHAINE F5
#define CHAINE_M6_Pin                 9       // n° de broche de l'actionneur de CHAINE M6
#define CHAINE_ARTE_Pin              10       // n° de broche de l'actionneur de CHAINE ARTE
#define AdresseNEC                 0x20       // Adresse du protocole NEC

// declaration des fonctions du programme
uint8_t CalculerVolume(uint8_t Donnee);                   // fonction de traitement
uint8_t CalculerChaine(uint8_t Donnee);                   // fonction de traitement
void PiloterVolume(uint8_t Volume);                       // fonction d'action
void PiloterChaine(uint8_t Chaine);                       // fonction d'action


// definition des fonctions du programme
uint8_t CalculerVolume(uint8_t Donnee)                    // CalculerVolume : fonction de traitement
{
  static uint8_t ValeurVolume = 50;
  if (Donnee == 0x85)            // Appui touche VOLUME MOINS ?
    if (ValeurVolume > 0)
      ValeurVolume--;
  if (Donnee == 0x05)            // Appui touche VOLUME PLUS ?
    if (ValeurVolume < 100)
      ValeurVolume++;
  return ValeurVolume;
}

uint8_t CalculerChaine(uint8_t Donnee)                    // CalculerChaine : fonction de traitement
{
  static uint8_t ValeurChaine = 1;
  if (Donnee == 0xC5)            // Appui touche CHAINE PLUS ?
    if (ValeurChaine > 1)
      ValeurChaine--;
  if (Donnee == 0x45)            // Appui touche CHAINE MOINS ?
    if (ValeurChaine < 7)
      ValeurChaine++;
  return ValeurChaine;
}


void PiloterVolume(uint8_t Volume)                        // PiloterVolume : fonction d'action
{
  analogWrite(VOLUME_Pin, Volume);
}

void PiloterChaine(uint8_t Chaine)                        // PiloterChaine : fonction d'action
{
  switch (Chaine) {
    case 1 : digitalWrite(CHAINE_TF1_Pin,   HIGH);    // TF1 activé
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 2 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    HIGH);    // FRANCE2 activé
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 3 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    HIGH);    // FRANCE3 activé
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 4 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, HIGH);    // CANAL+ activé
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 5 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    HIGH);    // FRANCE5 activé
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 6 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    HIGH);    // M6 activé
             digitalWrite(CHAINE_ARTE_Pin,  LOW);
             break;
    case 7 : digitalWrite(CHAINE_TF1_Pin,   LOW);
             digitalWrite(CHAINE_F2_Pin,    LOW);
             digitalWrite(CHAINE_F3_Pin,    LOW);
             digitalWrite(CHAINE_CPLUS_Pin, LOW);
             digitalWrite(CHAINE_F5_Pin,    LOW);
             digitalWrite(CHAINE_M6_Pin,    LOW);
             digitalWrite(CHAINE_ARTE_Pin,  HIGH);    // ARTE activé
             break;
    default : digitalWrite(CHAINE_TF1_Pin,   HIGH);
              digitalWrite(CHAINE_F2_Pin,    LOW);
              digitalWrite(CHAINE_F3_Pin,    LOW);
              digitalWrite(CHAINE_CPLUS_Pin, LOW);
              digitalWrite(CHAINE_F5_Pin,    LOW);
              digitalWrite(CHAINE_M6_Pin,    LOW);
              digitalWrite(CHAINE_ARTE_Pin,  LOW);
              break;
  }
}


void setup()
{
  // Initialisation du sens de transfert de l'information des broches de type GPIO
  pinMode(RECEPTEUR_INFRAROUGE_Pin, INPUT);                 // broche du port GPIO configuree en entree
  pinMode(CHAINE_TF1_Pin,           OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_F2_Pin,            OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_F3_Pin,            OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_CPLUS_Pin,         OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_F5_Pin,            OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_M6_Pin,            OUTPUT);                // broche du port GPIO configuree en sortie
  pinMode(CHAINE_ARTE_Pin,          OUTPUT);                // broche du port GPIO configuree en sortie
  PiloterVolume(50);                                        // positionnement initial du volume televiseur (50 = volume moyen)
  PiloterChaine(1);                                         // position initiale de la chaine (1 = TF1)
}


void loop()
{
  uint8_t Adresse;
  uint8_t Donnee;
  uint8_t Volume;
  uint8_t Chaine;
  int8_t Erreur;

  Erreur = AcquerirTrameNEC(RECEPTEUR_INFRAROUGE_Pin,&Adresse,&Donnee);    // Acquisition Trame
  if (Erreur == 0)                                                         // Erreur correcte ?
  {
    if (Adresse == AdresseNEC)                                             // Traitement Volume et Chaine
    {
      Volume = CalculerVolume(Donnee);                                     // Traitement Volume
      PiloterVolume(Volume);                                               // Action Volume
      Chaine = CalculerChaine(Donnee);                                     // Traitement Chaine
      PiloterChaine(Chaine);                                               // Action Chaine
   }
}
