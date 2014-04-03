// Case.cpp

#include "Case.h"
#include "DisplayListPool.h"
#include "PastilleView.h"
#include "MurHautView.h"
#include "MurGaucheView.h"
#include "Surface.h"
#include "MyGlut.h"
using namespace glut;

/**
 * Constructeur vide d'une case
 */
Case::Case() {
	this->coord = Coordonnee();
	this->hasPastille = 0;
	this->nbrEntitees = 0;
	this->code = 0;
}

/**
 * Constructeur d'une case
 * @param coord Coordonnée de la case
 * @param couleurSol Couleur du sol de la case
 * @param code Code de la case servant a déterminer son contenu
 */
Case::Case(Coordonnee coord, Couleur couleurSol, int code) {
	this->coord = Coordonnee(coord);
	this->couleurSol = Couleur(couleurSol);
	this->hasPastille = 0;
	this->nbrEntitees = 0;
	this->code = code;
}

/**
 * Destructeur
 */
Case::~Case() {
	// S'il y a eu une pastille mais qu'elle a été mangée
	if (hasPastille < 0)
		nbrEntitees++;
	for (int i = 0; i < nbrEntitees; i++) {
		delete this->contenu[i];
	}
}

/**
 * Dessine le sol de la map
 * @return void
 */
void Case::dessineSol() {
	glPushMatrix();
		glCallList(DisplayListPool::getInstance()->getList(SURFACE_SOL_LIST));
	glPopMatrix();
}

/**
 * Dessine le contenu de la map en 2D
 * @return void
 */
void Case::dessine2D() {
	// Test obligé pour le brouillard : pour pas qu'il y ait de sol visible avec le brouillard
	if (couleurSol.getRouge() > 0) {
		glPushMatrix();
			glColor3f(couleurSol.getRouge(), couleurSol.getVert(), couleurSol.getBleu());
			dessineSol();
		glPopMatrix();
	}
	for (int i = 0; i < nbrEntitees; i++) {
		this->contenu[i]->dessine2D();
	}
}

/**
 * Dessine le contenu de la map en 3D
 * @return void
 */
void Case::dessine3D() {
	// Test obligé pour le brouillard : pour pas qu'il y ait de sol visible avec le brouillard
	if (couleurSol.getRouge() > 0) {
		glPushMatrix();
			GLfloat couleur[] = { couleurSol.getRouge(), couleurSol.getVert(), couleurSol.getBleu(), 0};
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, couleur);
			couleur[0] = couleurSol.getRouge() * 2;
			couleur[1] = couleurSol.getVert() * 2;
			couleur[2] = couleurSol.getBleu() * (2/3.0);
			glMaterialfv(GL_FRONT, GL_SPECULAR, couleur);
			glTranslatef(0, 0, -0.5);
			dessineSol();
		glPopMatrix();
	}
	for (int i = 0; i < nbrEntitees; i++) {
		this->contenu[i]->dessine3D();
	}
}

/**
 * Initialise la display list du sol de la case
 * @return void
 */
void Case::initDisplayList() {
	glNewList(DisplayListPool::getInstance()->getList(SURFACE_SOL_LIST), GL_COMPILE);
		Surface::dessineSurface(-0.5, 0.5, -0.5, 0.5);
	glEndList();
}

/**
 * Initialise la case
 * @return void
 */
void Case::initCase() {
	int code = this->code;
	Drawable *pastille = 0;
	if (code >= SUPER_PASTILLE) {
		// on donne le code de la display liste 3D, la 2D étant d'une valeur 3D + 1
		pastille = new PastilleView(coord, DisplayListPool::getInstance()->getList(SUPER_PASTILLE_3D_LIST));
		this->hasPastille = SUPER_PASTILLE;
	}
	else if (code >= PASTILLE) {
		// on donne le code de la display liste 3D, la 2D étant d'une valeur 3D + 1
		pastille = new PastilleView(coord, DisplayListPool::getInstance()->getList(PASTILLE_3D_LIST));
		this->hasPastille = PASTILLE;
	}
	code %= PASTILLE;

	if (code >= MUR_GAUCHE_INV) 
		this->contenu[this->nbrEntitees++] = new MurGaucheView(coord, COULEUR_MUR_INV);
	code %= MUR_GAUCHE_INV;
	if (code >= MUR_HAUT_INV) 
		this->contenu[this->nbrEntitees++] = new MurHautView(coord, COULEUR_MUR_INV);
	code %= MUR_HAUT_INV;

	if (code >= MUR_GAUCHE) 
		this->contenu[this->nbrEntitees++] = new MurGaucheView(coord, COULEUR_MUR);
	code %= MUR_GAUCHE;
	if (code >= MUR_HAUT) 
		this->contenu[this->nbrEntitees++] = new MurHautView(coord, COULEUR_MUR);
	if (this->hasPastille > 0)
		this->contenu[this->nbrEntitees++] = pastille;
}

/**
 * Vérifie une pastille
 * @return int La pastille contenue dans la case
 */
int Case::checkPastille() {
	int pastilleContenue = this->hasPastille;
	if (pastilleContenue > 0) {
		this->hasPastille = - 1;
		this->nbrEntitees--;
	}
	return pastilleContenue;
}

/**
 * Modifie le code d'une case
 * @param coord Nouvelle coordonnée
 * @return void
 */
void Case::setCoord(Coordonnee coord) {
	this->coord.setCoord(coord);
}