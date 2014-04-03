// EntiteMobile.h
#pragma once

#include "Entite.h"

class EntiteMobile :
	public Entite
{
protected:
	unsigned int direction;
	bool special;
	bool mort;
	Coordonnee coordInitiales;

	// Couleurs normale et sp�ciale utilis�es pour la 2D
	Couleur cNormal;
	Couleur cSpecial;

	// Constructeurs
	EntiteMobile();

	void deplacer();
public:
	// D�placements
	virtual void updatePosition() = 0;
	virtual void reset();

	// Setters
	void setSpecial(bool special);
	void setMort(bool mort);

	// Getters
	bool isSpecial() {
		return special;
	}
	bool isMort() {
		return mort;
	}
	unsigned int getDirection() {
		return direction;
	}
};

