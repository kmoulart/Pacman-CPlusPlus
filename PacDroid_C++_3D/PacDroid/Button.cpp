// Button.cpp

#include "Button.h"
#include "MyGlut.h"
using namespace glut;

/**
 * Constructeur vide de Button utilisé pour les tableaux
 */
Button::Button() {
	text.reset(new TextView("", Couleur(0, 0, 1)));
	this->bCouleur = Couleur(0, 0, 1);
	this->fCouleur = Couleur(0, 0, 0.3);
	pressed = false;
}

/**
 * Constructeur avec une string
 * @param s Text du bouton
 */
Button::Button(string s) {
	text.reset(new TextView(s, Couleur(0, 0, 1)));
	this->bCouleur = Couleur(0, 0, 1);
	this->fCouleur = Couleur(0, 0, 0.3);
	pressed = false;
}

/**
 * Destructeur
 */
Button::~Button() {
	text.reset();
}

/**
 * Inverse le background et le foreground du bouton
 * @return void
 */
void Button::change() {
	Couleur bCouleur = this->bCouleur;
	setBackground(this->fCouleur);
	setForeground(bCouleur);
	setCouleurText(this->bCouleur);
}

/**
 * Modifie la couleur du texte du bouton
 * @param couleur Nouvelle couleur du texte du bouton
 * @return void
 */
void Button::setCouleurText(Couleur couleur) {
	this->text.get()->modifierCouleurs(couleur);
}

/**
 * Modifie la couleur du background du bouton
 * @param couleur Nouvelle couleur du fond du bouton
 * @return void
 */
void Button::setBackground(Couleur couleur) {
	this->bCouleur = couleur;
}

/**
 * Modifie la couleur du foreground du bouton
 * @param couleur Nouvelle couleur d'avant plan du bouton
 * @return void
 */
void Button::setForeground(Couleur couleur) {
	this->fCouleur = couleur;
}

/**
 * Test si l'utilisateur clique sur un bouton
 * @param cClick Coordonnée à tester avec la coordonnée du bouton
 * @return bool Vérifie si une collision a eu lieu avec la coordonnée donnée
 */
bool Button::click(const Coordonnee &cClick) {
	if (cClick.getX() >= leftSide && cClick.getX() <= rightSide) {
		if (cClick.getY() >= bottomSide && cClick.getY() <= topSide) {
			return true;
		}
	}
	return false;
}

/**
 * Simule une pression et change l'etat du bouton
 * @return void
 */
void Button::press() {
	if (pressed)
		return;
	change();
	pressed = true;
}

/**
 * Simule le relachement et change l'etat du bouton
 * @return void
 */
void Button::release() {
	if (!pressed)
		return;
	change();
	pressed = false;
}

/**
 * Place le bouton sur l'espace de dessin
 * @param cPlacement Coordonnée du bouton
 * @return void
 */
void Button::placer(const Coordonnee &cPlacement) {
	// Coordonnées du texte dans le bouton
	static const Coordonnee cText(0, 0.3);
	glPushMatrix();
		glTranslated(cPlacement.getX(), cPlacement.getY(), 0);
		glColor3f(this->bCouleur.getRouge(), this->bCouleur.getVert(), this->bCouleur.getBleu());
		glRectd(-0.35, -0.1, this->text.get()->computeLargeur() + 0.35, 1.6);
		glPushMatrix();
			glColor3f(this->fCouleur.getRouge(), this->fCouleur.getVert(), this->fCouleur.getBleu());
			glRectd(-0.2, 0.05, this->text.get()->computeLargeur() + 0.2, 1.45);
		glPopMatrix();
		this->text.get()->placer(cText);
	glPopMatrix();
	leftSide = cPlacement.getX() - 0.35;
	rightSide = cPlacement.getX() + this->text.get()->computeLargeur() + 0.35;
	topSide = cPlacement.getY() + 1.6;
	bottomSide = cPlacement.getY() - 0.1;
}

/**
 * Modifie le texte du bouton
 * @param s Nouveau texte du bouton
 * @return void
 */
void Button::setText(string s) {
	this->text.get()->setText(s);
}