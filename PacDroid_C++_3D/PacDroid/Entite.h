// Entite.h
#pragma once

#include "Coordonnee.h"
#include "Couleur.h"

class Entite
{
protected:
	Coordonnee coord;
	Couleur couleur;

	// Constructeurs
	Entite();
	Entite(Coordonnee coord, Couleur couleur);
public:

	// Setters
	void setCoord(Coordonnee coord);
	void setCouleur(Couleur couleur);

	// Getters
	Coordonnee getCoord() {
		return coord;
	}
};

