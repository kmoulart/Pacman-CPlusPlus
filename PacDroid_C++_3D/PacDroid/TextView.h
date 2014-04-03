// TextView.h
#pragma once

#include "Couleur.h"
#include "Coordonnee.h"
#include <string>

using namespace std;

class TextView
{
private:
	string text;
	Couleur couleur;

public:
	// Constructeurs et destructeurs
	TextView(string text);
	TextView(string text, Couleur couleur);

	
	// Place le texte
	virtual void placer(const Coordonnee &cPlacement);
	
	// Calcul sur le texte
	float computeLargeur();

	// Setters
	void setText(string text);
	void modifierCouleurs(Couleur couleur);

	// Getters
	string getText() {
		return text;
	}
};