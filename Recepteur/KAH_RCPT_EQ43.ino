/*************************************************************************************************************************************/
// Sujet :   Programme du récepteur du projet KAH                                                                                   //
// Equipe :  EQ43                                                                                                                //
// Date :    19/03/2025                                                                                                              //
// Version : 1                                                                                                                  //
/*************************************************************************************************************************************/

// inclusion des fichiers header des bibliothèques de fonctions Arduino
#include <stdint.h>    // Inclut les types de données standard comme uint8_t
#include <arduino.h>   // Bibliothèque standard pour Arduino
#include "NEC.h"       // Inclusion d'une bibliothèque spécifique pour l'interface infrarouge NEC
#include <Servo.h>     // Inclusion de la bibliothèque pour le contrôle du servomoteur
// definition des constantes du projet
#define Servomoteur_Pin              12     // Pin où le servomoteur est connecté
#define Moteur_Pin                    5      // Pin où le moteur est connecté
#define Buzzer_Pin                   11     // Pin où le buzzer est connecté
#define LedBleue_Pin                  4     // Pin pour la LED bleue
#define LedVerte_Pin                  6     // Pin pour la LED verte
#define NumeroEquipe               0x43     // Adresse de l'équipe (peut être utilisée pour identifier l'équipe)

// Définition des fonctions d'acquisition (elles sont importées depuis la bibliothèque NEC)
                    // inclus dans la bibliothèque NEC


