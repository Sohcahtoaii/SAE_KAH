/*************************************************************************************************************************************/
// Sujet :   Programme de l'émetteur du projet KAH                                                                                   //
// Equipe :  EQ43                                                                                                                  //
// Date :    13/03/2025                                                                                                              //
// Version : 1                                                                                                                  //
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
#define Buzzer_Pin                           // à modifier
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
void PiloterLedMarche(uint8_t etat){ //active ou non la LED marche/arret: 0 = éteint; 1 = allumé
if (etat == 0){
  digitalWrite(LEDMarche, LOW);
}
else{
  digitalWrite(LEDMarche, HIGH);
}
  
}
void PiloterLedInfrarouge(uint8_t numer_led, char etat){


for( int i; i<=8 ;i--){
  int Sadresse[8] = CalculerAdresseNEC(Klaxon);
  digitalWrite(LEDInfrarouge_Pin,Sadressse[i]);
  delay();
  digitalWrite(LEDInfrarouge_Pin,LOW);
  delay();
}
for( int i; i<=8 ;i--){
  int Sdonnee[8] = CalculerDonneeNEC(Vitesse,Direction) ;
  digitalWrite(LEDInfrarouge_Pin,Sdonnee[i]);
  delay();
  digitalWrite(LEDInfrarouge_Pin,LOW);
  delay();
}
}

void PiloterBuzzer(uint16_t etat){
if (etat == 0){
  return 1;        //ETEINDRE LE BUZZER DANS LE LOOP
}
  else{
  return 0;
  }
}

// definition des fonctions principales
void setup(void) {
  Serial.begin(9600);
// à compléter
}

void loop(void) {
  uint16_t Vitesse = AcquerirPotentiometreVitesse();
  uint16_t Direction = AcquerirPotentiometreDirection();
  uint8_t Klaxon = PiloterBuzzer(frequence);
  uint8_t DonneeNEC =  CalculerDonneeNEC(Vitesse,Direction);
  uint8_t AdresseNEC = CalculerAdresseNEC(Klaxon);
//  ...             // à compléter
}
