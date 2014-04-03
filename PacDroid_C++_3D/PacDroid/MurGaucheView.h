// MurGaucheView.h
#pragma once

#include "MurView.h"

class MurGaucheView : public MurView
{
public:
	// Constructeur
	MurGaucheView(Coordonnee coord, Couleur couleur);

	// Méthodes de dessin
	virtual void dessine2D();
	virtual void dessine3D();
};

