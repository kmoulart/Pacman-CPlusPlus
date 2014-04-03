// Map.cpp

#include "Map.h"
#include "Utils.h"

/**
 * Constructeur vide de la map
 */
Map::Map(){
	map = NULL;
	model = Model::getInstance();
	pacman = PacmanView::getInstance();
	fantomes = 0;
	nbFantomes = 0;
	rotation = false;
	darkMode = false;
	firstPerson = false;
	angle = 0;
	nbrPastilles = 0;
}

/**
 * Charge le labyrinthe à partir d'un fichier
 * @param fichierLaby Fichier à charger pour le labyrinthe
 * @return void
 */
void Map::load(ifstream &fichierLaby) {
	int posLigne, posColonne, nbFantomes, nbrLignes, nbrColonnes;
	float ligneFantomeInit, colonneFantomeInit;
	// la fonction écrit d'abord les valeurs lues dans les variables respectives
	fichierLaby >> nbrLignes >> nbrColonnes >> posLigne >> posColonne >> ligneFantomeInit >> colonneFantomeInit >> nbFantomes;
	// maintenant que les dimensions sont connues, on initialise la mémoire où sera stockée les tableaux
	
	// Si une map a déjà été chargée, on la décharge pour la nouvelle
	if (map != NULL) {
		for (int i = 0; i < this->nbrLignes + 1; i++) {
			delete[] map[i];
		}
		delete map;
	}

	// Initialise la map
	initMap(nbrLignes, nbrColonnes);

	// Initialise les éléments mobiles
	initFantomes(nbFantomes, colonneFantomeInit, ligneFantomeInit);
	initPacman(posColonne, posLigne);
	
	// Charge le content de la map
	loadMap(fichierLaby, nbrLignes, nbrColonnes);
}

/**
 * Redéfinition de l'operateur >> pour lire le fichier
 * @param fichier Fichier à charger pour le labyrinthe
 * @param map Map à initialiser
 * @return ifstream Fichier qui a été utilisé pour charger le labyrinthe
 */
ifstream &operator>>(ifstream &fichier, Map &map) {
	map.load(fichier);
	return fichier;
}

/**
 * Décrémente le nombre de pastille sur la map et augmente son score
 * @return bool Valeur booléenne sur le nombre de pastille encore sur la map
 */
bool Map::decrementNbrPastilles() {
	this->nbrPastilles--;
	model->incrementScore();
	return this->nbrPastilles <= 0;
}

/**
 * Charge la map
 * @param fichierLaby Fichier à charger pour le labyrinthe
 * @param nbrLignes Nombre de lignes du labyrinthe à charger
 * @param nbrColonnes Nombre de colonnes du labyrinthe à charger
 * @return void
 */
void Map::loadMap(ifstream &fichierLaby, int nbrLignes, int nbrColonnes) {
	//La map contient toujours 1 ligne et 1 colonne en plus que les dimensions du tableau affiché
	//donc on stocke dans le labyrinthe la taille réelle du tableau
	nbrLignes++;
	nbrColonnes++;
	nbrPastilles = 0;
	int code = 0;
	for (int i = nbrLignes - 1; i >= 0; i--) {
		for (int j = 0; j < nbrColonnes; j++) {
			fichierLaby >> code;
			if (i == 0 || j == nbrColonnes - 1)
				map[i][j] = Case(Coordonnee(i, j), Couleur(-1, -1, -1), code);
			else
				map[i][j] = Case(Coordonnee(i, j), COULEUR_SOL, code);
			map[i][j].initCase();
			if (code >= PASTILLE) nbrPastilles++;
		}
	}
}

/**
 * Initialises les fantomes
 * @param newNbFantomes Nouveau nombre de fantome sur la map
 * @param newColonneFantomeInit Nouvelle position sur l'axe des x des fantomes
 * @param newLigneFantomeInit Nouvelle position sur l'axe des y des fantomes
 * @return void
 */
void Map::initFantomes(int newNbFantomes, float newColonneFantomeInit, float newLigneFantomeInit) {
	this->nbFantomes = newNbFantomes;
	this->fantomes = new FantomeView[nbFantomes];
	for (int i = 0; i < nbFantomes; i++) {
		this->fantomes[i].init(Coordonnee(newColonneFantomeInit, newLigneFantomeInit));
	}
}

