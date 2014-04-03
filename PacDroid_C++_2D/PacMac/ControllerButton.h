// ControllerButton.h
#pragma once

#include "Model.h"
#include "ViewJeu.h"
#include "Button.h"
#include "Pacman.h"

class ControllerButton
{
private:
	static ControllerButton *instance;
	Model *model;
	Pacman *pacman;
	Button *tabButton;
	float hvp, wvp, xViewport, yViewport, hController, wController;
	float leftSideController, rightSideController, bottomSideController, topSideController;
	float x_dessin, y_dessin;
	
	ControllerButton();

	void viewport();
	void computeViewPort();
	void afficheButtons();
public:
	// Singleton
	static ControllerButton *getInstance();

	// Controleur
	void mouse(int button, int state, int x, int y);

	// Affichage
	void display();
	void reshape();
	void redraw();
};