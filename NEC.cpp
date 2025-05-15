/*************************************************************************************************************************************/
// Sujet :   Definition de la bibliotheque de fonctions NEC                                                                          //
// Auteur :  AUGEREAU F.                                                                                                             //
// Date :    13/03/2023                                                                                                              //
// Version : 1.4.2                                                                                                                   //
/*************************************************************************************************************************************/
//                                                                                                                                   //
// 2 fonctions sont fournies dans cette bibliotheque NEC :                                                                           //
//                                                                                                                                   //
//   => fonction d'emission d'une trame NEC                                                                                          //
//     syntaxe : void GenererTrameNEC(int Broche, uint8_t Adresse, uint8_t Donnee);                                                  //
//          Broche est la valeur de la broche Arduino sur laquelle est connectee la LED d'émission infrarouge                        //
//          Adresse est la valeur de l'adresse NEC à transmettre dans la trame NEC                                                   //
//          Donnee est la valeur de la donnee NEC à transmettre dans la trame NEC                                                    //
//                                                                                                                                   //
//   => fonction de reception d'une trame NEC                                                                                        //
//     syntaxe : int8_t AcquerirTrameNEC(int Broche, uint8_t* Adresse, uint8_t* Donnee);                                             //
//          AcquerirTrameNEC retourne une valeur d'erreur (0 : trame NEC valide ; -1 : erreur de reception NEC ; -2 : trame absente) //
//          Broche est la valeur de la broche Arduino sur laquelle est connectee le recepteur infrarouge                             //
//          *Adresse retourne la valeur de l'adresse NEC incluse dans la trame NEC recue (passage de la valeur par pointeur)         //
//          *Donnee retourne la valeur de la donnee NEC incluse dans la trame NEC recue (passage de la valeur par pointeur)          //
//                                                                                                                                   //
/*************************************************************************************************************************************/


// inclusion des fichiers header des bibliothèques de fonctions Arduino
#include <stdint.h>
#include <arduino.h>
#include "NEC.h"

// definition des fonctions d'emission de la bibliotheque NEC
void GenererTrameNEC(int Broche, uint8_t Adresse, uint8_t Donnee)   // GenererTrameNEC : fonction d'action
{
  GenererEnteteNEC(Broche);               // generation du header NEC
  GenererOctetNEC(Broche, Adresse);       // generation de l'adresse NEC
  GenererOctetNEC(Broche, ~Adresse);      // generation de l'adresse_barre NEC
  GenererOctetNEC(Broche, Donnee);        // generation de la donnee NEC
  GenererOctetNEC(Broche, ~Donnee);       // generation de la donnee_barre NEC
  GenererBurst562usNEC(Broche);           // burst final d'une trame NEC
  delay(41);                              // delai inter-trame de 40,5ms
}

void GenererEnteteNEC(int Broche)                                   // GenererEnteteNEC : fonction d'action
{
  GenererBurst9000usNEC(Broche);
  delayMicroseconds(4500);          // temps a l'etat bas apres entete du protocole NEC
}


void GenererBurst9000usNEC(int Broche)                              // GenererBurst9000usNEC : fonction d'action
{
  uint16_t i;
  for(i=0;i<342;i++)                // impulsions du protocole NEC pendant 9000 us
  {
    GenererImpulsion38kHzNEC(Broche);
  }
}

void GenererOctetNEC(int Broche, uint8_t Octet)               // GenererOctetNEC : fonction d'action
{
  int8_t i;
  for(i=7;i>=0;i--)
  {
    if ((Octet & (1 << i)) == 0)
      GenererBit0NEC(Broche);
    else
      GenererBit1NEC(Broche);
  }
}

void GenererBit0NEC(int Broche)                                     // GenererBit0NEC : fonction d'action
{
  GenererBurst562usNEC(Broche);
  delayMicroseconds(562);           // temps a l'etat bas pour un bit 0 du protocole NEC
}

void GenererBit1NEC(int Broche)                                     // GenererBit1NEC : fonction d'action
{
  GenererBurst562usNEC(Broche);
  delayMicroseconds(1687);          // temps a l'etat bas pour un bit 1 du protocole NEC
}

void GenererBurst562usNEC(int Broche)                               // GenererBurst562usNEC : fonction d'action
{
  int i;
  for(i=0;i<22;i++)                 // 22 impulsions du protocole NEC
  {
    GenererImpulsion38kHzNEC(Broche);
  }
}

void GenererImpulsion38kHzNEC(int Broche)                           // GenererImpulsion38kHzNEC : fonction d'action
{
  register uint8_t i;
  AllumerDiodeInfrarouge(Broche);
  for(i = 0 ; i < 35 ; i++)         // valeur ajustee a l'oscilloscope avec un compilateur Arduino version 1.8.9
    asm("nop");                     // attente de 8.8 us
  EteindreDiodeInfrarouge(Broche);
  for(i = 0 ; i < 66 ; i++)         // valeur ajustee a l'oscilloscope avec un compilateur Arduino version 1.8.9
    asm("nop");                     // attente de 17.5 us
}

