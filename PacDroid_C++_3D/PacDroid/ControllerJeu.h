// ControllerJeu.h
#pragma once

#include "Model.h"
#include "MapView.h"
#include "ViewJeu.h"
#include "PacmanView.h"

class ControllerJeu
{
private:
	static ControllerJeu *instance;
	Model *model;
	MapView *map;
	ViewJeu *viewJeu;
	PacmanView *pacman;

	// Pivot utilisé pour le repérage du click de la souris
	int pivot;

	// Constructeur
	ControllerJeu();
public:
	// Singleton
	static ControllerJeu *getInstance();

	// Controleurs
	void keyPressed(int key, const Coordonnee &cMouse);
	void picking(int button, int state, const Coordonnee &c);
	void animateDisplay();
};