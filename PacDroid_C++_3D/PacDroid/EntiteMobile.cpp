// EntiteMobile.cpp

#include "EntiteMobile.h"
#include "Constantes.h"

/**
 * Constructeur vide d'une entité mobile
 */
EntiteMobile::EntiteMobile() : Entite() {
	this->couleur = Couleur();
	this->cNormal = this->couleur;
	this->cSpecial = Couleur();
	this->reset();
}

/**
 * Determine et exécute le deplacement à faire selon la direction
 * @return void
 */
void EntiteMobile::deplacer() {
	switch(this->direction) {
		case BAS:
			coord.setY(coord.getY() - VITESSE);
			break;
		case HAUT:
			coord.setY(coord.getY() + VITESSE);
			break;
		case DROITE:
			coord.setX(coord.getX() + VITESSE);
			break;
		case GAUCHE:
			coord.setX(coord.getX() - VITESSE);
		default:
			break;
	}
}

/**
 * Réinitialise l'entité mobile
 * @return void
 */
void EntiteMobile::reset() {
	this->coord.setCoord(this->coordInitiales);
	this->direction = DIRECTION_INIT;
	this->setSpecial(false);
	this->mort = false;
}

/**
 * Modifie l'effet spécial sur l'entitée mobile
 * @param special Permet d'activer ou non le mode spécial de l'entité mobile
 * @return void
 */
void EntiteMobile::setSpecial(bool special) {
	if (special)
		this->couleur.modifier(this->cSpecial);
	else
		this->couleur.modifier(this->cNormal);
	this->special = special;
}

/**
 * Modifie la mort sur l'entitée mobile
 * @param mort Permet de mourir
 * @return void
 */
void EntiteMobile::setMort(bool mort) {
	this->mort = mort;
}