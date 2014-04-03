// FantomeModel.h
#pragma once

#include "EntiteMobile.h"

class FantomeModel :
	public EntiteMobile
{
private:
	// D�finit le degr� de difficult� d'un fantome en particulier
	// C'est a dire sa propension � suivre le pacman (en %)
	int difficulte;

	int* computeDirectionsPossibles();
	int findOptimalDirection();
	Coordonnee change(int direction, float value);

public:
	// Constructeur
	FantomeModel();

	// M�thode h�rit�e
	virtual void updatePosition();

	// Initialisation
	void init(const Coordonnee &c);

	// Setters
	void setDifficulte(int difficulte);
	void tuable(bool special);
	void meurt();
};