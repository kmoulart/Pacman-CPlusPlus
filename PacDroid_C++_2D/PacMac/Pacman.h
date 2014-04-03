// Pacman.h
#pragma once

#include "Model.h"

// Fixe la taille de l'angle de la bouche de PacMan
#define ANGLE_BOUCHE 90 
// Direction initiale de PacMan
#define DIRECTION_INIT 270
// Durée du mode super PacMan
#define DUREE_SUPER_PAC 10

class Pacman
{
private:
	static Pacman *instance;
	float posX, posY;
	float nbCaseRestanteSuper;
	int angleBoucheCourant, direction, directionVoulue;
	int rouge, vert, bleu;
	bool super, gameOver;

	void deplacer();

	Pacman();
public:
	// Singleton
	static Pacman *getInstance(); 

	// Affichage
	void updatePosition();
	void dessine();
	void dessineGameOver(float thickness, float radius);
	void setPosX(float newPosX);
	void setPosY(float newPosY);
	void anime();
	
	// Super PacMan
	void invulnerable();
	void disableSuperPac();
	void decrementSuperPac();

	// Reset
	void reset();

	// Setters
	void setDirection(int direction);
	void setDirectionVoulue(int directionVoulue);
	void setGameOver(bool gameOver);

	// Getters
	float getPosX() {
		return posX;
	}
	float getPosY() {
		return posY;
	}
	int getDirection() {
		return direction;
	}
	int getDirectionVoulue() {
		return directionVoulue;
	}
	bool isSuper() {
		return super;
	}
};