inline void AllumerDiodeInfrarouge(int Broche)                             // AllumerDiodeInfrarouge : fonction d'action
{
  if (Broche ==  0) PORTD = PORTD | 0x01; else ;
  if (Broche ==  1) PORTD = PORTD | 0x02; else ;
  if (Broche ==  2) PORTD = PORTD | 0x04; else ;
  if (Broche ==  3) PORTD = PORTD | 0x08; else ;
  if (Broche ==  4) PORTD = PORTD | 0x10; else ;
  if (Broche ==  5) PORTD = PORTD | 0x20; else ;
  if (Broche ==  6) PORTD = PORTD | 0x40; else ;
  if (Broche ==  7) PORTD = PORTD | 0x80; else ;
  if (Broche ==  8) PORTB = PORTB | 0x01; else ;
  if (Broche ==  9) PORTB = PORTB | 0x02; else ;
  if (Broche == 10) PORTB = PORTB | 0x04; else ;
  if (Broche == 11) PORTB = PORTB | 0x08; else ;
  if (Broche == 12) PORTB = PORTB | 0x10; else ;
  if (Broche == 13) PORTB = PORTB | 0x20; else ;
  if (Broche == A0) PORTC = PORTC | 0x01; else ;
  if (Broche == A1) PORTC = PORTC | 0x02; else ;
  if (Broche == A2) PORTC = PORTC | 0x04; else ;
  if (Broche == A3) PORTC = PORTC | 0x08; else ;
  if (Broche == A4) PORTC = PORTC | 0x10; else ;
  if (Broche == A5) PORTC = PORTC | 0x20; else ;
}

inline void EteindreDiodeInfrarouge(int Broche)                            // EteindreDiodeInfrarouge : fonction d'action
{
  if (Broche ==  0) PORTD = PORTD & 0xFE; else ;
  if (Broche ==  1) PORTD = PORTD & 0xFD; else ;
  if (Broche ==  2) PORTD = PORTD & 0xFB; else ;
  if (Broche ==  3) PORTD = PORTD & 0xF7; else ;
  if (Broche ==  4) PORTD = PORTD & 0xEF; else ;
  if (Broche ==  5) PORTD = PORTD & 0xDF; else ;
  if (Broche ==  6) PORTD = PORTD & 0xBF; else ;
  if (Broche ==  7) PORTD = PORTD & 0x7F; else ;
  if (Broche ==  8) PORTB = PORTB & 0xFE; else ;
  if (Broche ==  9) PORTB = PORTB & 0xFD; else ;
  if (Broche == 10) PORTB = PORTB & 0xFB; else ;
  if (Broche == 11) PORTB = PORTB & 0xF7; else ;
  if (Broche == 12) PORTB = PORTB & 0xEF; else ;
  if (Broche == 13) PORTB = PORTB & 0xDF; else ;
  if (Broche == A0) PORTC = PORTC & 0xFE; else ;
  if (Broche == A1) PORTC = PORTC & 0xFD; else ;
  if (Broche == A2) PORTC = PORTC & 0xFB; else ;
  if (Broche == A3) PORTC = PORTC & 0xF7; else ;
  if (Broche == A4) PORTC = PORTC & 0xEF; else ;
  if (Broche == A5) PORTC = PORTC & 0xDF; else ;
}


// definition des fonctions de reception de la bibliotheque NEC
int8_t AcquerirTrameNEC(int Broche, uint8_t* ptr_Adresse, uint8_t* ptr_Donnee) // AcquerirTrameNEC : fonction d'acquisition
{
  int8_t entete;
  int16_t adresse;
  int16_t adresse_barre;
  int16_t donnee;
  int16_t donnee_barre;
  int32_t temps;
  *ptr_Adresse = 0x00;
  *ptr_Donnee = 0x00;
  entete = AcquerirEnteteNEC(Broche);
  if (entete < 0)                                       // Controle de timing
    return entete;                                      // Erreur de timing
  adresse = AcquerirOctetNEC(Broche);
  if (adresse < 0)                                      // Controle de timing
    return adresse;                                     // Erreur de timing
  adresse_barre = AcquerirOctetNEC(Broche);
  if (adresse_barre < 0)                                // Controle de timing
    return adresse_barre;                               // Erreur de timing
  donnee = AcquerirOctetNEC(Broche);
  if (donnee < 0)                                       // Controle de timing
    return donnee;                                      // Erreur de timing
  donnee_barre = AcquerirOctetNEC(Broche);
  if (donnee_barre < 0)                                 // Controle de timing
    return donnee_barre;                                // Erreur de timing
  if ((adresse + adresse_barre) != 0xFF)                // Controle de transmission
    return -1;                                          // Erreur de transmission
  if ((donnee + donnee_barre) != 0xFF)                  // Controle de transmission
    return -1;                                          // Erreur de transmission
  if ((temps = AcquerirFrontDescendantNEC(Broche)) < 0) // Controle de timing
    return temps;                                       // Erreur de timing
  *ptr_Adresse = adresse;
  *ptr_Donnee = donnee;
  return 0;                                             // Trame correcte
}

