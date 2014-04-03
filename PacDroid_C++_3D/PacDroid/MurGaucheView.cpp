// MurGaucheView.cpp

#include "MurGaucheView.h"
#include "DisplayListPool.h"
#include "Constantes.h"
#include "MyGlut.h"
using namespace glut;

/**
 * Constructeur d'une vue pour le mur de gauche
 * @param coord Coordonnée du mur gauche
 * @param couleur Couleur du mur gauche
 */
MurGaucheView::MurGaucheView(Coordonnee coord, Couleur couleur) : MurView(coord, couleur) {
}

/**
 * Dessine le mur gauche en 2D
 * @return void
 */
void MurGaucheView::dessine2D() {
	glPushMatrix();
		glRotated(GAUCHE, 0, 0, 1);
		dessineMur2D();
	glPopMatrix();
}

/**
 * Dessine le mur gauche en 3D
 * @return void
 */
void MurGaucheView::dessine3D() {
	glPushMatrix();
		glRotated(GAUCHE, 0, 0, 1);
		dessineMur3D();
	glPopMatrix();
}
