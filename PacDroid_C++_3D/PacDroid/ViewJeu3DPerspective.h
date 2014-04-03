// ViewJeu3DPerspective.h
#pragma once

#include "ViewJeu3D.h"

class ViewJeu3DPerspective :
	public ViewJeu3D
{
private:
	static ViewJeu *instance;

	// Constructeur
	ViewJeu3DPerspective();

public:
	//Singleton
	static ViewJeu *getInstance();

	// Affichage
	virtual void zoomer();
	virtual void dezoomer();

	// M�thode h�rit�e
	virtual void projection();
};

