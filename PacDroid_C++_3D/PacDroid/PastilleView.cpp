// PastilleView.cpp

#include "PastilleView.h"
#include "DisplayListPool.h"
#include "Constantes.h"
#include "MyGlut.h"
using namespace glut;

/**
 * Constructeur pour une pastille vue
 * @param coord Coordonnée de la pastille
 * @param type Type de la pastille
 */
PastilleView::PastilleView(Coordonnee coord, int type) : PastilleModel(coord, type) {
}

/**
 * Dessine la pastille en 2D
 * @return void
 */
void PastilleView::dessine2D() {
	glPushMatrix();
		glCallList(type + 1);
	glPopMatrix();
}

/**
 * Dessine la pastille en 3D
 * @return void
 */
void PastilleView::dessine3D() {
	glPushMatrix();
		glCallList(type);
	glPopMatrix();
}

/**
 * Initialise les display lists 2D des pastilles
 * @return void
 */
void PastilleView::initDisplayLists2D() {
	GLUquadricObj *pastille;
	pastille = gluNewQuadric();
	gluQuadricDrawStyle(pastille, GLU_FILL);
	
	glNewList(DisplayListPool::getInstance()->getList(PASTILLE_2D_LIST), GL_COMPILE);
		Couleur couleur = COULEUR_PASTILLE;
		glColor3f(couleur.getRouge(), couleur.getVert(), couleur.getBleu());
		gluDisk(pastille, 0, RAYON_PASTILLE, NB_SLICES_QUADRIQUES, 1);
	glEndList();

	glNewList(DisplayListPool::getInstance()->getList(SUPER_PASTILLE_2D_LIST), GL_COMPILE);
		couleur = COULEUR_SUPER_PASTILLE;
		glColor3f(couleur.getRouge(), couleur.getVert(), couleur.getBleu());
		gluDisk(pastille, 0, RAYON_SUPER_PASTILLE, NB_SLICES_QUADRIQUES, 1);
	glEndList();

	gluDeleteQuadric(pastille);
}

/**
 * Initialise les display lists 3D des pastilles
 * @return void
 */
void PastilleView::initDisplayLists3D() {
	GLUquadricObj *pastille;
	pastille = gluNewQuadric();
	gluQuadricDrawStyle(pastille, GLU_FILL);

	glNewList(DisplayListPool::getInstance()->getList(PASTILLE_3D_LIST), GL_COMPILE);
		Couleur couleur = COULEUR_PASTILLE;
		GLfloat couleurPastille[] ={ couleur.getRouge(), couleur.getVert(), couleur.getBleu(), 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, couleurPastille);
		couleurPastille[0] *= 2;
		couleurPastille[1] *= 2;
		couleurPastille[2] /= 2;
		glMaterialfv(GL_FRONT, GL_SPECULAR, couleurPastille);
		gluSphere(pastille, RAYON_PASTILLE*2, NB_SLICES_QUADRIQUES, NB_SLICES_QUADRIQUES);
	glEndList();

	glNewList(DisplayListPool::getInstance()->getList(SUPER_PASTILLE_3D_LIST), GL_COMPILE);
		couleur = COULEUR_SUPER_PASTILLE;
		GLfloat couleurSuperPastille[] ={ couleur.getRouge(), couleur.getVert(), couleur.getBleu(), 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, couleurSuperPastille);
		couleurSuperPastille[0] *= 2;
		couleurSuperPastille[1] *= 2;
		couleurSuperPastille[2] /= 2;
		glMaterialfv(GL_FRONT, GL_SPECULAR, couleurSuperPastille);
		gluSphere(pastille, RAYON_SUPER_PASTILLE*2, NB_SLICES_QUADRIQUES, NB_SLICES_QUADRIQUES);
	glEndList();
	
	gluDeleteQuadric(pastille);
}

/**
 * Initialise les displays lists des pastilles
 * @return void
 */
void PastilleView::initDisplayLists() {
	initDisplayLists2D();
	initDisplayLists3D();
}
