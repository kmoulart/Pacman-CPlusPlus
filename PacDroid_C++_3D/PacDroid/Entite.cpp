// Entite.cpp

#include "Entite.h"

/**
 * Constructeur vide d'une entité
 */
Entite::Entite() {
	coord = Coordonnee();
	couleur = Couleur();
}

/**
 * Constructeur d'une entité avec une coordonnée et une couleur
 * @param coord Coordonnée d'une entité
 * @param couleur Couleur d'une entité
 */
Entite::Entite(Coordonnee coord, Couleur couleur) : coord(coord), couleur(couleur) {
}

/**
 * Modifie la coordonnée d'une entitée
 * @param coord Nouvelle coordonnée d'une entité
 * @return void
 */
void Entite::setCoord(Coordonnee coord) {
	this->coord.setCoord(coord);
}

/**
 * Modifie la couleur d'une entitée
 * @param couleur Nouvelle couleur d'une entité
 * @return void
 */
void Entite::setCouleur(Couleur couleur) {
	this->couleur.modifier(couleur);
}