// ControllerButton.h
#pragma once

#include "Constantes.h"
#include "Model.h"
#include "PacmanView.h"
#include "Button.h"

class PacmanView;
class ControllerButton
{
private:
	static ControllerButton *instance;
	Model *model;
	PacmanView *pacman;
	Button *tabButton;

	// Données de la viewport
	Coordonnee coordViewport;
	float hvp, wvp, hController, wController;

	// Données de l'univers de dessin
	Coordonnee coordDessin;
	float leftSideController, rightSideController, bottomSideController, topSideController;
	
	// Constructeur
	ControllerButton();

	void viewport();
	void computeViewPort();
	void afficheButtons();
public:
	// Singleton
	static ControllerButton *getInstance();

	// Controleur souris
	void mouse(int button, int state, const Coordonnee &cClick);

	// Affichage
	void display();
	void reshape();
	void redraw();
};