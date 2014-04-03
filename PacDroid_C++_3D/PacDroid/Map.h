// Map.h
#pragma once

#include "Model.h"
#include "PacmanView.h"
#include "FantomeView.h"
#include "Case.h"
#include <fstream>

using namespace std;

class Model;
class PacmanView;
class FantomeView;
class Case;
class Map
{
private:
	Model *model;
	int nbrPastilles;

	// Charge le labyrinthe dans la structure de donnée
	void load(ifstream &fichierLaby);

protected:
	PacmanView *pacman;
	FantomeView *fantomes;
	Case **map;
	int nbrLignes, nbrColonnes, nbFantomes, angle;
	// Définit l'activité ou l'inactivité des différents modes d'affichage
	bool rotation, darkMode, firstPerson;

	// Constructeur
	Map();

public:
	// Redéfinition de l'opérateur utilisé pour le chargement du labyrinthe
	friend ifstream &operator>>(ifstream &fichier, Map &map);

	// Chargement et initialisations
	void loadMap(ifstream &fichierLaby, int nbrLignes, int nbrColonnes);
	void initFantomes(int newNbFantomes, float newColonneFantomeInit, float newLigneFantomeInit);
	void initPacman(int newColonnePacmanInit, int newLignePacmanInit);
	void initMap(int nbrLignes, int nbrColonnes);

	// Verifications
	bool viragePossible(const Coordonnee &coord, int directionVoulue, bool traverse);
	bool deplacementPossible(const Coordonnee &coord, int direction, bool traverse);
	bool verifierPastilles();
	bool decrementNbrPastilles();
	bool verifierFantome(int i);

	// Setters
	void setFirstPerson(bool firstPerson);
	void setDarkMode(bool activer);
	void setRotation(bool rotation);
	void setAngle(int angle);

	// Getters
	int getNbrLignes() {
		return nbrLignes;
	}
	int getNbrColonnes() {
		return nbrColonnes;
	}
	int getNbFantomes() {
		return nbFantomes;
	}
	FantomeView *getFantomes() {
		return fantomes;
	}
	int getAngle() {
		return angle;
	}
	bool isRotation() {
		return rotation;
	}
	bool isDarkMode() {
		return darkMode;
	}
	bool isFirstPerson() {
		return firstPerson;
	}
};