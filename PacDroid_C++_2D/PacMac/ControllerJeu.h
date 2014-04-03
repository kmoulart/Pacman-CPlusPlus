// ControllerJeu.h
#pragma once

#include "Model.h"
#include "ViewJeu.h"
#include "Pacman.h"
#include "Map.h"

// Temps de raffraichissement pour la bouche de pacman
#define TEMPS_BASE_BOUCHE 0.5 

class ControllerJeu
{
private:
	static ControllerJeu *instance;
	Model *model;
	ViewJeu *viewJeu;
	Pacman *pacman;

	ControllerJeu();
public:
	// Singleton
	static ControllerJeu *getInstance();

	// Controler
	void keyPressed(int key, int x, int y);
	void animateDisplay();
};