#pragma once

#include "FantomeModel.h"
#include "Drawable.h"
#include "MyGlut.h"
using namespace glut;

class FantomeView :
	public Drawable, public FantomeModel
{
private:
	static void MyMaterial(GLenum mode,GLfloat *f,GLfloat alpha);
	static void SelectMaterial(int i);

	// Initialisation des display lists
	static void initDisplayList2D();
	static void initDisplayList3D();

public:
	// Constructeur
	FantomeView();
	
	// Affichage
	virtual void dessine2D();
	virtual void dessine3D();

	// Initialisation des display lists
	static void initDisplayLists();
};

