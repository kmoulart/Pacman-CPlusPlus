// ViewJeu3DParalleles.cpp

#include "ViewJeu3DParalleles.h"
#include "Constantes.h"

// Les membres static non constants doivent �tres initialis�s dans le .cpp
ViewJeu *ViewJeu3DParalleles::instance = 0;

/**
 * Constructeur vide de la vue 3D parall�le
 */
ViewJeu3DParalleles::ViewJeu3DParalleles() : ViewJeu3D() {
	this->zoom = 0;
}

/**
 * Renvoi l'unique instance de la vue (Application du pattern singleton)
 * @return ViewJeu* Pointeur vers l'instance unique de la classe
 */
ViewJeu *ViewJeu3DParalleles::getInstance() {
	if (ViewJeu3DParalleles::instance == 0 )
		instance = dynamic_cast<ViewJeu *>(new ViewJeu3DParalleles());
	return instance;
}

/**
 * Zoom sur la sc�ne de jeu
 * @return void
 */
void ViewJeu3DParalleles::zoomer() {
	if (zoom > MIN_ZOOM_PARALLELE)
		this->zoom -= PAS_ZOOM_PARALLELE;
}

/**
 * D�zoom sur la sc�ne de jeu
 * @return void
 */
void ViewJeu3DParalleles::dezoomer() {
	if (zoom < MAX_ZOOM_PARALLELE)
		this->zoom += PAS_ZOOM_PARALLELE;
}

/**
 * D�finit le type de projection (ici une vue parall�le)
 * @return void
 */
void ViewJeu3DParalleles::projection() {
	glOrtho((- map->getNbrColonnes() - this->zoom)/2.0, (map->getNbrColonnes() + this->zoom)/2.0, - map->getNbrLignes() - this->zoom / 2.0, this->zoom / 2.0, 1.0, 200.0);
}