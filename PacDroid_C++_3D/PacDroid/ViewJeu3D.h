// ViewJeu3D.h
#pragma once

#include "ViewJeu.h"
#include "Camera.h"

class ViewJeu;
class ViewJeu3D :
	public ViewJeu
{
private:
	Camera *camera;

	void init();

protected:
	// Constructeur
	ViewJeu3D();

public:
	// Viewport
	virtual void viewport();
	virtual void projection() = 0;

	// Affichage
	virtual void dessineMap();
	virtual void display();
};
