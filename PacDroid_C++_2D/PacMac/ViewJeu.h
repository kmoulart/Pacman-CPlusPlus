// ViewJeu.h
#pragma once

#include "Model.h"
#include "Labyrinthe.h"
#include "View.h"
#include "Pacman.h"

class Labyrinthe;
class ViewJeu
{
private:
	static ViewJeu *instance;
	Map *map;
	Labyrinthe *laby;
	Pacman *pacman;
	float hvp, wvp, xViewport, yViewport, leftSideLaby, rightSideLaby, bottomSideLaby, topSideLaby;

	// Viewport
	void viewport();
	void computeViewPort();

	// Affichage
	void dessineLaby();
	void dessinePacMan();
	void dessineFantomes();
	string getFileName();

	ViewJeu();
public:
	// Singletons
	static ViewJeu *getInstance();

	// Affichage
	void loadLaby();
	void display();
	void reshape();
	void redraw();

	// Getters
	float getHvp() {
		return hvp;
	}
	float getWvp() {
		return wvp;
	}
	float getXViewport() {
		return xViewport;
	}
	float getYViewport() {
		return yViewport;
	}
};
