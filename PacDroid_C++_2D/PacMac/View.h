// View.h
#pragma once

#include "Model.h"
#include "ViewJeu.h"
#include "ViewInfos.h"
#include "ControllerButton.h"

class View
{
private:
	static View *instance;
	int h_global, w_global;
	int x_dessin, y_dessin;

	View();
public:
	// Singletons
	static View *getInstance();

	void display();
	void reshape(int w, int h);
	void reshape();
	void redraw();

	// Getters
	int getHGlobal() {
		return h_global;
	}
	int getWGlobal() {
		return w_global;
	}
};
