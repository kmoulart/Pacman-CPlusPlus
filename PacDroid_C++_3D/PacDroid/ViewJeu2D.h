// ViewJeu2D.h
#pragma once

#include "ViewJeu.h"

class ViewJeu;
class ViewJeu2D :
	public ViewJeu
{
private:
	static ViewJeu *instance;

	// Constructeur
	ViewJeu2D();
public:
	//Singleton
	static ViewJeu *getInstance();

	// Viewport
	virtual void viewport();
	virtual void projection();

	// Affichage
	virtual void dessineMap();
	virtual void display();
};
