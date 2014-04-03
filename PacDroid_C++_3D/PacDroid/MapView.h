// MapView.h
#pragma once

#include "Map.h"

class MapView :
	public Map
{
private:
	static MapView *instance;

	// Constructeur
	MapView();
public:
	// Singleton
	static MapView *getInstance();

	// M�thodes de dessin
	void dessine2D();
	void dessine3D();
};

