#pragma once

#include "PacmanModel.h"
#include "Drawable.h"
#include "MyGlut.h"

using namespace glut;

class PacmanView :
	public Drawable, public PacmanModel
{
private:
	static PacmanView *instance;
	static void MyMaterial(GLenum mode,GLfloat *f,GLfloat alpha);
	static void SelectMaterial(int i);
	
	// Constructeur
	PacmanView();

public:
	// Singleton
	static PacmanView *getInstance(); 

	// Méthodes de dessin
	virtual void dessine2D();
	virtual void dessine3D();

	// Initialisation de la display list
	static void initDisplayList();
};

