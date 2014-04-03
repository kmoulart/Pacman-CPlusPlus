// ViewJeu2D.cpp

#include "ViewJeu2D.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
ViewJeu *ViewJeu2D::instance = 0;

/**
 * Constructeur de la view 2D vide
 */
ViewJeu2D::ViewJeu2D() : ViewJeu() {
}

/**
 * Renvoi l'unique instance de la vue 2D (Application du pattern singleton)
 * @return ViewJeu* Pointeur vers l'instance unique de la classe
 */
ViewJeu *ViewJeu2D::getInstance() {
	if (ViewJeu2D::instance == 0 )
		instance = dynamic_cast<ViewJeu *>(new ViewJeu2D());
	return instance;
}

/**
 * Initialise la viewport de ViewJeu2D
 * @return void
 */
void ViewJeu2D::viewport() {
	glViewport(coordViewport.getX(), coordViewport.getY(), wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	projection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Définit le type de projection
 * @return void
 */
void ViewJeu2D::projection() {
	gluOrtho2D(leftSideLaby, rightSideLaby, bottomSideLaby, topSideLaby);
}

/**
 * Dessine le labyrinthe
 * @return void
 */
void ViewJeu2D::dessineMap() {
	map->dessine2D();
}

/**
 * Réaffiche la vue
 * @return void
 */
void ViewJeu2D::display() {
	viewport();
	dessineMap();
}