uint8_t ExtraireNumeroEquipe(uint8_t Adresse) { // retourne une valeur : [ ? ; ? ]
    int NumeroEquipe = Adresse & NumeroEquipe;  // Masque pour extraire les 4 bits de poids faible
    return NumeroEquipe;  // Retourne le numéro de l'équipe
     

// efinition des fonctions de traitement
uint8_t CalculerDirectionServomoteur(uint8_t Donnee) { 
uint8_t direction = Donnee & 0x1F;  // Masque pour extraire les 5 bits de direction
direction=map(direction, 0 ,, toLow, toHigh);
  return direction;  // Retourne la direction du servomoteur
}

// definition des fonctions de traitement
uint8_t CalculerVitesseMoteur(uint8_t Donnee) { 
  Donnee = Donnee >>>5;  // Décalage de 5 bits vers la droite pour extraire les 3 bits de vitesse
  uint8_t speed= map(Donnee, 0, 7, 0, 180);
  return speed;  // Retourne la vitesse du moteur
}

// definition des fonctions de traitement
uint8_t ExtraireEtatBuzzer(uint8_t Adresse) { 
  int EtatBuzzer = (Adresse >> 7);  // Décalage de 7 bits vers la droite pour extraire l'état du buzzer
  return EtatBuzzer;  // Retourne l'état du buzzer
}



// definition des fonctions d'action
void PiloterServomoteur(uint8_t Direction) { 
  analogWrite(Servomoteur_Pin,Direction);
}

void PiloterMoteur(uint8_t Vitesse, uint8_t EtatMoteur) { // Contrôle le moteur en fonction de sa vitesse et de son état
  if (EtatMoteur == 1){  // Si le moteur est ordonné d'être actif
    analogWrite(Moteur_Pin, Vitesse);  // Envoie un signal PWM pour définir la vitesse
  }
    else{
      analogWrite(Moteur_Pin,0);
    }
}



void PiloterBuzzer(uint8_t EtatBuzzer) { // Contrôle l'état du buzzer
  if (EtatBuzzer == 1) {  // Si le buzzer doit être actif
    tone(11, 4000);   // Génère un signal carré à 4kHz sur la pin 11 (buzzer)
  } 
  else {
    noTone();    // Arrête le buzzer si l'état est 0
  }
}

void PiloterLedBleue(uint8_t EtatLedBleue) {  // Contrôle l'état de la LED bleue
  if (EtatLedBleue == 1) {  // Si la LED bleue doit être allumée
    digitalWrite(4, LOW);   // Allume la LED bleue
  } 
  else {
    digitalWrite(4, HIGH);  // Éteint la LED bleue
  }
}

void PiloterLedVerte(uint8_t EtatLedVerte) {  // Contrôle l'état de la LED verte
  digitalWrite(6, LOW);   // Allume la LED verte (LOW sur la pin 6)
}

// Définition des fonctions principales

void setup(void) {  // Fonction d'initialisation qui s'exécute une seule fois au démarrage
  Serial.begin(9600);  // Initialisation de la communication série pour afficher des informations de débogage
  pinMode(12, OUTPUT);  // Configuration de la pin 12 comme une sortie pour le servomoteur
  pinMode(5, OUTPUT);   // Configuration de la pin 5 comme une sortie pour le moteur
  pinMode(11, OUTPUT);  // Configuration de la pin 11 comme une sortie pour le buzzer
  pinMode(4, OUTPUT);   // Configuration de la pin 4 comme une sortie pour la LED bleue
  pinMode(6, OUTPUT);   // Configuration de la pin 6 comme une sortie pour la LED verte
}

void loop(void) {  // Fonction principale qui s'exécute en boucle
  uint8_t Donnee;  // Variable pour stocker les données reçues
  uint8_t Adresse; // Variable pour stocker l'adresse des données
  uint8_t Vitesse; // Variable pour stocker la vitesse du moteur
  uint8_t Direction; // Variable pour stocker la direction du servomoteur
  uint8_t Klaxon;   // Variable pour stocker l'état du buzzer (Klaxon)
  uint8_t Erreur;   // Variable pour stocker l'état de l'acquisition des données
  uint8_t LedB;     // Variable pour l'état de la LED bleue
  uint8_t Moteur;   // Variable pour l'état du moteur
  unsigned long T;  // Variable pour stocker un timer pour l'affichage périodique
  unsigned long T1; // Variable pour stocker un timer pour la gestion de la trame correcte

  // Acquisition et traitement des données infrarouges
  Erreur = AcquerirTrameNEC(RECEPTEUR_INFRAROUGE_Pin, &Adresse, &Donnee);  // Acquérir la trame infrarouge
  if (Erreur == 0 & Adresse == AdresseNEC) {  // Si l'acquisition de la trame est réussie et l'adresse reçue correspond à l'adresse du récepteur
    LedB = 1;  // Allumer la LED bleue
    Moteur = 1;  // Activer le moteur
    T1 = millis();  // Remise à zéro du timer de trame correcte
  }
  else {
    // Si aucune trame correcte n'a été reçue dans les 333ms
    if (millis() - T1 == 333) {
      LedB = 0;  // Éteindre la LED bleue
      Moteur = 0;  // Désactiver le moteur
      T1 = millis();  // Remise à zéro du timer
    }
  }
}

  // Appel des fonctions pour piloter les composants
  PiloterServomoteur(Direction);  // Piloter le servomoteur
  PiloterMoteur(Vitesse, Moteur); // Piloter le moteur
  PiloterBuzzer(Klaxon);         // Piloter le buzzer
  PiloterLedBleue(LedB);         // Piloter la LED bleue
  PiloterLedVerte(1);            // Allumer la LED verte

  // Affichage des données sur le moniteur série toutes les 5 secondes
  if (millis() - T == 5000) {
    Serial.print("Donnee: ");  // Afficher la donnée
    Serial.println(Donnee);
    Serial.print("Adresse: ");  // Afficher l'adresse
    Serial.println(Adresse);
    Serial.print("Vitesse: ");  // Afficher la vitesse
    Serial.println(Vitesse);
    Serial.print("Direction: "); // Afficher la direction
    Serial.println(Direction);
    Serial.print("Klaxon: ");    // Afficher l'état du klaxon
    Serial.println(Klaxon);
    Serial.print("Erreur: ");    // Afficher l'état d'erreur
    Serial.println(Erreur);
  }
}
