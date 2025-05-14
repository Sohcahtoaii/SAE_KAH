/*************************************************************************************************************************************/
// Sujet :   Programme du récepteur du projet KAH
// Equipe :  EQ43
// Date :    19/03/2025
// Version : 1
/*************************************************************************************************************************************/

#include <stdint.h>
#include <arduino.h>
#include "NEC.h"   // Bibliothèque pour décoder les trames infrarouges NEC
#include <Servo.h> // Bibliothèque pour contrôler les servomoteurs

// Définition des constantes
#define Servomoteur_Pin 12          // Broche du servomoteur de direction
#define Moteur_Pin 5                // Broche du servomoteur de propulsion
#define Buzzer_Pin 11               // Broche du buzzer
#define LedBleue_Pin 4              // Broche de la LED bleue
#define LedVerte_Pin 6              // Broche de la LED verte
#define NumeroEquipe 0x2B           // Numéro d'équipe (67 en décimal)
#define RECEPTEUR_INFRAROUGE_Pin 2  // Broche du récepteur infrarouge
#define TimingMinPWM         1000  // definition du temps (en us) a l'etat haut de la commande du servomoteur correspondant a un angle de 0 degres
#define TimingMaxPWM         2000  // definition du temps (en us) a l'etat haut de la commande du servomoteur correspondant a un angle de 180 degres

// Objets globaux
Servo myservo;  // Servomoteur pour la direction
Servo moteur;   // Servomoteur pour la propulsion
uint8_t Adresse = 0, Donnee = 0;  // Variables pour stocker l'adresse et les données reçues
uint8_t Vitesse = 0, Direction = 0, Klaxon = 0, LedB = 0, Moteur = 0; // Variables de contrôle des actionneurs
static unsigned long T1 = 0, T = 0; // Variables pour gérer le temps
// Définition des fonctions

//Contrôle la validité de la trame
void ValiditeTrameNEC() {
  // Acquisition de la trame infrarouge NEC
  int8_t Erreur = AcquerirTrameNEC(RECEPTEUR_INFRAROUGE_Pin, &Adresse, &Donnee);
  // Vérifie si la trame est valide et si l'adresse correspond à celle de l'équipe
  if (Erreur == 0 && ExtraireNumeroEquipe(Adresse) == NumeroEquipe) { 
    Vitesse = CalculerVitesseMoteur(Donnee); // Extrait la vitesse
    Direction = CalculerDirectionServomoteur(Donnee); // Extrait la direction
    Klaxon = ExtraireEtatBuzzer(Adresse); // Vérifie si le buzzer doit être activé
    LedB = 1; // Active la LED bleue
    Moteur = 1; // Active le moteur
    T1 = millis(); // Réinitialise le timer de sécurité
  } 
  else if (millis() - T1 >= 333) { // Si aucune trame correcte reçue depuis plus de 333 ms
    Securite();
    Moteur = 0; // Active la sécurité
    T1 = millis(); // Réinitialise le timer
  }
}

// Extrait le numéro d'équipe à partir de l'adresse reçue
uint8_t ExtraireNumeroEquipe(uint8_t Adresse) {
  return Adresse & 0x7F; // Extrait les 7 bits de poids faible pour obtenir le numéro d'équipe
}

// Calcule l'angle du servomoteur en fonction des données reçues
uint8_t CalculerDirectionServomoteur(uint8_t Donnee) {
  uint8_t direction = Donnee & 0x1F; // Extrait les 5 bits de direction (0 à 31)
  return map(direction, 0, 31, 0, 180); // Convertit cette valeur en un angle de 0° à 180°
}

// Calcule la vitesse du moteur en fonction des données reçues
uint8_t CalculerVitesseMoteur(uint8_t Donnee) {
  uint8_t vitesse = (Donnee >> 5) & 0x07; // Extrait les 3 bits de vitesse (0 à 7)
  return map(vitesse, 0, 7, 0, 180); // Convertit cette valeur en une plage de 0 à 180
}

// Extrait l'état du buzzer (ON/OFF) à partir de l'adresse reçue
uint8_t ExtraireEtatBuzzer(uint8_t Adresse) {
  return (Adresse >> 7) & 0x01; // Extrait le bit de poids fort (1er bit)
}

// Contrôle le servomoteur de direction
void PiloterServomoteur(uint8_t Direction) {
  myservo.write(Direction); // Définit l'angle du servomoteur
}

// Contrôle le moteur (ON/OFF et vitesse)
void PiloterMoteur(uint8_t Vitesse, uint8_t EtatMoteur) {
  moteur.write(EtatMoteur ? Vitesse : 0); // Si EtatMoteur est activé, applique la vitesse, sinon arrête le moteur
}

// Contrôle l'activation du buzzer
void PiloterBuzzer(uint8_t EtatBuzzer) {
  if (EtatBuzzer) {
    tone(Buzzer_Pin, 4000); // Active le buzzer à 4 kHz
  } else {
    noTone(Buzzer_Pin); // Désactive le buzzer
  }
}

// Contrôle l'état de la LED bleue
void PiloterLedBleue(uint8_t EtatLedBleue) {
  digitalWrite(LedBleue_Pin, EtatLedBleue ? LOW : HIGH); // Active (LOW) ou désactive (HIGH) la LED bleue
}

// Allume la LED verte pour indiquer que le système fonctionne
void LedIndicateur(uint8_t EtatLedVerte) {
  digitalWrite(LedVerte_Pin, EtatLedVerte ? LOW : HIGH);
}

// Fonction de sécurité en cas d'absence de signal valide
void Securite() {
  PiloterMoteur(0, 0); // Arrête le moteur
  PiloterLedBleue(0);  // Éteint la LED bleue
  Serial.println("Sécurité activée : moteur arrêté");
}

void setup() {
  Serial.begin(9600); // Initialisation de la communication série
  myservo.attach(Servomoteur_Pin,TimingMinPWM,TimingMaxPWM); // Attache le servomoteur à la broche définie
  moteur.attach(Moteur_Pin,TimingMinPWM,TimingMaxPWM);       // Attache le moteur à la broche définie
  pinMode(Buzzer_Pin, OUTPUT);     // Définit le buzzer en sortie
  pinMode(LedBleue_Pin, OUTPUT);   // Définit la LED bleue en sortie
  pinMode(LedVerte_Pin, OUTPUT);   // Définit la LED verte en sortie
}

void loop() {
  
  ValiditeTrameNEC(); // Vérifie la validité de la trame infrarouge et lance le traitement si valide
  // Contrôle des actionneurs
  PiloterServomoteur(Direction); // Applique la direction au servomoteur
  PiloterMoteur(Vitesse, Moteur); // Applique la vitesse au moteur
  PiloterBuzzer(Klaxon); // Active/désactive le klaxon
  PiloterLedBleue(LedB); // Active/désactive la LED bleue
  LedIndicateur(1); // Allume la LED verte pour indiquer que le système fonctionne
}
