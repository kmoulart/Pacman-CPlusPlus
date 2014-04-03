// MurView.h
#pragma once

#include "Entite.h"
#include "Drawable.h"

class MurView : public Drawable, public Entite
{
private:
	// M�thodes d'initialisation des display lists
	static void initDisplayList2D();
	static void initDisplayList3D();

protected:
	// Constructeur
	MurView(Coordonnee coord, Couleur couleur);

public:
	static void initDisplayLists();

	// M�thodes de dessin
	void dessineMur2D();
	void dessineMur3D();
};

