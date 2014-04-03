// Button.cpp
#include "Button.h"

/*
 * Constructeur vide de Button utilisé pour les tableaux
 */
Button::Button() {
	text = new TextView("", 0, 0, 1);
	this->bRouge = 0;
	this->bVert = 0;
	this->bBleu = 1;
	this->fRouge = 0;
	this->fVert = 0;
	this->fBleu = 0.3;
	pressed = false;
}

/*
 * Constructeur avec une string
 * @param string s
 */
Button::Button(string s) {
	text = new TextView(s, 0, 0, 1);
	this->bRouge = 0;
	this->bVert = 0;
	this->bBleu = 1;
	this->fRouge = 0;
	this->fVert = 0;
	this->fBleu = 0.3;
	pressed = false;
}

/*
 * Destructeur
 */
Button::~Button() {
	delete text;
}

/*
 * Test si l'utilisateur clique sur un bouton
 * @param float x
 * @param float y
 * @return bool
 */
bool Button::click(float x, float y) {
	if (x >= leftSide && x <= rightSide) {
		if (y >= bottomSide && y <= topSide) {
			return true;
		}
	}
	return false;
}

/*
 * Simule une pression et change l'etat du bouton
 * @return void
 */
void Button::press() {
	if (pressed)
		return;
	change();
	pressed = true;
}

/*
 * Simule le relachement et change l'etat du bouton
 * @return void
 */
void Button::release() {
	if (!pressed)
		return;
	change();
	pressed = false;
}

/*
 * Inverse le background et le forground du bouton
 * @return void
 */
void Button::change() {
	float bRouge = this->bRouge, bVert = this->bVert, bBleu = this->bBleu;
	setBackground(this->fRouge, this->fVert, this->fBleu);
	setForeground(bRouge, bVert, bBleu);
	setCouleurText(this->bRouge, this->bVert, this->bBleu);
}

/*
 * Place le bouton sur l'espace de dessin
 * @param float x
 * @param float y
 * @return void
 */
void Button::placer(float x, float y) {
	glPushMatrix();
		glTranslated(x, y, 0);
		glColor3f(this->bRouge, this->bVert, this->bBleu);
		glRectd(-0.35, -0.1, this->text->computeLargeur() + 0.35, 1.6);
		glPushMatrix();
			glColor3f(this->fRouge, this->fVert, this->fBleu);
			glRectd(-0.2, 0.05, this->text->computeLargeur() + 0.2, 1.45);
		glPopMatrix();
		this->text->placer(0, 0.3);
	glPopMatrix();
	leftSide = x - 0.35;
	rightSide = x + this->text->computeLargeur() + 0.35;
	topSide = y + 1.6;
	bottomSide = y - 0.1;
}

/*
 * Modifie le texte du bouton
 * @param string s
 * @return void
 */
void Button::setText(string s) {
	this->text->setText(s);
}

/*
 * Modifie la couleur du texte du bouton
 * @param int rouge
 * @param int vert
 * @param int bleu
 * @return void
 */
void Button::setCouleurText(float rouge, float vert, float bleu) {
	this->text->modifierCouleurs(rouge, vert, bleu);
}

/*
 * Modifie la couleur du background du bouton
 * @param int rouge
 * @param int vert
 * @param int bleu
 * @return void
 */
void Button::setBackground(float rouge, float vert, float bleu) {
	bRouge = rouge;
	bVert = vert;
	bBleu = bleu;
}

/*
 * Modifie la couleur du foreground du bouton
 * @param int rouge
 * @param int vert
 * @param int bleu
 * @return void
 */
void Button::setForeground(float rouge, float vert, float bleu) {
	fRouge = rouge;
	fVert = vert;
	fBleu = bleu;
}