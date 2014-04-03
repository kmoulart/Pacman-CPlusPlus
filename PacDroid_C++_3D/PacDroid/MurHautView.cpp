// MurHautView.cpp

#include "MurHautView.h"
#include "DisplayListPool.h"

/**
 * Constructeur d'une vue pour le mur de haut
 * @param coord Coordonnée du mur haut
 * @param couleur Couleur du mur haut
 */
MurHautView::MurHautView(Coordonnee coord, Couleur couleur) : MurView(coord, couleur) {
}

/**
 * Dessine le mur haut en 2D
 * @return void
 */
void MurHautView::dessine2D() {
	dessineMur2D();
}

/**
 * Dessine le mur haut en 3D
 * @return void
 */
void MurHautView::dessine3D() {
		dessineMur3D();
}
