// PastilleView.h
#pragma once

#include "PastilleModel.h"
#include "Drawable.h"

class PastilleView : 
	public Drawable, public PastilleModel
{
private:
	// Initialisation des display lists
	static void initDisplayLists2D();
	static void initDisplayLists3D();

public:
	// Constructeur
	PastilleView(Coordonnee coord, int type);

	// Méthodes de dessin
	virtual void dessine2D();
	virtual void dessine3D();

	// Initialisation des display lists
	static void initDisplayLists();
};