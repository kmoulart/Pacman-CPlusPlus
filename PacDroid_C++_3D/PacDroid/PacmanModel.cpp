// PacmanModel.cpp

#include "PacmanModel.h"
#include "MapView.h"
#include "Constantes.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
PacmanModel *PacmanModel::instance = 0;

/**
 * Constructeur vide du PacmanModel
 */
PacmanModel::PacmanModel() : EntiteMobile() {
	this->reset();
}

/**
 * Renvoi l'unique instance du pacman (Application du pattern singleton)
 * @return PacmanModel Pointeur vers l'instance unique de la classe
 */
PacmanModel *PacmanModel::getInstance() {
	if (PacmanModel::instance == 0 )
		instance = new PacmanModel();
	return instance;
}

/**
 * Met a jour si possible la direction de pacman et le fait avancer
 * @return void
 */
void PacmanModel::updatePosition() {
	Map *map = MapView::getInstance();
	if (map->viragePossible(coord, directionVoulue, false)) {
		direction = directionVoulue;
		directionVoulue = -1;
		deplacer();
	} else if (map->deplacementPossible(coord, direction, false)) {
		deplacer();
	}
}

/**
 * Incrémente/décrémente l'angle de la bouche de pacman
 * @return void
 */
void PacmanModel::anime() {
	static int sens = -1;
	angleBoucheCourant = angleBoucheCourant + 5 * sens;
	if (angleBoucheCourant >= ANGLE_BOUCHE || angleBoucheCourant <= 2) {
		sens *= -1;
	}
}

/**
 * Rend pacman invulnérable
 * @return void
 */
void PacmanModel::invulnerable() {
	this->setSpecial(true);
	this->tempsRestantSuper = DUREE_SUPER_PAC;
}

/**
 * Annule l'invulnérabilité du pacman
 * @return void
 */
void PacmanModel::disableSuperPac() {
	this->setSpecial(false);
	this->tempsRestantSuper = 0;
}

/**
 * Décrémente le temps du mode super Pacman
 * @return void
 */
void PacmanModel::decrementSuperPac() {
	if (this->tempsRestantSuper > 0) 
		this->tempsRestantSuper -= VITESSE_PERTE_SUPER_PAC;
	else
		disableSuperPac();
}

/**
 * Initialise le pacman
 * @param c Coordonnée initiale du pacman
 * @return void
 */
void PacmanModel::init(const Coordonnee &c) {
	this->couleur = Couleur(0, 0, 0);
	this->cNormal = this->couleur;
	this->cSpecial = Couleur(1, 0, 0);
	this->coord = c;
	this->coordInitiales = c;
}

/**
 * Réinitialise pacman
 * @return void
 */
void PacmanModel::reset() {
	EntiteMobile::reset();
	this->angleBoucheCourant = ANGLE_BOUCHE / 2;
	this->directionVoulue = -1;
	this->tempsRestantSuper = 0;
}

/**
 * Modifie la direction voulue par l'utilisateur pour pacman
 * @param directionVoulue Nouvelle direction voulue du pacman
 * @return void
 */
void PacmanModel::setDirectionVoulue(int directionVoulue) {
	this->directionVoulue = directionVoulue;
}