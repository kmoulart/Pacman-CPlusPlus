// Case.h
#pragma once

#include "Drawable.h"
#include "Coordonnee.h"
#include "Couleur.h"
#include "Constantes.h"

class Case
{
private:
	Drawable *contenu[NB_ENTITE_MAX_PAR_CASE];
	Coordonnee coord;
	Couleur couleurSol;
	int hasPastille;
	int nbrEntitees;
	int code;

	void dessineSol();
public:
	// Constructeurs et destructeur
	Case();
	Case(Coordonnee coord, Couleur couleurSol, int code);
	~Case();

	// Affichage
	void dessine2D();
	void dessine3D();
	void initCase();

	// Verification
	int checkPastille();

	// Display list
	static void initDisplayList();

	// Setter
	void setCoord(Coordonnee coord);

	// Getter
	int getCode() {
		return code;
	}
};