int8_t AcquerirEnteteNEC(int Broche)                                   // AcquerirEnteteNEC : fonction d'acquisition
{
  int32_t temps;
  if ((temps = AcquerirFrontMontantNEC(Broche)) < 0)    // Acquisition du front montant
    return temps;                                       // Erreur de timing
  if ((temps = AcquerirFrontDescendantNEC(Broche)) < 0) // Acquisition du front descendant
    return temps;                                       // Erreur de timing
  if((temps < 8100) || (temps > 9900))                  // Controle de timing       9000us du protocole NEC (-/+10%)
    return -1;                                          // Erreur de timing
  temps = AcquerirFrontMontantNEC(Broche);              // Acquisition du front montant
  if((temps < 4050) || (temps > 4950))                  // Controle de timing       4500us du protocole NEC (-/+10%)
    return -1;                                          // Erreur de timing
  return 0;                                             // Entete correcte
}

int16_t AcquerirOctetNEC(int Broche)                                    // AcquerirOctetNEC : fonction d'acquisition
{
  int8_t i;
  int8_t bit;
  int16_t octet;
  octet = 0;
  for(i=7;i>=0;i--)                                     // boucle de construction de l'octet NEC
  {
    bit = AcquerirBitNEC(Broche);                       // Acquisition bit NEC
    if (bit < 0)                                        // Erreur de timing ?
      return bit;                                       // Erreur de timing
    octet = octet | (bit << i);                         // Construction de l'octet NEC
  }
  return octet;
}

int8_t AcquerirBitNEC(int Broche)                                       // AcquerirBitNEC : fonction d'acquisition
{
  int32_t temps;
  if ((temps = AcquerirFrontDescendantNEC(Broche)) < 0) // Acquisition du front descendant
    return temps;                                       // Erreur de timing
  if((temps < 281) || (temps > 843))                    // Controle de timing       562us du protocole NEC (-/+281us)
    return -1;                                          // Erreur de timing
  if ((temps = AcquerirFrontMontantNEC(Broche)) < 0)    // Acquisition du front montant
    return temps;
  if((temps > 281) && (temps < 843))                    // Controle de timing       562us du protocole NEC (-/+281us)
    return 0;                                           // Bit 0
  if((temps > 1405) && (temps < 1967))                  // Controle de timing       1686us du protocole NEC (-/+281us)
    return 1;                                           // Bit 1
  return -1;                                            // Sinon erreur de timing
}

int32_t AcquerirFrontMontantNEC(int Broche)                              // AcquerirFrontMontantNEC : fonction d'acquisition
{
  uint32_t TempsFrontPrecedent, Temps;
  uint8_t Infrarouge;
  Infrarouge = 0;
  TempsFrontPrecedent = micros();
  while(((Temps = micros() - TempsFrontPrecedent) < 500000) && ((Infrarouge = AcquerirInfrarouge(Broche)) == 0));
  if (Infrarouge == 1)
    if (Temps < 200)
      return -1;
    else
      return (int32_t)Temps;
  else
    return -2;
}

int32_t AcquerirFrontDescendantNEC(int Broche)                           // AcquerirFrontDescendantNEC : fonction d'acquisition
{
  uint32_t TempsFrontPrecedent, Temps;
  uint8_t Infrarouge;
  Infrarouge = 1;
  TempsFrontPrecedent = micros();
  while(((Temps = micros() - TempsFrontPrecedent) < 500000) && ((Infrarouge = AcquerirInfrarouge(Broche)) == 1));
  if (Infrarouge == 0)
    if (Temps < 200)
      return -1;
    else
      return (int32_t)Temps;
  else
    return -2;
}

uint8_t AcquerirInfrarouge(int Broche)
{
  uint8_t valeur = 0;
  if (Broche ==  0) if ((PIND & 0x01) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  1) if ((PIND & 0x02) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  2) if ((PIND & 0x04) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  3) if ((PIND & 0x08) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  4) if ((PIND & 0x10) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  5) if ((PIND & 0x20) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  6) if ((PIND & 0x40) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  7) if ((PIND & 0x80) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  8) if ((PINB & 0x01) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche ==  9) if ((PINB & 0x02) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == 10) if ((PINB & 0x04) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == 11) if ((PINB & 0x08) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == 12) if ((PINB & 0x10) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == 13) if ((PINB & 0x20) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A0) if ((PINC & 0x01) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A1) if ((PINC & 0x02) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A2) if ((PINC & 0x04) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A3) if ((PINC & 0x08) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A4) if ((PINC & 0x10) == 0) valeur = 1; else valeur = 0; else ;
  if (Broche == A5) if ((PINC & 0x20) == 0) valeur = 1; else valeur = 0; else ;
  return valeur;
}
