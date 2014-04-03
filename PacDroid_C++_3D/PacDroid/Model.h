// Model.h
#pragma once

#include "PacmanView.h"
#include <sstream>

class Model
{
private:
	static Model *instance;
	PacmanView *pacman;

	// Informations sur l'état du jeu
	int score, scoreTotal, status, niveau, nbrVies;

	// Constructeur
	Model();
public:
	// Singleton
	static Model *getInstance();

	// Modifications de l'état du jeu
	void firstLevel();
	void levelUp();
	void pauseUnpause();
	void resetLevel();
	void setStatus(int newStatus);

	// Vérification sur l'état du jeu
	bool gameOver();
	bool isPaused();

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