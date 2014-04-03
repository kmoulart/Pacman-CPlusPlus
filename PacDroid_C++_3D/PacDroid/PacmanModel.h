// PacmanModel.h
#pragma once

#include "EntiteMobile.h"

class PacmanModel :
	public EntiteMobile
{
private:
	static PacmanModel *instance;
	float tempsRestantSuper;

protected:
	int angleBoucheCourant, directionVoulue;

	// Constructeur
	PacmanModel();

public:
	// Singleton
	static PacmanModel *getInstance(); 

	// Méthode héritée
	virtual void updatePosition();

	// Animation du pacman
	void anime();
	
	// Super Pacman
	void invulnerable();
	void disableSuperPac();
	void decrementSuperPac();

	// Initialisation
	void init(const Coordonnee &c);

	// Reset
	virtual void reset();

	// Setter
	void setDirectionVoulue(int directionVoulue);

	// Getter
	int getDirectionVoulue() {
		return directionVoulue;
	}
};