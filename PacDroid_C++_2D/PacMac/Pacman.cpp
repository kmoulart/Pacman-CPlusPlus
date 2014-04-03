// Pacman.cpp

#include "Pacman.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
Pacman *Pacman::instance = 0;

/*
 * Constructeur du Pacman
 */
Pacman::Pacman() {
	this->posX = 0;
	this->posY = 0;
	this->angleBoucheCourant = ANGLE_BOUCHE / 2;
	this->direction = DIRECTION_INIT;
	this->directionVoulue = -1;
	this->rouge = 0;
	this->vert = 0;
	this->bleu = 0;
	this->super = false;
	this->gameOver = false;
}

/*
 * Renvoi l'unique instance du pacman (Singleton)
 * @return Pacman *
 */
Pacman *Pacman::getInstance() {
	if (Pacman::instance == 0 )
		instance = new Pacman();
	return instance;
}

/*
 * Fait avancerpacman dans la bonne direction
 * @return void
 */
void Pacman::deplacer() {
	switch(getDirection()) {
		case BAS:
			setPosY(posY + VITESSE);
			break;
		case HAUT:
			setPosY(posY - VITESSE);
			break;
		case DROITE:
			setPosX(posX + VITESSE);
			break;
		case GAUCHE:
			setPosX(posX - VITESSE);
		default:
			break;
	}
}

/*
 * Met a jour si possible la direction de pacman et le fait avancer
 * @return void
 */
void Pacman::updatePosition() {
	Map *map = Map::getInstance();
	if (map->viragePossible(posY, posX, getDirectionVoulue(), false)) {
		setDirection(getDirectionVoulue());
		setDirectionVoulue(-1);
		deplacer();
	} else if (map->deplacementPossible(posY, posX, getDirection(), false)) {
		deplacer();
	}
}

/*
 * Dessine pacman sur l'espace de dessin
 * @return void
 */
void Pacman::dessine() {
	glPushMatrix();
	glTranslated(this->posX, Map::getInstance()->getNbrLignes() - 1 - this->posY, 0);
		glPushMatrix();
			glRotatef(this->direction, 0.0, 0.0, 1.0);
			glColor3f(1, 1, 0); // Définit la couleur de la bouche et des bords
			GLUquadricObj *pacMan;
			pacMan = gluNewQuadric();
			gluQuadricDrawStyle(pacMan, GLU_FILL);
			gluPartialDisk(pacMan, 0.0, 1.0/3, 36, 1, (this->angleBoucheCourant - 10) / 2, 360 - (this->angleBoucheCourant - 10)); 
		glPopMatrix();
		glPushMatrix();
			glRotatef(this->direction, 0.0, 0.0, 1.0);
			if (this->super)
				glColor3f(1, 0, 0); // Définit la couleur du centre de Pacman
			else
				glColor3f(0, 0, 0);
			gluQuadricDrawStyle(pacMan, GLU_FILL);
			gluPartialDisk(pacMan, 0.0, 1.0/3.2, 36, 1, this->angleBoucheCourant / 2, 360 - this->angleBoucheCourant);
			gluDeleteQuadric(pacMan);
		glPopMatrix();
		if (this->gameOver) {
			glPushMatrix();
				dessineGameOver(0.1, 1);
			glPopMatrix();
		}
	glPopMatrix();
}

/*
 * Dessine pacman sur l'espace de dessin au game over
 * @param float thickness
 * @param float radius
 * @return void
 */
void Pacman::dessineGameOver(float thickness, float radius) {
	glPushMatrix();
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-radius, radius - thickness / 2.0);
		glVertex2f(-radius, radius + thickness / 2.0);
		glVertex2f(radius, -radius + thickness / 2.0);
		glVertex2f(radius, -radius - thickness / 2.0);
		glVertex2f(-radius, -radius - thickness / 2.0);
		glVertex2f(-radius, -radius + thickness / 2.0);
		glVertex2f(radius, radius + thickness / 2.0);
		glVertex2f(radius, radius - thickness / 2.0);
		glEnd();
	glPopMatrix();
}

/*
 * Modifie la position en X du pacman sur l'espace de dessin
 * @param newPosX
 * @return void
 */
void Pacman::setPosX(float newPosX) {
	this->posX = (floor((newPosX + 0.005) * 100) / 100.0);
}

/*
 * Modifie la position en Y du pacman sur l'espace de dessin
 * @param newPosY
 * @return void
 */
void Pacman::setPosY(float newPosY) {
	this->posY = (floor((newPosY + 0.005) * 100) / 100.0);
}

/*
 * In(dé)crémente l'angle de la bouche de pacman
 * @return void
 */
void Pacman::anime() {
	static int sens = -1;
	angleBoucheCourant = angleBoucheCourant + 5 * sens;
	if (angleBoucheCourant >= ANGLE_BOUCHE || angleBoucheCourant <= 2) {
		sens *= -1;
	}
}

/*
 * Rend pacman invulnérable
 * @return void
 */
void Pacman::invulnerable() {
	this->rouge = 1;
	this->vert = 0;
	this->bleu = 0;
	this->nbCaseRestanteSuper = DUREE_SUPER_PAC;
	this->super = true;
}

/*
 * Annule l'invulnérabilité du pacman
 * @return void
 */
void Pacman::disableSuperPac() {
	this->rouge = 0;
	this->vert = 0;
	this->bleu = 0;
	this->nbCaseRestanteSuper = 0;
	this->super = false;
}

/*
 * Décrémente le temps du mode super PacMan
 * @return void
 */
void Pacman::decrementSuperPac() {
	if (this->nbCaseRestanteSuper > 0) 
		this->nbCaseRestanteSuper -= 0.04;
	else
		disableSuperPac();
}

/*
 * Réinitialise pacman
 * @return void
 */
void Pacman::reset() {
	this->angleBoucheCourant = ANGLE_BOUCHE / 2;
	this->direction = DIRECTION_INIT;
	this->directionVoulue = -1;
	this->rouge = 0;
	this->vert = 0;
	this->bleu = 0;
	this->nbCaseRestanteSuper = 0;
	this->super = false;
	this->gameOver = false;
}

/* 
 * Modifie la direction de pacman
 * @param int direction
 * @return void
 */
void Pacman::setDirection(int direction) {
	this->direction = direction;
}

/* 
 * Modifie la direction voulue par l'utilisateur pour pacman
 * @param int direction
 * @return void
 */
void Pacman::setDirectionVoulue(int directionVoulue) {
	this->directionVoulue = directionVoulue;
}

/* 
 * Modifie le status de game over
 * @param int direction
 * @return void
 */
void Pacman::setGameOver(bool gameOver) {
	this->gameOver = gameOver;
}