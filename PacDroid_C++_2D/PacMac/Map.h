// Map.h
#pragma once

#include "Model.h"
#include "Pacman.h"
#include "Fantome.h"

class Model;
class Pacman;
class Fantome;
class Map
{
private:
	static Map *instance;
	Model *model;
	Pacman *pacman;
	Fantome *fantomes;
	int **map;
	int nbrLignes, nbrColonnes, nbFantomes, nbrPastilles;
	float ligneFantomeInit, colonneFantomeInit;

	Map();
public:
	// Singleton
	static Map *getInstance();

	// Map du jeu
	void loadMaps(int nbrLignes, int nbrColonnes);
	void setNbrPastilles(int newNbrPastilles);
	void setNbFantomes(int newNbFantomes);
	void setLigneFantomeInit(int newLigneFantomeInit);
	void setColonneFantomeInit(int newColonneFantomeInit);
	bool decrementNbrPastilles();

	// Verifications
	bool viragePossible(float posLigne, float posColonne, int directionVoulue, bool traverse);
	bool deplacementPossible(float posLigne, float posColonne, int direction, bool traverse);
	bool verifierPastilles();
	bool verifierFantomes();

	// Getters
	int ** getMap() {
		return map;
	}
	int getNbrLignes() {
		return nbrLignes;
	}
	int getNbrColonnes() {
		return nbrColonnes;
	}
	int getNbFantomes() {
		return nbFantomes;
	}
	float getLigneFantomeInit() {
		return ligneFantomeInit;
	}
	float getColonneFantomeInit() {
		return colonneFantomeInit;
	}
	Fantome *getFantomes() {
		return fantomes;
	}
};