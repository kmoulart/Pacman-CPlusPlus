// ViewJeu.h
#pragma once

#include "MapView.h"
#include "Coordonnee.h"

class MapView;
class ViewJeu
{
protected:
	MapView *map;
	Coordonnee coordViewport;

	// Paramètres de la viewport
	float hvp, wvp, leftSideLaby, rightSideLaby, bottomSideLaby, topSideLaby;

	// Niveau de zoom actuel
	int zoom;
	
	string getFileName();

	// Constructeur
	ViewJeu();

public:
	// Viewport
	virtual void computeViewPort();
	virtual void viewport() = 0;

	// Affichage
	void redraw();
	virtual void zoomer();
	virtual void dezoomer();
	virtual void reshape();
	virtual void display() = 0;
	virtual void dessineMap() = 0;
	virtual void projection() = 0;
	
	// Chargement
	void loadLaby();

	// Getters
	float getHvp() {
		return hvp;
	}
	float getWvp() {
		return wvp;
	}
	float getXViewport() {
		return coordViewport.getX();
	}
	float getYViewport() {
		return coordViewport.getY();
	}
	int getZoom() {
		return zoom;
	}
};
