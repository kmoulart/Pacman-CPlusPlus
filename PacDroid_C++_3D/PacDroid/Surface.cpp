// Surface.cpp

#include "Surface.h"
#include "Utils.h"
#include "MyGlut.h"

using namespace glut;

/**
 * Dessine une surface suivant une certaine finesse avec des plus petits polygones
 * @param left Valeur gauche de la surface
 * @param right Valeur droite de la surface
 * @param bottom Valeur basse de la surface
 * @param top Valeur haute de la surface
 * @return void
 */
void Surface::dessineSurface(float left, float right, float bottom, float top) {
	float finesse = 20.0;
	float largeur = 1/finesse * (right - left);
	float hauteur = 1/finesse * (top - bottom);

	int sens = 1;
	for (float ligne = bottom; ligne < top; ligne = Utils::floor2Decimal(ligne + hauteur)) {
		glBegin(GL_QUAD_STRIP);
		for (float colonne = left; colonne <= right; colonne = Utils::floor2Decimal(colonne + largeur))
		{
			glNormal3f(0, 0, 1);
			glVertex3f(colonne, Utils::floor2Decimal(ligne + Utils::floor2Decimal(sens * hauteur)), 0);
			glVertex3f(colonne, Utils::floor2Decimal(ligne + Utils::floor2Decimal((sens + 1)%2 * hauteur)), 0);
		}
		glEnd();
		sens = (sens + 1) % 2;
	}
}
