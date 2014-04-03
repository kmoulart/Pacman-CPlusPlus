// TextView.cpp

#include "TextView.h"
#include "MyGlut.h"

using namespace glut;

/**
 * Constructeur avec une string
 * @param text Texte du TextView
 */
TextView::TextView(string text) 
{
	this->text = text;
	this->couleur = Couleur(1, 1, 1);
}

/**
 * Constructeur avec une string et une couleur
 * @param text Texte du TextView
 * @param couleur Couleur du TextView
 */
TextView::TextView(string text, Couleur couleur)
{
	this->text = text;
	this->couleur = couleur;
}

/**
 * Place le texte sur l'espace de dessin
 * @param cPlacement Coordonnée du TextView
 * @return void
 */
void TextView::placer(const Coordonnee &cPlacement) {
	glPushMatrix();
	glTranslated(cPlacement.getX(), cPlacement.getY(), 0);
		// le 119.05 vient de la documentation, il s'agit de la hauteur maximale d'un caractère en glutStrokeCharacter
		glScaled(1/119.05, 1/119.05, 1);
		glColor3f(this->couleur.getRouge(), this->couleur.getVert(), this->couleur.getBleu());
		for (unsigned int i = 0; i < this->text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, this->text[i]);
		}
	glPopMatrix();
}

/**
 * Calcule la largeur du texte
 * @return float Largueur du texte du TextView
 */
float TextView::computeLargeur() {
	return glutStrokeLength(GLUT_STROKE_ROMAN, (unsigned char *) this->text.c_str()) / 119.05;
}

/**
 * Modifie le texte du TextView
 * @param text Nouveau text du TextView
 * @return void
 */
void TextView::setText(string text) {
	this->text = text;
}

/**
 * Modifie la couleur du texte
 * @param couleur Nouvelle couleur du TextView
 * @return void
 */
void TextView::modifierCouleurs(Couleur couleur) {
	this->couleur = couleur;
}