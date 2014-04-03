// Labyrinthe.h
#pragma once

#include <fstream>
#include "Model.h"
#include "Map.h"

using namespace std;

class Labyrinthe {
private:
	static Labyrinthe *instance;
	int nbrLignes, nbrColonnes;
	Map *map;

	Labyrinthe();

	// Dessine unités
	void dessineHaut(float red, float green, float blue);
	void dessineGauche(float red, float green, float blue);
	void dessine(int type);
	void dessineUnite();
	void dessineUniteSpecial();
	void load(ifstream &fichierLaby);
public:
	// Singleton
	static Labyrinthe *getInstance();

	void dessine();
	friend ifstream &operator>>(ifstream &fichier, Labyrinthe &laby);
};