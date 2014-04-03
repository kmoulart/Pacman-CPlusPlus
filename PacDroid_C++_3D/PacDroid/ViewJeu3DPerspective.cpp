// ViewJeu3DPerspective.cpp

#include "ViewJeu3DPerspective.h"
#include "Constantes.h"
#include "MyGlut.h"
using namespace glut;

// Les membres static non constants doivent êtres initialisés dans le .cpp
ViewJeu *ViewJeu3DPerspective::instance = 0;

/**
 * Constructeur vide de la vue 3D perspective
 */
ViewJeu3DPerspective::ViewJeu3DPerspective() : ViewJeu3D() {
	this->zoom = 60;
}

/**
 * Renvoi l'unique instance de la vue (Application du pattern singleton)
 * @return ViewJeu* Pointeur vers l'instance unique de la classe
 */
ViewJeu *ViewJeu3DPerspective::getInstance() {
	if (ViewJeu3DPerspective::instance == 0 )
		instance = dynamic_cast<ViewJeu *>(new ViewJeu3DPerspective());
	return instance;
}

/**
 * Zoom sur la scène de jeu
 * @return void
 */
void ViewJeu3DPerspective::zoomer() {
	if (zoom > MIN_ZOOM_PERSPECTIVE)
		this->zoom -= PAS_ZOOM_PERSPECTIVE;
}

/**
 * Dézoom sur la scène de jeu
 * @return void
 */
void ViewJeu3DPerspective::dezoomer() {
	if (zoom < MAX_ZOOM_PERSPECTIVE)
		this->zoom += PAS_ZOOM_PERSPECTIVE;
}

/**
 * Définit le type de projection (ici un type perspective)
 * @return void
 */
void ViewJeu3DPerspective::projection() {
	gluPerspective(this->zoom, wvp/hvp, 1.0, 200.0);
}