/**
 * Initialises le pacman
 * @param newColonnePacmanInit Nouvelle position sur l'axe des x du pacman
 * @param newLignePacmanInit Nouvelle position sur l'axe des y du pacman
 * @return void
 */
void Map::initPacman(int newColonnePacmanInit, int newLignePacmanInit) {
	pacman->init(Coordonnee(newColonnePacmanInit, newLignePacmanInit));
}

/**
 * Initialises la map
 * @param nbrLignes Nouvelle hauteur du labyrinthe
 * @param nbrColonnes Nouvelle largeur du labyrinthe
 * @return void
 */
void Map::initMap(int nbrLignes, int nbrColonnes) {
	this->nbrLignes = nbrLignes;
	this->nbrColonnes = nbrColonnes;
	map = new Case*[nbrLignes + 1];
	for (int i = 0; i < nbrLignes + 1; i++) {
		// cette boucle initialise chaque pointeurs de ce tableau avec des tableaux de cases
		map[i] = new Case[nbrColonnes + 1];
	}
}

/**
 * Test si le virage est possible
 * @param coord Coordonnée à tester pour voir si le virage est possible
 * @param directionVoulue Direction voulue par l'entité mobile
 * @param traverse Permet de traverser ou non les murs invisibles
 * @return bool Virage possible ou non
 */
bool Map::viragePossible(const Coordonnee &coord, int directionVoulue, bool traverse) {
	float posColonne = coord.getX();
	float posLigne = coord.getY();
	// Si aucune direction voulue, on sort
	if (directionVoulue >= 0
		// Si on est sur une colonne...
		&& ((posColonne == Utils::round(posColonne) 
			// ... et qu'on veut se déplacer en sur un axe haut bas
			&& (directionVoulue == BAS || directionVoulue == HAUT))
				// Ou si on est sur une ligne..
				|| (posLigne == Utils::round(posLigne) 
					// ... et qu'on veut se déplacer sur un un axe gauche-droite
					&& (directionVoulue == GAUCHE || directionVoulue == DROITE)))) {
			// Enfin, si on peut se déplacer dans la direction voulue
			return deplacementPossible(coord, directionVoulue, traverse);
	}
	return false;
}

/**
 * Test si le déplacement est possible
 * @param coord Coordonnée à tester pour voir si le déplacement est possible
 * @param direction Direction pour l'entité mobile
 * @param traverse Permet de traverser ou non les murs invisibles
 * @return bool Déplacement possible ou non
 */
bool Map::deplacementPossible(const Coordonnee &coord, int direction, bool traverse) {
	float posColonne = coord.getX();
	float posLigne = coord.getY();
	// Le + 1 est nécessaire car la ligne 0 du labyrinthe est la ligne du bas du fichier de labyrinthe
	// La partie que l'on peut parcourir du labyrinthe commence à l'indice 1 et jusqu'à nbrLigne - 1
	int pl = Utils::round(posLigne) + 1;
	int pc = Utils::round(posColonne);
	switch (direction) {
	case DROITE:
		// on ne peut se déplacer sur un axe gauche-droite que si on est sur une ligne a coordonnées entières
		return posLigne == Utils::round(posLigne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posColonne != Utils::round(posColonne) 
				// On ne peut pas sortir du labyrinthe
				|| (posColonne < (nbrColonnes - 1)
					// Teste si il y a un mur a droite (mur gauche dans la case de droite)
					&& ((map[pl][pc + 1].getCode() % (MUR_GAUCHE * 2)) < MUR_GAUCHE
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible a droite (mur gauche invisible dans la case de droite)
							|| (map[pl][pc + 1].getCode() % (MUR_GAUCHE_INV * 2)) < MUR_GAUCHE_INV))));
	case GAUCHE:
		// on ne peut se déplacer sur un axe gauche-droite que si on est sur une ligne a coordonnées entières
		return posLigne == Utils::round(posLigne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posColonne != Utils::round(posColonne) 
				// On ne peut pas sortir du labyrinthe
				|| (posColonne > 0 
					// Teste si il y a un mur a gauche
					&& ((map[pl][pc].getCode() % (MUR_GAUCHE * 2)) < MUR_GAUCHE 
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible a gauche
							|| (map[pl][pc].getCode() % (MUR_GAUCHE_INV * 2)) < MUR_GAUCHE_INV))));
	case BAS:
		// on ne peut se déplacer sur un axe haut-bas que si on est sur une colonne a coordonnées entières
		return posColonne == Utils::round(posColonne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posLigne != Utils::round(posLigne) 
				// On ne peut pas sortir du labyrinthe
				|| (posLigne > 0
					// Teste si il y a un mur en bas (mur haut dans la case d'en bas)
					&& ((map[pl - 1][pc].getCode() % (MUR_HAUT * 2)) < MUR_HAUT 
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible en bas (mur haut invisible dans la case d'en bas)
							|| (map[pl - 1][pc].getCode() % (MUR_HAUT_INV * 2)) < MUR_HAUT_INV))));
	case HAUT:
		// on ne peut se déplacer sur un axe haut-bas que si on est sur une colonne a coordonnées entières
		return posColonne == Utils::round(posColonne) 
			// Si on est entre deux cases on peut bouger car il n'y a pas de murs aux coordonnées non entières
			&& (posLigne != Utils::round(posLigne)
				// On ne peut pas sortir du labyrinthe
				|| (posLigne < (nbrLignes - 1) 
					// Teste si il y a un mur en haut
					&& ((map[pl][pc].getCode() % (MUR_HAUT * 2)) < MUR_HAUT
						// Si on traverse les murs invisibles
						&& (traverse
							// Teste si il y a un mur invisible en haut
							|| (map[pl][pc].getCode() % (MUR_HAUT_INV * 2)) < MUR_HAUT_INV))));
	default:
		return false;
	}
}

