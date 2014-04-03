// MurView.cpp

#include "MurView.h"
#include "Surface.h"
#include "DisplayListPool.h"
#include "Constantes.h"
#include "MyGlut.h"

using namespace glut;

/**
 * Constructeur d'une vue pour un mur
 * @param coord Coordonnée du mur
 * @param couleur Couleur du mur
 */
MurView::MurView(Coordonnee coord, Couleur couleur) : Entite(coord, couleur) {
}

/**
 * Initialise la display list 2D du mur
 * @return void
 */
void MurView::initDisplayList2D() {
	glNewList(DisplayListPool::getInstance()->getList(MUR_HAUT_2D_LIST), GL_COMPILE);
		glBegin(GL_LINES);
			glVertex2f(-0.5, 0.5);
			glVertex2f(0.5, 0.5);
		glEnd();
	glEndList();
}

/**
 * Initialise la display list 3D du mur
 * @return void
 */
void MurView::initDisplayList3D() {
	glPushMatrix();
		glNewList(DisplayListPool::getInstance()->getList(MUR_HAUT_3D_LIST), GL_COMPILE);
			glTranslated(0.0, 0.5, 0.0);
			/* A des fins esthétiques, les murs ont une forme vue du dessus ressemblant à ceci : 

					face arrière gauche				face arrière			face arrière droite
									 ________________________________________
									/										 \
									\________________________________________/

					face avant gauche				face avant				face avant droite

				Les commentaires détaillant chaque face sont écrit du point de vue de la normale, donc
				faisant face à la face décrite */
			
			glBegin(GL_QUADS);
			// Face arrière gauche du mur
				glNormal3f(-1.0, 1.0, 0.0);
				// coin inférieur gauche
				glVertex3f(-0.5, EPAISSEUR_MUR, -0.5);
				// coin inférieur droit
				glVertex3f(-0.5 - EPAISSEUR_MUR, 0.0, -0.5);
				// coin supérieur droit
				glVertex3f(-0.5 - EPAISSEUR_MUR, 0.0, 0.5);
				// coin supérieur gauche
				glVertex3f(-0.5, EPAISSEUR_MUR, 0.5);
			
			// Face arrière droite du mur
				glNormal3f(1.0, 1.0, 0.0);
				// coin inférieur gauche
				glVertex3f(0.5 + EPAISSEUR_MUR, 0.0, -0.5);
				// coin inférieur droit
				glVertex3f(0.5, EPAISSEUR_MUR, -0.5);
				// coin supérieur droit
				glVertex3f(0.5, EPAISSEUR_MUR, 0.5);
				// coin supérieur gauche
				glVertex3f(0.5 + EPAISSEUR_MUR, 0.0, 0.5);

			// Face avant droite du mur
				glNormal3f(1.0, -1.0, 0.0);
				// coin inférieur gauche
				glVertex3f(0.5 + EPAISSEUR_MUR, 0.0, -0.5);
				// coin inférieur droit
				glVertex3f(0.5, -EPAISSEUR_MUR, -0.5);
				// coin supérieur droit
				glVertex3f(0.5, -EPAISSEUR_MUR, 0.5);
				// coin supérieur gauche
				glVertex3f(0.5 + EPAISSEUR_MUR, 0.0, 0.5);

			// Face avant gauche du mur
				glNormal3f(-1.0, -1.0, 0.0);
				// coin inférieur gauche
				glVertex3f(-0.5, -EPAISSEUR_MUR, -0.5);
				// coin inférieur droit
				glVertex3f(-0.5 - EPAISSEUR_MUR, 0.0, -0.5);
				// coin supérieur droit
				glVertex3f(-0.5 - EPAISSEUR_MUR, 0.0, 0.5);
				// coin supérieur gauche
				glVertex3f(-0.5, -EPAISSEUR_MUR, 0.5);
			glEnd();

			// Face arrière du mur
			glPushMatrix();
				glTranslatef(0, EPAISSEUR_MUR, 0);
				glRotated(90, 1, 0, 0);
				Surface::dessineSurface(-0.5, 0.5, -0.5, 0.5);
			glPopMatrix();

			// Face avant du mur
			glPushMatrix();
				glTranslatef(0, -EPAISSEUR_MUR, 0);
				glRotated(-90, 1, 0, 0);
				Surface::dessineSurface(-0.5, 0.5, -0.5, 0.5);
			glPopMatrix();
		
			// Face haut du mur
			glPushMatrix();
				glTranslatef(0, 0, 0.5);
				Surface::dessineSurface(-0.5, 0.5, -EPAISSEUR_MUR, EPAISSEUR_MUR);
			glPopMatrix();
		glEndList();
	glPopMatrix();
}

/**
 * Initialise la display list des murs 2D et 3D
 * @return void
 */
void MurView::initDisplayLists() {
	initDisplayList2D();
	initDisplayList3D();
}

/**
 * Dessine le mur haut en 2D
 * @return void
 */
void MurView::dessineMur2D() {
	glPushMatrix();
		glColor3f(couleur.getRouge(), couleur.getVert(), couleur.getBleu());
		glCallList(DisplayListPool::getInstance()->getList(MUR_HAUT_2D_LIST));
	glPopMatrix();
}

/**
 * Dessine le mur haut en 3D
 * @return void
 */
void MurView::dessineMur3D() {
	glPushMatrix();
		GLfloat couleurMur[] ={ couleur.getRouge(), couleur.getVert(), couleur.getBleu(), 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, couleurMur);
		GLfloat couleurS[] ={ 1, 1, 0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, couleurS);
		glCallList(DisplayListPool::getInstance()->getList(MUR_HAUT_3D_LIST));
	glPopMatrix();
}