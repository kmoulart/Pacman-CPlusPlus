// ViewInfos.h
#pragma once

#include "Model.h"
#include "Coordonnee.h"

class Model;
class ViewInfos
{
private:
	static ViewInfos *instance;
	Model *model;

	// Paramètres de la viewport
	Coordonnee coordViewport;
	float hvp, wvp, leftSideInfos, rightSideInfos, bottomSideInfos, topSideInfos;

	// Viewport
	void viewport();
	void computeViewPort();

	// Affichage
	void dessineVie();
	void dessineVies();
	void afficheScore();
	void afficheNiveau();
	void afficheInfos();

	// Contructeur
	ViewInfos();
public:
	// Singleton
	static ViewInfos *getInstance();

	// Affichage
	void display();
	void reshape();
	void redraw();

	// Initialisation de la display list
	static void initDisplayList();
};