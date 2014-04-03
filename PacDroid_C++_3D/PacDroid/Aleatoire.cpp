// Aleatoire.cpp

#include "Aleatoire.h"
#include <iostream>

using namespace std;

/**
 * Renvoie un nombre entier au hasard entre min et max
 * @param min Valeur minimum dans l'interval choisi
 * @param max Valeur maximum dans l'interval choisi
 * @return int Entier au hasard compris entre un minimum et un maximum
 */
int Aleatoire::hasardi(int min, int max) {
	// rand() renvoie une valeur entre 0 et RAND_MAX, qui est une constante fixee par le systeme.
    // Donc, le quotient rand() / RAND_MAX est compris entre 0 et 1. Le (float) sert a ce que ce quotient ne soit pas arrondi.
    // On multiplie ensuite cette valeur aleatoire par la taille de l'intervalle souhaite et on ajoute la valeur de la borne inferieure.
    // On transforme ensuite la valeur obtenue en un entier via le (int).
    return (int) (min + ((float) rand() / RAND_MAX * (max - min + 1)));
}

/**
 * Renvoie un nombre à virgule flottante au hasard entre min et max
 * @param min Valeur minimum dans l'interval choisi
 * @param max Valeur maximum dans l'interval choisi
 * @return float Float au hasard compris entre un minimum et un maximum
 */
float Aleatoire::hasardf(float min, float max) {
	// rand() renvoie une valeur entre 0 et RAND_MAX, qui est une constante fixee par le systeme.
    // Donc, le quotient rand() / RAND_MAX est compris entre 0 et 1. Le (float) sert a ce que ce quotient ne soit pas arrondi.
    // On multiplie ensuite cette valeur aleatoire par la taille de l'intervalle souhaite et on ajoute la valeur de la borne inferieure.
    return min + ((float) rand() / RAND_MAX * (max - min + 1.0f));
}

/**
 * Renvoie une couleur générée aléatoirement
 * @return Couleur couleur défini au hasard
 */
Couleur Aleatoire::couleur() {
	float couleur[3];
	for (int i = 0; i < 3; i++) {
		couleur[i] = hasardf(0.0f, 1.0f);
	}
	return Couleur(couleur[0], couleur[1], couleur[2]);
}