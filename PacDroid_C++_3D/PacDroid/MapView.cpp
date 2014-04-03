// MapView.cpp

#include "MapView.h"
#include "FantomeView.h"
#include "PacmanView.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
MapView *MapView::instance = 0;

/**
 * Constructeur vide de la map view
 */
MapView::MapView() : Map() {
}

/**
 * Renvoi l'unique instance de la map (Application du pattern singleton)
 * @return MapView* Pointeur vers l'instance unique de la classe
 */
MapView *MapView::getInstance(){
	if (instance == 0)
		instance = new MapView();
	return instance;
}

/**
 * Dessine les éléments de la map en 2D
 * @return void
 */
void MapView::dessine2D() {
	glPushMatrix();
		glTranslated(0,-1, 0);
		for (int x = nbrLignes; x >= 0; x--) {
			for (int y = 0; y < nbrColonnes + 1; y++) {
				glPushMatrix();
					glTranslated(y, x, 0);
					map[x][y].dessine2D();
				glPopMatrix();
			}
		}
	glPopMatrix();
	for (int i = 0; i < nbFantomes; i++) {
		fantomes[i].dessine2D();
	}
	pacman->dessine2D();
}

/**
 * Dessine les éléments de la map en 3D
 * @return void
 */
void MapView::dessine3D() {
	if (this->rotation) {
		this->angle = (this->angle + 1) % 360;
	}
	glPushMatrix();
		glTranslated(this->nbrColonnes/2.0 - 0.5, this->nbrLignes/2.0 - 0.5, 0);
		glRotated(this->angle, 0, 0, 1);
		glTranslated(-this->nbrColonnes/2.0 + 0.5, -this->nbrLignes/2.0 + 0.5, 0);
		glPushMatrix();
			glTranslated(0,-1, 0);
			for (int x = nbrLignes; x >= 0; x--) {
				for (int y = 0; y < nbrColonnes + 1; y++) {
					glPushMatrix();
						glTranslated(y, x, 0);
						map[x][y].dessine3D();
					glPopMatrix();
				}
			}
		glPopMatrix();
		for (int i = 0; i < nbFantomes; i++) {
			fantomes[i].dessine3D();
		}
		pacman->dessine3D();
	glPopMatrix();
}
