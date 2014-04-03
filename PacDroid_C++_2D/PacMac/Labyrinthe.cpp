// Labyrinthe.cpp
#include "Labyrinthe.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
Labyrinthe *Labyrinthe::instance = 0;

/*
 * Constructeur du Labyrinthe
 */
Labyrinthe::Labyrinthe() {
	map = Map::getInstance();
}

/*
 * Renvoi l'unique instance du Labyrinthe (Singleton)
 * @return Labyrinthe *
 */
Labyrinthe *Labyrinthe::getInstance()
{
	if (Labyrinthe::instance == 0)
		instance = new Labyrinthe();

	return instance;
}

/*
 * Dessine le mur haut du labyrinthe
 * @param float rouge
 * @param float vert
 * @param float bleu
 * @return void
 */
void Labyrinthe::dessineHaut(float red, float green, float blue) {
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		glVertex2f(-1/2.0, 1/2.0);
		glVertex2f(1/2.0, 1/2.0);
	glEnd();
}

/*
 * Dessine le mur gauche du labyrinthe
 * @param float rouge
 * @param float vert
 * @param float bleu
 * @return void
 */
void Labyrinthe::dessineGauche(float red, float green, float blue) {
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		glVertex2f(-1/2.0, 1/2.0);
		glVertex2f(-1/2.0, -1/2.0);
	glEnd();
}

/*
 * Dessine une pastille normale
 * @return void
 */
void Labyrinthe::dessineUnite() {
	glPushMatrix();
	glTranslated(0, 0, 0);
	glColor3f(1, 1, 1);
	GLUquadricObj *pastille;
	pastille = gluNewQuadric(); 
	gluQuadricDrawStyle(pastille, GLU_FILL);
	gluDisk(pastille, 0, 1.0/30, 36, 1);
	gluDeleteQuadric(pastille);
	glPopMatrix();
}

/*
 * Dessine une pastille spécial
 * @return void
 */
void Labyrinthe::dessineUniteSpecial() {
	glPushMatrix();
	glTranslated(0, 0, 0);
	glColor3f(0, 0, 1);
	GLUquadricObj *pastille;
	pastille = gluNewQuadric();
	gluQuadricDrawStyle(pastille, GLU_FILL);
	gluDisk(pastille, 0, 1.0/10, 36, 1);
	gluDeleteQuadric(pastille);
	glPopMatrix();
}

/*
 * Dessine le bon dessin
 * @param int type
 * @return void
 */
void Labyrinthe::dessine(int type) {
	if (type >= SUPER_PASTILLE) dessineUniteSpecial();
	type %= SUPER_PASTILLE;
	if (type >= PASTILLE) dessineUnite();
	type %= PASTILLE;
	
	if (type >= MUR_GAUCHE_INV) dessineGauche(0.2, 0.2, 0.4);
	type %= MUR_GAUCHE_INV;
	if (type >= MUR_HAUT_INV) dessineHaut(0.2, 0.2, 0.4);
	type %= MUR_HAUT_INV;

	if (type >= MUR_GAUCHE) dessineGauche(0, 0, 1);
	type %= MUR_GAUCHE;
	if (type >= MUR_HAUT) dessineHaut(0, 0, 1);
}

/*
 * Dessine le labyrinthe
 * @return void
 */
void Labyrinthe::dessine() {
	int **mapLab = map->getMap();
	for (int x = 0; x < map->getNbrLignes() + 1; x++) {
		for (int y = 0; y < map->getNbrColonnes() + 1; y++) {
			glPushMatrix();
			glTranslated(y, -x, 0);
			dessine(mapLab[x][y]);
			glPopMatrix();
		}
	}
	
}

/*
 * Redéfinition de l'operateur >> pour lire le fichier
 * @param ifstream &fichier
 * @param Labyrinthe &laby
 * @return void
 */
ifstream &operator>>(ifstream &fichier, Labyrinthe &laby) {
	laby.load(fichier);
	return fichier;
}

/*
 * Charge le labyrinthe a partir d'un fichier
 * @param ifstream &fichier
 * @return void
 */
void Labyrinthe::load(ifstream &fichierLaby) {
	int posLigne, posColonne, nbFantomes;
	float ligneFantomeInit, colonneFantomeInit;
	// la fonction écrit d'abord les valeurs lues dans les variables respectives
	fichierLaby >> nbrLignes >> nbrColonnes >> posLigne >> posColonne >> ligneFantomeInit >> colonneFantomeInit >> nbFantomes;
	// maintenant que les dimensions sont connues, on initialise la mémoire où sera stockée les tableaux
	map->loadMaps(nbrLignes, nbrColonnes);

	map->setLigneFantomeInit(ligneFantomeInit);
	map->setColonneFantomeInit(colonneFantomeInit);
	map->setNbFantomes(nbFantomes);
	Pacman::getInstance()->setPosY(posLigne);
	Pacman::getInstance()->setPosX(posColonne);
	
	//La map contient toujours 1 ligne et 1 colonne en plus que les dimensions du tableau affiché
	//donc on stocke dans le labyrinthe la taille réelle du tableau
	nbrLignes++;
	nbrColonnes++;
	int **mapLab = map->getMap();
	int nbrPastilles = 0;
	for (int i = 0; i < nbrLignes; i++)
	{
		for (int j = 0; j < nbrColonnes; j++)
		{
			fichierLaby >> mapLab[i][j];
			if (mapLab[i][j] >= PASTILLE) nbrPastilles++;
		}
	}
	map->setNbrPastilles(nbrPastilles);
}