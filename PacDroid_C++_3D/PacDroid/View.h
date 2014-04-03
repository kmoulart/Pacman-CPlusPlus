// View.h
#pragma once
//VERIF_OK
#include "ViewJeu.h"

class ViewJeu;
class View
{
private:
	static View *instance;
	ViewJeu *viewJeu;
	
	// Dimensions de la fenêtre
	int h_global, w_global;

	// Constructeur
	View();
public:
	// Singletons
	static View *getInstance();

	// Strategy
	ViewJeu *getView();
	void changeView(ViewJeu *v);

	// Méthodes de vue
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
