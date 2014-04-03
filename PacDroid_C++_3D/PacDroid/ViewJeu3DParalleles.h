// ViewJeu3DParalleles.h
#pragma once

#include "ViewJeu3D.h"

class ViewJeu3DParalleles :
	public ViewJeu3D
{
private:
	static ViewJeu *instance;

	// Constructeur
	ViewJeu3DParalleles();

public:
	//Singleton
	static ViewJeu *getInstance();

	// Affichage
	virtual void zoomer();
	virtual void dezoomer();

	// Methode héritée
	virtual void projection();
};

