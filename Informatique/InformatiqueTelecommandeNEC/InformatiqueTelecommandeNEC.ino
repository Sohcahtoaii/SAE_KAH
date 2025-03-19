/*********************************************************************/
// Sujet :   Programme de la telecommande NEC pour téléviseur        //
// Auteur :  AUGEREAU F.                                             //
// Date :    09/02/2018                                              //
// Version : 1.1                                                     //
/*********************************************************************/

// inclusion des fichiers header des bibliothèques de fonctions
#include <arduino.h>       // bibliotheque de fonctions arduino
#include "NEC.h"           // bibliotheque de fonctions NEC

// definition des constantes du programme
#define LED_INFRAROUGE_Pin             2      // n° de broche de la LED infrarouge
#define CMD_CHAINE_PLUS_Pin           A0      // n° de broche du bouton poussoir CHAINE_PLUS
#define CMD_CHAINE_MOINS_Pin          A1      // n° de broche du bouton poussoir CHAINE_MOINS
#define CMD_VOLUME_PLUS_Pin           A2      // n° de broche du bouton poussoir VOLUME_PLUS
#define CMD_VOLUME_MOINS_Pin          A3      // n° de broche du bouton poussoir VOLUME_MOINS
#define AdresseNEC                  0x20      // Adresse du protocole NEC

// declaration des fonctions du programme
uint8_t AcquerirCmdChainePlus(void);                                                                          // fonction d'acquisition
uint8_t AcquerirCmdChaineMoins(void);                                                                         // fonction d'acquisition
uint8_t AcquerirCmdVolumePlus(void);                                                                          // fonction d'acquisition
uint8_t AcquerirCmdVolumeMoins(void);                                                                         // fonction d'acquisition
uint8_t CalculerDonneeNEC(uint8_t ChainePlus, uint8_t ChaineMoins, uint8_t VolumePlus, uint8_t VolumeMoins);  // fonction de traitement


// definition des fonctions du programme
uint8_t AcquerirCmdChainePlus(void)                                     // AcquerirCmdChainePlus : fonction d'acquisition
{
  return digitalRead(CMD_CHAINE_PLUS_Pin);
}

uint8_t AcquerirCmdChaineMoins(void)                                    // AcquerirCmdChaineMoins : fonction d'acquisition
{
  return digitalRead(CMD_CHAINE_MOINS_Pin);
}

uint8_t AcquerirCmdVolumePlus(void)                                     // AcquerirCmdVolumePlus : fonction d'acquisition
{
  return digitalRead(CMD_VOLUME_PLUS_Pin);
}

uint8_t AcquerirCmdVolumeMoins(void)                                    // AcquerirCmdVolumeMoins : fonction d'acquisition
{
  return digitalRead(CMD_VOLUME_MOINS_Pin);
}


uint8_t CalculerDonneeNEC(uint8_t ChainePlus, uint8_t ChaineMoins, uint8_t VolumePlus, uint8_t VolumeMoins)   // CalculerDonneeNEC : fonction de traitement
{
  uint8_t DonneeNEC;
  if (ChaineMoins == HIGH)
    DonneeNEC = 0x45;               // Appui sur CHAINE MOINS
  if (ChainePlus == HIGH)
    DonneeNEC = 0xC5;               // Appui sur CHAINE PLUS
  if (VolumeMoins == HIGH)
    DonneeNEC = 0x85;               // Appui sur VOLUME MOINS
  if (VolumePlus == HIGH)
    DonneeNEC = 0x05;               // Appui sur VOLUME PLUS
  return DonneeNEC;
}


void setup()
{
  // Initialisation du sens de transfert de l'information des broches de type GPIO
  pinMode(CMD_CHAINE_PLUS_Pin,  INPUT);   // broche GPIO configuree en entree
  pinMode(CMD_CHAINE_MOINS_Pin, INPUT);   // broche GPIO configuree en entree
  pinMode(CMD_VOLUME_PLUS_Pin,  INPUT);   // broche GPIO configuree en entree
  pinMode(CMD_VOLUME_MOINS_Pin, INPUT);   // broche GPIO configuree en entree
  pinMode(LED_INFRAROUGE_Pin,   OUTPUT);  // broche GPIO configuree en sortie
}


void loop()
{
  uint8_t ChainePlus;
  uint8_t ChaineMoins;
  uint8_t VolumePlus;
  uint8_t VolumeMoins;
  uint8_t DonneeNEC;

  ChainePlus = AcquerirCmdChainePlus();                                           // Acquisition bouton poussoir CHAINE PLUS
  ChaineMoins = AcquerirCmdChaineMoins();                                         // Acquisition bouton poussoir CHAINE MOINS
  VolumePlus = AcquerirCmdVolumePlus();                                           // Acquisition bouton poussoir VOLUME PLUS
  VolumeMoins = AcquerirCmdVolumeMoins();                                         // Acquisition bouton poussoir VOLUME MOINS
  if ((ChainePlus == HIGH) || (ChaineMoins == HIGH) || (VolumePlus == HIGH) || (VolumeMoins == HIGH))
  {
    DonneeNEC = CalculerDonneeNEC(ChainePlus,ChaineMoins,VolumePlus,VolumeMoins); // Traitement VOLUME et CHAINE
    GenererTrameNEC(LED_INFRAROUGE_Pin,AdresseNEC,DonneeNEC);                     // Action VOLUME et CHAINE
  }
  else
  {
  }
}

