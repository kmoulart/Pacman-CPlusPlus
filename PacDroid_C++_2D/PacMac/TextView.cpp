// TextView.cpp
#include "TextView.h"

/*
 * Constructeur avec une string
 * @param string text
 */
TextView::TextView(string text) 
{
	this->text = text;
	this->rouge = 1;
	this->vert = 1;
	this->bleu = 1;
}

/*
 * Constructeur avec une string
 * @param string text
 * @param int rouge
 * @param int vert
 * @param int bleu
 */
TextView::TextView(string text, int rouge, int vert, int bleu)
{
	this->text = text;
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
}

/*
 * Place le texte sur l'espace de dessin
 * @param float x
 * @param float y
 * @return void
 */
void TextView::placer(float x, float y) {
	glPushMatrix();
		glTranslated(x, y, 0);
		// le 119.05 vient de la documentation, il s'agit de la hauteur maximale d'un caractère en glutStrokeCharacter
		glScaled(1/119.05, 1/119.05, 1);
		glColor3f(this->rouge, this->vert, this->bleu);
		for (unsigned int i = 0; i < this->text.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, this->text[i]);
		}
	glPopMatrix();
}

/*
 * Calcule la largeur du texte
 * @param float x
 * @param float y
 * @return float
 */
float  TextView::computeLargeur() {
	return glutStrokeLength(GLUT_STROKE_ROMAN, (unsigned char *) this->text.c_str()) / 119.05;
}

/*
 * Modifie le texte du TextView
 * @param string text
 * @return void
 */
void TextView::setText(string text) {
	this->text = text;
}

/*
 * Modifie la couleur du texte
 * @param int rouge
 * @param int vert
 * @param int bleu
 * @return void
 */
void TextView::modifierCouleurs(int rouge, int vert, int bleu) {
	this->rouge = rouge;
	this->vert = vert;
	this->bleu = bleu;
}