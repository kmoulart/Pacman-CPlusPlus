// Couleur.cpp

#include "Couleur.h"

/**
 * Constructeur par defaut
 */
Couleur::Couleur() {
	this->rouge = 1;
	this->vert = 1;
	this->bleu = 1;
	this->alpha = 0;
}

/**
 * Constructeur de Couleur en spécifiant les couleurs RGB
 * @param rouge Valeur rouge
 * @param vert Valeur verte
 * @param bleu Valeur bleu
 */
Couleur::Couleur(float rouge, float vert, float bleu) {
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
	this->alpha = 0;
}

/**
 * Constructeur de Couleur en spécifiant les couleurs RGBA
 * @param rouge Valeur rouge
 * @param vert Valeur verte
 * @param bleu Valeur bleu
 * @param alpha Valeur alpha
 */
Couleur::Couleur(float rouge, float vert, float bleu, float alpha) {
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
	this->alpha = alpha;
}

/**
 * Modifie la couleur des 3 valeurs
 * @param couleur Nouvelle couleur
 * @return void
 */
void Couleur::modifier(Couleur couleur) {
	this->rouge = couleur.rouge;
	this->vert = couleur.vert;
	this->bleu = couleur.bleu;
	this->alpha = couleur.alpha;
}