// Entite.cpp

#include "Entite.h"

/**
 * Constructeur vide d'une entit�
 */
Entite::Entite() {
	coord = Coordonnee();
	couleur = Couleur();
}

/**
 * Constructeur d'une entit� avec une coordonn�e et une couleur
 * @param coord Coordonn�e d'une entit�
 * @param couleur Couleur d'une entit�
 */
Entite::Entite(Coordonnee coord, Couleur couleur) : coord(coord), couleur(couleur) {
}

/**
 * Modifie la coordonn�e d'une entit�e
 * @param coord Nouvelle coordonn�e d'une entit�
 * @return void
 */
void Entite::setCoord(Coordonnee coord) {
	this->coord.setCoord(coord);
}

/**
 * Modifie la couleur d'une entit�e
 * @param couleur Nouvelle couleur d'une entit�
 * @return void
 */
void Entite::setCouleur(Couleur couleur) {
	this->couleur.modifier(couleur);
}