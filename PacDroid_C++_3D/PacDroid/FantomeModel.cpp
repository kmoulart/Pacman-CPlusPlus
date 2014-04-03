// FantomeModel.cpp

#include "FantomeModel.h"
#include "MapView.h"
#include "PacmanView.h"
#include "Aleatoire.h"

/**
 * Constructeur vide de FantomeModel utilis� pour les tableaux
 */
FantomeModel::FantomeModel() : EntiteMobile() {
	this->difficulte = 20;
}

/**
 * Met � jours la position du fant�me
 * @return void
 */
void FantomeModel::updatePosition() {
	if (this->mort) return;
	// Un fantome ne doit voir que s'il peut changer de direction qu'a une coordonn�e enti�re
	if (Coordonnee::estEntiere(coord)) {
		this->direction = findOptimalDirection();
	}
	this->deplacer();
}

/**
 * Calcule les directions possibles que peut emprunter les fantomes
 * @return int* Tableau des directions possibles que peut emprunter les fantomes
 */
int* FantomeModel::computeDirectionsPossibles() {
	static const int directions[4] = { DROITE, GAUCHE, HAUT, BAS };
	static int directionsPossibles[5];
	directionsPossibles[0] = 0; // indique l'�tat de remplissement du tableau (taille logique)
	int nbDirImpossibles = 0; // indique le nombre de direction impossible
	while (directionsPossibles[0] + nbDirImpossibles < 4) {
		// on refuse le demi-tour sauf si pas d'autres options
		if (directions[directionsPossibles[0] + nbDirImpossibles] == (this->direction + 180) % 360) {
			nbDirImpossibles++;
		}
		// sinon, si le d�placement n'est pas possible dans la direction
		else if (!MapView::getInstance()->deplacementPossible(coord, directions[directionsPossibles[0] + nbDirImpossibles], true)) {
			nbDirImpossibles++;
		}
		// sinon, le d�placement est possible dans la direction actuelle
		else {
			directionsPossibles[directionsPossibles[0] + 1] = directions[directionsPossibles[0] + nbDirImpossibles];
			directionsPossibles[0]++;
		}
	}
	return directionsPossibles;
}

/**
 * Recherche la direction optimale que doit emprunter le fantome en fonction de la position du pacman
 * et de son niveau de difficult�
 * @return int La direction optimale de toutes les directions possibles
 */
int FantomeModel::findOptimalDirection() {
	int* directionsPossibles = computeDirectionsPossibles();
	// Aucune direction possible, on effectue alors un demi-tour
	if (directionsPossibles[0] == 0)
		return (this->direction + 180) % 360;
	// Temp�re la difficult� du fantome
	if (Aleatoire::hasardi(0, 99) < this->difficulte)
		return directionsPossibles[Aleatoire::hasardi(1, directionsPossibles[0] - 1)];
	int direction = directionsPossibles[1];
	float distanceActuelle = Coordonnee::computeDistance(this->change(direction, VITESSE), PacmanView::getInstance()->getCoord());
	float distanceMin = distanceActuelle;
	float distanceMax = distanceActuelle;
	// Parcours toutes les directions possibles pour trouver la meilleure
	for (int i = 1; i <= directionsPossibles[0]; i++) {
		float distance = Coordonnee::computeDistance(this->change(directionsPossibles[i], VITESSE), PacmanView::getInstance()->getCoord());
		// Si l'on n'est pas en mode sp�cial, on cherche � s'approcher du pacman
		if (!this->special && distance < distanceMin) {
			distanceMin = distance;
			direction = directionsPossibles[i];
		}
		// Si l'on est en mode sp�cial, on cherche � s'�loigner du pacman
		if (this->special && distance > distanceMax) {
			distanceMax = distance;
			direction = directionsPossibles[i];
		}
	}
	return direction;
}

/**
 * Simule le d�placement du fantome d'une certaine valeur dans la direction demand�e
 * @param direction Direction pour calculer la nouvelle coordonn�e
 * @param value Valeur du d�placement dans la direction demand�e
 * @return Coordonnee La coordonn�e chang�e en fonction de la direction et de la valeur donn�e
 */
Coordonnee FantomeModel::change(int direction, float value) {
	return Coordonnee(
		this->coord.getX() + value * ((direction == GAUCHE) ? -1 : (direction == DROITE) ? 1 : 0),
		this->coord.getY() + value * ((direction == BAS) ? -1 : (direction == HAUT) ? 1 : 0));
}

/**
 * Initialise le fantome
 * @param c Coordonn�e initiale du fantome
 * @return void
 */
void FantomeModel::init(const Coordonnee &c) {
	this->setDifficulte(Aleatoire::hasardi(20, 100));
	this->couleur = Aleatoire::couleur();
	this->cNormal = this->couleur;
	this->cSpecial = Couleur(0, 0, 1);
	this->coord = c;
	this->coordInitiales = c;
}

/**
 * Modifie la difficulte du fantome
 * @param difficulte Nouvelle difficult� du fantome
 * @return void
 */
void FantomeModel::setDifficulte(int difficulte) {
	this->difficulte = difficulte;
}

/**
 * Rend le fantome tuable
 * @param special Permet d'activer ou non le mode sp�cial du fantome
 * @return void
 */
void FantomeModel::tuable(bool special) {
	this->setSpecial(special);
}

/**
 * Indique que le fantome meurt
 * @return void
 */
void FantomeModel::meurt() {
	this->mort = true;
}