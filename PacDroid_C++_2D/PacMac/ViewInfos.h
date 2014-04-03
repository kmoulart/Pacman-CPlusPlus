// ViewInfos.h
#pragma once

#include "Model.h"
#include "View.h"
#include "TextView.h"

class ViewInfos
{
private:
	static ViewInfos *instance;
	Model *model;
	float hvp, wvp, xViewport, yViewport, leftSideInfos, rightSideInfos, bottomSideInfos, topSideInfos;

	// Viewport
	void viewport();
	void computeViewPort();

	// Affichage
	void dessineVie();
	void dessineVies();
	void afficheScore();
	void afficheNiveau();
	void afficheInfos();

	ViewInfos();
public:
	// Singleton
	static ViewInfos *getInstance();

	// Affichage
	void display();
	void reshape();
	void redraw();
};