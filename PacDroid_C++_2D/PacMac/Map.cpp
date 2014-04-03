// Map.cpp
#include "Map.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
Map *Map::instance = 0;

/*
 * Constructeur de la map
 */
Map::Map(){
	map = NULL;
	fantomes = 0;
	nbFantomes = 0;
	pacman = Pacman::getInstance();
	model = Model::getInstance();
}

/*
 * Renvoi l'unique instance de la map (Singleton)
 * @return Map *
 */
Map *Map::getInstance(){
	if (instance == 0)
		instance = new Map();
	return instance;
}

/*
 * Arrondi la valeur passée en paramètre
 * @param int i
 * @return int
 */
int round(float i) {
	if (i < ((int) i) + 0.5)
		return (int) i;
	return ceil(i);
}

/*
 * Charge la map
 * @param int nbrLignes
 * @param int nbrColonnes
 * @return void
 */
void Map::loadMaps(int nbrLignes, int nbrColonnes) {
	if (map != NULL) {
		for (int i = 0; i < this->nbrLignes; i++) {
			delete map[i];
		}
		delete map;
	}
	this->nbrLignes = nbrLignes;
	this->nbrColonnes = nbrColonnes;

	map = new int*[nbrLignes + 1];
	for (int i = 0; i < nbrLignes + 1; i++)
	{
		// cette boucle initialise chaque pointeurs de ce tableau avec des tableaux d'entiers
		map[i]=new int[nbrColonnes + 1];
	}
}

/*
 * Modifie le nombre de pastille sur la map
 * @param int newNbrPastilles
 * @return void
 */
void Map::setNbrPastilles(int newNbrPastilles) {
	this->nbrPastilles = newNbrPastilles;
}

/*
 * Modifie le nombre de fantome sur la maps
 * @param int newNbFantomes
 * @return void
 */
void Map::setNbFantomes(int newNbFantomes) {
	if (this->fantomes != 0) {
		delete[] fantomes;
	}
	this->nbFantomes = newNbFantomes;
	this->fantomes = new Fantome[nbFantomes];
}

/*
 * Modifie la position initiale des fantômes sur l'axe des y
 * @param int newLigneFantomeInit
 * @return void
 */
void Map::setLigneFantomeInit(int newLigneFantomeInit) {
	this->ligneFantomeInit = newLigneFantomeInit;
}

/*
 * Modifie la position initiale des fantômes sur l'axe des x
 * @param int newColonneFantomeInit
 * @return void
 */
void Map::setColonneFantomeInit(int newColonneFantomeInit) {
	this->colonneFantomeInit = newColonneFantomeInit;
}

/*
 * Décrémente le nombre de pastille sur la map et augmente son score
 * @return bool
 */
bool Map::decrementNbrPastilles() {
	this->nbrPastilles--;
	model->incrementScore();
	return this->nbrPastilles <= 0;
}

/*
 * Test si le virage est possible (mouvement fluide)
 * @param float posLigne
 * @param float posColonne
 * @param int directionVoulue
 * @param bool traverse
 * @return bool
 */
bool Map::viragePossible(float posLigne, float posColonne, int directionVoulue, bool traverse) {
	// Si aucune direction voulue, on sort
	if (directionVoulue >= 0
		// Si on est sur une colonne...
		&& ((posColonne == round(posColonne) 
			// ... et qu'on veut se déplacer en sur un axe haut bas
			&& (directionVoulue == BAS || directionVoulue == HAUT))
				// Ou si on est sur une ligne..
				|| (posLigne == round(posLigne) 
					// ... et qu'on veut se déplacer sur un un axe gauche-droite
					&& (directionVoulue == GAUCHE || directionVoulue == DROITE)))) {
			// Enfin, si on peut se déplacer dans la direction voulue
			return deplacementPossible(posLigne, posColonne, directionVoulue, traverse);
	}
	return false;
}

/*
 * Test si le déplacement est possible
 * @param float posLigne
 * @param float posColonne
 * @param int directionVoulue
 * @param bool traverse
 * @return bool
 */
