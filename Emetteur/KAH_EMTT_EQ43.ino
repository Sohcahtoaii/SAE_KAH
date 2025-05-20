/*************************************************************************************************************************************/
// Sujet :   Programme de l'émetteur du projet KAH                                                                                   //
// Equipe :  EQ43                                                                                                                  //
// Date :    13/03/2025                                                                                                              //
// Version : 1                                                                                                                  //
/*************************************************************************************************************************************/

// Inclusion des fichiers header des bibliothèques de fonctions Arduino
#include <stdint.h>         // Permet d'utiliser des types de données entiers avec des tailles spécifiques comme uint8_t (8 bits), uint16_t (16 bits), etc.
#include <arduino.h>        // La bibliothèque de base Arduino qui inclut des fonctions comme analogRead, digitalRead, etc.
#include "NEC.h"            // Inclusion d'un fichier d'entête spécifique au protocole NEC (probablement pour la gestion de l'envoi infrarouge NEC)

// Définition des constantes du projet
#define PotentiometreVitesse_Pin     A0      // Pin analogique A0 pour le potentiomètre de la vitesse (à modifier selon le câblage)
#define PotentiometreDirection_Pin   A1       // Pin analogique A1 pour le potentiomètre de la direction (à modifier selon le câblage)
#define BoutonPoussoir_Pin           9        // Pin numérique 8 pour le bouton poussoir 
#define LEDInfrarouge_Pin            11        // Pin numérique 9 pour la LED infrarouge (à modifier selon la configuration du projet)
#define LEDverte                      A5       // Pin numérique 9 pour la LED infrarouge
#define NumeroEquipe                 0x43    // Identifiant unique de l'équipe (0x52 en hexadécimal, à personnaliser)

// Définition des fonctions d'acquisition
// Fonction pour obtenir la valeur du potentiomètre de la vitesse
uint16_t AcquerirPotentiometreVitesse(void) {     
  uint16_t Aq_vitesse = map(analogRead(PotentiometreVitesse_Pin), 0, 1024, 0, 7);
  return Aq_vitesse;  // Lit la valeur analogique sur la pin A0 et retourne la valeur lue (de 0 à 1023)
}

// Fonction pour obtenir la valeur du potentiomètre de la direction
uint16_t AcquerirPotentiometreDirection(void) {   
  uint16_t Aq_direction = map(analogRead(PotentiometreDirection_Pin), 0, 1024, 0, 31);  // Lit la valeur du potentiomètre de direction et la mappe sur une plage de 0 à 31
  return Aq_direction;  // Retourne la valeur mappée
}

// Fonction pour obtenir l'état du bouton poussoir
uint8_t AcquerirBoutonPoussoir() {
  // Retourne 1 si le bouton est enfoncé, 0 si le bouton est relâché
  if (digitalRead(BoutonPoussoir_Pin) == 1) {
    return 0;  // Le bouton est relâché
  } else {
    return 1;  // Le bouton est enfoncé
  }
}


// Définition des fonctions de traitement
// Fonction pour calculer les données NEC à partir de la vitesse et de la direction
uint8_t CalculerDonneeNEC(uint16_t Vitesse, uint16_t Direction) { 
  static int Donnee[8] = {0};  // Tableau pour stocker les 8 bits de données
  int drctin = (Vitesse << 5) | (Direction & 0x1F);  // Combine la vitesse et la direction dans une seule valeur (3 bits pour la vitesse et 5 bits pour la direction)
  for (int i = 7; i >= 0; i--) {
    Donnee[i] = ((drctin >> i) & 1);  // Remplie le tableau Donnee avec les bits de la donnée calculée
  }
  return Donnee;  // Retourne les 8 bits sous forme de tableau (probablement à convertir en un octet plus tard)
}

// Fonction pour calculer l'adresse NEC à partir de l'état du Klaxon et du numéro de l'équipe
uint8_t CalculerAdresseNEC(uint8_t Klaxon) { 
  static int Adresse[8] = {0};  // Tableau pour stocker les 8 bits de l'adresse
  int adrss = (Klaxon << 7) | (NumeroEquipe & 0x7F);  // Combine l'état du Klaxon (1 bit) avec le numéro de l'équipe (7 bits)
  for (int i = 7; i >= 0; i--) {
    Adresse[i] = ((adrss >> i) & 1);  // Remplie le tableau Adresse avec les bits de l'adresse calculée
  }
  return Adresse;  // Retourne l'adresse (probablement à convertir en un octet plus tard)
}

// Définition des fonctions principales
// Fonction d'initialisation du système
void setup(void) {
  Serial.begin(9600);
  pinMode(LEDInfrarouge_Pin,OUTPUT);// Initialise la communication série à 9600 bauds pour afficher des informations sur le moniteur série
  pinMode(LEDverte,OUTPUT);//
  digitalWrite(LEDverte, HIGH);
  
  // Cette section peut être utilisée pour initialiser d'autres paramètres comme les pins ou les périphériques
}

// Fonction principale appelée en boucle
void loop(void) {
  static uint8_t donnee_prec = 0x00;
  uint16_t Vitesse = AcquerirPotentiometreVitesse();  // Lit la valeur du potentiomètre de la vitesse
  uint16_t Direction = AcquerirPotentiometreDirection();  // Lit la valeur du potentiomètre de direction 
  uint8_t Klaxon = AcquerirBoutonPoussoir();
  uint8_t adresse = CalculerAdresseNEC(Klaxon);  // Calcule l'adresse (8 bits)
  Serial.print("adresse :");
  Serial.println(adresse);
  uint8_t donnee = CalculerDonneeNEC(Vitesse, Direction);  // Calcule les données (8 bits)
  Serial.print("donnee :");
  Serial.println(donnee);
  if (donnee_prec == donnee){
    delay(333);
    GenererTrameNEC(17, adresse, donnee);
    Serial.println("Envoyé avec un délai de 333ms");
  }
  else{
    delay(108);
    GenererTrameNEC(17, adresse, donnee);
    Serial.println("Envoyé avec un délai de 108ms");
  }
  Serial.print("Donnee_prec : ");
  Serial.println(donnee_prec);
  Serial.print("Donnee : ");
  Serial.println(donnee);
  Serial.print("Vitesse : ");
  Serial.println(Vitesse);
  donnee_prec = donnee; // sauvegarde l'adresse précédente
    // Envoie la trame NEC en utilisant les données et l'adresse calculées

}
