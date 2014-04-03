// Model.h
#pragma once

#include <sstream>
#include "MyGlut.h"
#include "Fantome.h"
#include "Pacman.h"
#include "Map.h"
#include "ViewJeu.h"

// Chargement de l'application
#define LARGEUR_FENETRE_INIT 900
#define HAUTEUR_FENETER_INIT 400
#define EXTENSION ".xD"
// Codes pour le labyrinthe
#define SUPER_PASTILLE 32
#define PASTILLE 16
#define MUR_GAUCHE_INV 8
#define MUR_HAUT_INV 4
#define MUR_GAUCHE 2
#define MUR_HAUT 1
// Directions
#define DROITE 270
#define BAS 180
#define GAUCHE 90
#define HAUT 0
// Etats du jeu
#define PAUSE -1
#define START 1
#define GAME_OVER -2
// paramètres du pacman/fantomes
#define NB_VIES_DEBUT 3
#define VITESSE 0.04

using namespace glut;
class Fantome;
class Pacman;
class Map;
class Model
{
private:
	static Model *instance;
	Pacman *pacman;
	// Informations du jeu
	int score, scoreTotal, status, niveau, nbrVies;

	Model();
public:
	// Singleton
	static Model *getInstance();

	// Etat du jeu
	void firstLevel();
	void levelUp();
	void pauseUnpause();
	bool isPaused();
	void resetLevel();
	bool gameOver();
	void setStatus(int newStatus);

	// Vies du joueur
	void decrementNbrVies();
	void incrementNbrVies(); // Utilisé a des fins de test et debugging

	// Score du joueur
	void incrementScore();

	// Getters
	int getScore() {
		return score;
	}
	int getNiveau() {
		return niveau;
	}
	int getNbrVies() {
		return nbrVies;
	}
};