// MurHautView.h
#pragma once

#include "MurView.h"

class MurHautView : public MurView
{
public:
	// Constructeur
	MurHautView(Coordonnee coord, Couleur couleur);

	// M�thodes de dessin
	virtual void dessine2D();
	virtual void dessine3D();
};

