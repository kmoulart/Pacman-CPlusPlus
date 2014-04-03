// View.cpp

#include "View.h"
#include "ViewJeu2D.h"
#include "ViewInfos.h"
#include "ControllerButton.h"
#include "DisplayListPool.h"
#include "MurView.h"
#include "Case.h"
#include "PastilleView.h"
#include "PacmanView.h"
#include "FantomeView.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
View *View::instance = 0;

/**
 * Constructeur de la view
 */
View::View() {
	h_global = HAUTEUR_FENETER_INIT;
	w_global = LARGEUR_FENETRE_INIT;
	viewJeu = 0;
	
	// Création des display listes pour un fantome
	FantomeView::initDisplayLists();
	
	// Création de la display liste pour pacman
	PacmanView::initDisplayList();

	// Création des display listes pour les murs
	MurView::initDisplayLists();

	// Création de la display liste pour le sol
	Case::initDisplayList();

	// Création des display listes pour les pastilles et super pastilles
	PastilleView::initDisplayLists();
	
	// Création de la display liste pour l'affichage des vies du pacman
	ViewInfos::initDisplayList();
}

/**
 * Renvoi l'unique instance de view (Application du pattern singleton)
 * @return View* Pointeur vers l'instance unique de la classe
 */
View *View::getInstance() {
	if (View::instance == 0) {
		instance = new View();
	}
	return instance;
}

/**
 * Retourne la vue du jeu en cours
 * @return ViewJeu* Pointeur vers l'instance de la vue jeu en cours
 */
ViewJeu *View::getView() {
	if (viewJeu == 0) {
		viewJeu = ViewJeu2D::getInstance();
		viewJeu->loadLaby();
	}
	return viewJeu;
}

/**
 * Change la vue du jeu
 * @param v Pointeur vers la nouvelle instance d'une vue de jeu
 * @return void
 */
void View::changeView(ViewJeu *v) {
	viewJeu = v;
	MapView::getInstance()->setFirstPerson(false);
	this->reshape();
}

/**
 * Affiche les différentes vues
 * @return void
 */
void View::display() {
	this->getView()->display();
	ViewInfos::getInstance()->display();
	ControllerButton::getInstance()->display();
}

/**
 * Redessine les différentes vues
 * @return void
 */
void View::redraw() {
	glutPostRedisplay();
}

/**
 * Redimensionne les vues en initialisant les variables de hauteur et largeur global
 * @param w Nouvelle largueur de la fenêtre
 * @param h Nouvelle hauteur de la fenêtre
 * @return void
 */
void View::reshape(int w, int h) {
	w_global = w;
	h_global = h;
	this->getView()->reshape();
	ViewInfos::getInstance()->reshape();
	ControllerButton::getInstance()->reshape();
}

/**
 * Redimensionne les vues
 * @return void
 */
void View::reshape() {
	this->getView()->reshape();
	ViewInfos::getInstance()->reshape();
	ControllerButton::getInstance()->reshape();
}