bool Map::deplacementPossible(float posLigne, float posColonne, int direction, bool traverse) {	
	int pl = round(posLigne);
	int pc = round(posColonne);
	switch (direction) {
	case DROITE:
		// on ne peut se déplacer sur un axe gauche-droite que si on est sur une ligne a coordonnées entières
		return posLigne == round(posLigne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posColonne != round(posColonne) 
				// On ne peut pas sortir du labyrinthe
				|| (posColonne < (nbrColonnes - 1)
					// Teste si il y a un mur a droite (mur gauche dans la case de droite)
					&& ((map[pl][pc + 1] % (MUR_GAUCHE * 2)) < MUR_GAUCHE
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible a droite (mur gauche invisible dans la case de droite)
							|| (map[pl][pc + 1] % (MUR_GAUCHE_INV * 2)) < MUR_GAUCHE_INV))));
	case GAUCHE:
		// on ne peut se déplacer sur un axe gauche-droite que si on est sur une ligne a coordonnées entières
		return posLigne == round(posLigne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posColonne != round(posColonne) 
				// On ne peut pas sortir du labyrinthe
				|| (posColonne > 0 
					// Teste si il y a un mur a gauche
					&& ((map[pl][pc] % (MUR_GAUCHE * 2)) < MUR_GAUCHE 
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible a gauche
							|| (map[pl][pc] % (MUR_GAUCHE_INV * 2)) < MUR_GAUCHE_INV))));
	case BAS:
		// on ne peut se déplacer sur un axe haut-bas que si on est sur une colonne a coordonnées entières
		return posColonne == round(posColonne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posLigne != round(posLigne) 
				// On ne peut pas sortir du labyrinthe
				|| (posLigne < (nbrLignes - 1) 
					// Teste si il y a un mur a en bas (mur haut dans la case d'en bas)
					&& ((map[pl + 1][pc] % (MUR_HAUT * 2)) < MUR_HAUT 
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible en bas (mur haut invisible dans la case d'en bas)
							|| (map[pl + 1][pc] % (MUR_HAUT_INV * 2)) < MUR_HAUT_INV))));
	case HAUT:
		// on ne peut se déplacer sur un axe haut-bas que si on est sur une colonne a coordonnées entières
		return posColonne == round(posColonne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posLigne != round(posLigne)
				// On ne peut pas sortir du labyrinthe
				|| (posLigne > 0 
					// Teste si il y a un mur a en haut
					&& ((map[pl][pc] % (MUR_HAUT * 2)) < MUR_HAUT
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible en haut
							|| (map[pl][pc] % (MUR_HAUT_INV * 2)) < MUR_HAUT_INV))));
	default:
		return false;
	}
}

/*
 * Verifie le nombre de pastille sur la map et les différents 
 * effets que cela engendre
 * @return bool
 */
bool Map::verifierPastilles() {
	float posLigne = pacman->getPosY(), posColonne = pacman->getPosX();
	if (posLigne != round(posLigne) 
		|| posColonne != round(posColonne)) {
		return false;
	}
	int pl = round(posLigne);
	int pc = round(posColonne);
	if (map[pl][pc] >= SUPER_PASTILLE) {
		pacman->invulnerable();
	}
	if (map[pl][pc] >= PASTILLE 
		&& decrementNbrPastilles()) {
		model->levelUp();
		return true;
	}
	map[pl][pc] %= PASTILLE;
	return false;
}

/*
 * Vérifie le status des fantomes présents sur la map
 * @return bool
 */
bool Map::verifierFantomes() {
	float posLigne = pacman->getPosY(), posColonne = pacman->getPosX();
	for (int i = 0; i < nbFantomes; i++) {
		if (fantomes[i].isMort())
			return false;
		// on arrondi ici a 2 décimales pour palier a un souci d'imprécision machine
		// menant a une collision non détectée dans de rares cas
		if ((floor((nbrLignes - 1 - fantomes[i].getPosY() + 0.005) * 100) / 100.0) == (floor((posLigne + 0.005) * 100) / 100.0) 
			&& fantomes[i].getPosX() == posColonne) {
			if (pacman->isSuper()) {
				fantomes[i].meurt();
			} else {
				model->decrementNbrVies();
				model->resetLevel();
			}
			return true;
		}
	}
	return false;
}