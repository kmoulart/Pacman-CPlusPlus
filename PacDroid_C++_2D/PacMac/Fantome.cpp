// Fantome.cpp

#include "Fantome.h"

/*
 * Constructeur vide de Fantome utilisé pour les tableaux
 */
Fantome::Fantome() {
	map = Map::getInstance();
	this->direction = DROITE;
	this->posX = map->getColonneFantomeInit();
	this->posY = map->getLigneFantomeInit();
	this->rouge = 1;
	this->vert = 1;
	this->bleu = 1;
	this->victime = false;
	this->mort = false;
}

/*
 * Constructeur avec la position en x et y du fantome
 * @param float posX
 * @param float posY
 */
Fantome::Fantome(float posX, float posY) {
	map = Map::getInstance();
	this->direction = DROITE;
	this->posX = posX;
	this->posY = posY;
	this->rouge = 1;
	this->vert = 1;
	this->bleu = 1;
	this->victime = false;
	this->mort = false;
}

/*
 * Constructeur avec la position en x et y du fantome et ses
 * couleurs
 * @param float posX
 * @param float posY
 * @param int rouge
 * @param int vert
 * @param int bleu
 */
Fantome::Fantome(float posX, float posY, int rouge, int vert, int bleu) {
	map = Map::getInstance();
	this->direction = DROITE;
	this->posX = posX;
	this->posY = posY;
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
	this->victime = false;
	this->mort = false;
}

/*
 * Dessine le fantome sur l'espace de dessin
 * @return void
 */
void Fantome::dessine() {
	if (this->mort) return;//reset apres un timer
	glPushMatrix();
		glTranslated(this->posX, this->posY, 0);
		glPushMatrix();
			// Rectangle du fantome
			glColor3f(this->rouge, this->vert, this->bleu);
			glRectd(-1/4.0, 1/8.0, 1/4.0, -1/4.0);
			glPushMatrix();
				// Tete du fantome
				glTranslated(0, 1/8.0, 0);
				GLUquadricObj *tete = gluNewQuadric(); 
				gluQuadricDrawStyle(tete, GLU_FILL);
				gluDisk(tete, 0, 1.0 / 4.0, 36, 1);
				gluDeleteQuadric(tete);
			glPopMatrix();
			glPushMatrix();
				// oeil droit
				glColor3f(0, 0, 0);
				GLUquadricObj *oeil = gluNewQuadric(); 
				gluQuadricDrawStyle(oeil, GLU_FILL);
				glTranslated(1/8.0, 1/6.0, 0);
				gluDisk(oeil, 0, 1.0 / 15.0, 36, 1);
			glPopMatrix();
			glPushMatrix();
				//oeil gauche
				glColor3f(0, 0, 0);
				glTranslated(-1/8.0, 1/6.0, 0);
				gluDisk(oeil, 0, 1.0 / 12.0, 36, 1);
				//Les yeux sont volontairement de taille différente pour un effet de style O_o
				gluDeleteQuadric(oeil);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

/*
 * Fonction C qui renvoie un nombre entier au hasard entre min et max
 * @return int
 */
int hasard(int min, int max)
{
	// rand() renvoie une valeur entre 0 et RAND_MAX, qui est une constante fixee par le systeme.
    // Donc, le quotient rand() / RAND_MAX est compris entre 0 et 1. Le (float) sert a ce que ce quotient ne soit pas arrondi.
    // On multiplie ensuite cette valeur aleatoire par la taille de l'intervalle souhaite et on ajoute la valeur de la borne inferieure.
    // On transforme ensuite la valeur obtenue en un entier via le (int).
    return (int) (min + ((float) rand() / RAND_MAX * (max - min + 1)));
}

/*
 * Déplace le fantome de manière aléatoire dans le labyrinthe
 * @return void
 */
void Fantome::updatePosition() {
	static const int directions[4] = {DROITE, GAUCHE, HAUT, BAS};
	static int directionsPossibles[3];
	int nbDirectionsPossibles = 0;
	int i = 0;
	while (nbDirectionsPossibles + i < 4) {
		// on refuse le demi-tour sauf si pas d'autres options
		if (directions[nbDirectionsPossibles + i] == (this->direction + 180) % 360) {
			i++;
		}
		// si le déplacement n'est pas possible dans la direction
		else if (!map->deplacementPossible(map->getNbrLignes() - 1 - posY, posX, directions[nbDirectionsPossibles + i], true)) {
			i++;
		}
		else {
			directionsPossibles[nbDirectionsPossibles] = directions[nbDirectionsPossibles + i];
			nbDirectionsPossibles++;
		}
	}
	if (nbDirectionsPossibles == 0) {
		// on est au bout d'un cul de sac, on fait demi-tour
		this->direction = (this->direction + 180) % 360;
	}
	else {
		// on est devant un choix, on choisit parmi les directions possibles
		this->direction = directionsPossibles[hasard(0, nbDirectionsPossibles - 1)];
	}
	this->deplacer();
}

/*
 * Determine le deplacement à faire selon la direction
 * @return void
 */
void Fantome::deplacer() {
	switch(this->direction) {
		case BAS:
			this->deplacer(posX, posY - VITESSE);
			break;
		case HAUT:
			this->deplacer(posX, posY + VITESSE);
			break;
		case DROITE:
			this->deplacer(posX + VITESSE, posY);
			break;
		case GAUCHE:
			this->deplacer(posX - VITESSE, posY);
		default:
			break;
	}
}


/*
 * Place le fantome sur l'espace de dessin
 * @param float x
 * @param float y
 * @return void
 */
void Fantome::deplacer(float posX, float posY) {
	this->posX = (floor((posX + 0.005) * 100)) / 100.0;
	this->posY = (floor((posY + 0.005) * 100)) / 100.0;
}

/*
 * Rend le fantôme tuable
 * @param int rouge
 * @param int vert
 * @param int bleu
 * @param bool victime
 * @return void
 */
void Fantome::tuable(int rouge, int vert, int bleu, bool victime) {
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
	this->victime = victime;
}

/*
 * Indique que le fantome meurt
 * @return void
 */
void Fantome::meurt() {
	this->mort = true;
}

/*
 * Réinitialise le fantôme
 * @return void
 */
void Fantome::reset() {
	this->posX = map->getColonneFantomeInit();
	this->posY = map->getLigneFantomeInit();
	this->rouge = 1;
	this->vert = 1;
	this->bleu = 1;
	this->victime = false;
	this->mort = false;
}