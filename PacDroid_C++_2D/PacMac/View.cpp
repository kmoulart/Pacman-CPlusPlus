// View.cpp
#include "View.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
View *View::instance = 0;

/*
 * Constructeur du view
 */
View::View() {
	h_global = HAUTEUR_FENETER_INIT;
	w_global = LARGEUR_FENETRE_INIT;
}

/*
 * Renvoi l'unique instance de view (Singleton)
 * @return View *
 */
View *View::getInstance() {
	if (View::instance == 0 )
		instance = new View();
	return instance;
}

/*
 * Affiche les différentes vues
 * @return void
 */
void View::display() {
	ViewJeu::getInstance()->display();
	ViewInfos::getInstance()->display();
	ControllerButton::getInstance()->display();
}

/*
 * Redessine les différentes vues
 * @return void
 */
void View::redraw() {
	glutPostRedisplay();
}

/*
 * Redimensionne les vues en initialisant les variables de 
 * hauteur et largeur global
 * @param int w
 * @param int h
 * @return void
 */
void View::reshape(int w, int h) {
	w_global = w;
	h_global = h;
	ViewJeu::getInstance()->reshape();
	ViewInfos::getInstance()->reshape();
	ControllerButton::getInstance()->reshape();
}

/*
 * Redimensionne les vues
 * @return void
 */
void View::reshape() {
	ViewJeu::getInstance()->reshape();
	ViewInfos::getInstance()->reshape();
	ControllerButton::getInstance()->reshape();
}