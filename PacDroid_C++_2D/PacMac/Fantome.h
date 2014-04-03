// Fantome.h
#pragma once

#include "Model.h"
#include "Map.h"

class Model;
class Map;
class Fantome
{
private:
	Map *map;
	float posX, posY;
	int rouge, vert, bleu, direction;
	bool victime;
	bool mort;

	void deplacer();
	void deplacer(float posX, float posY);
public:
	// Constructeurs
	Fantome();
	Fantome(float posX, float posY);
	Fantome(float posX, float posY, int rouge, int vert, int bleu);

	void updatePosition();
	void dessine();
	void tuable(int rouge, int vert, int bleu, bool victime);
	void meurt();
	void reset();

	// Getters
	bool isMort() {
		return mort;
	}
	float getPosX() {
		return posX;
	}
	float getPosY() {
		return posY;
	}
	bool getVictime() {
		return victime;
	}
};