/**
 * Verifie le nombre de pastille sur la map ce que cela engendre
 * @return bool Vérifie si il y a encore des pastilles sur la map
 */
bool Map::verifierPastilles() {
	// Une pastille est mangée si on est dans une coordonnee entiere où se trouve une pastille
	if (!Coordonnee::estEntiere(pacman->getCoord()))
		return false;
	int pl = Utils::round(pacman->getCoord().getY() + 1);
	int pc = Utils::round(pacman->getCoord().getX());
	// Verifie qu'une pastille est contenu dans la case et l'enleve si il y en a une
	int pastilleContenue = map[pl][pc].checkPastille();
	// La pastille est une super pastille, on rend pacman invulnerable
	if (pastilleContenue >= SUPER_PASTILLE) {
		pacman->invulnerable();
		for (int i = 0; i < nbFantomes; i++)
			fantomes[i].tuable(true);
	}
	// Si la case contenait une pastille, on regarde si c'était la dernière
	if (pastilleContenue >= PASTILLE && decrementNbrPastilles()) {
		model->levelUp();
		return true;
	}
	return false;
}

/**
 * Vérifie le status du fantome passé en paramètre
 * @param i Fantome retenu dans le tableau de fantomes
 * @return bool Vérifie si il y a eu une collision entre un fantome et pacman
 */
bool Map::verifierFantome(int i) {
	// Le fantome est mort, on arrete la
	if (fantomes[i].isMort())
		return false;
	float posLigne = pacman->getCoord().getY();
	float posColonne = pacman->getCoord().getX();
	// Collision entre pacman et le fantome
	if (fantomes[i].getCoord().equals(pacman->getCoord())) {
		if (pacman->isSpecial()) {
			fantomes[i].meurt();
		} else {
			model->decrementNbrVies();
			model->resetLevel();
		}
		return true;
	}
	return false;
}

/**
 * Modifie le mode de la caméra
 * @param firstPerson Permet de rentrer en mode première personne
 * @return void
 */
void Map::setFirstPerson(bool firstPerson) {
	this->firstPerson = firstPerson;
}

/**
 * Modifie le mode du labyrinthe
 * @param activer Permet d'activer le "Dark Mode"
 * @return void
 */
void Map::setDarkMode(bool activer) {
	this->darkMode = activer;
}

/**
 * Modifie le status de la rotation du labyrinthe
 * @param rotation Permet d'activer la rotation
 * @return void
 */
void Map::setRotation(bool rotation) {
	this->rotation = rotation;
}

/**
 * Modifie l'angle de rotation du labyrinthe
 * @param angle Nouvelle valeur de l'angle de rotation
 * @return void
 */
void Map::setAngle(int angle) {
	this->angle = angle;
}
