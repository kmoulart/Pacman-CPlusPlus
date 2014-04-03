// TextView.h
#pragma once

#include "MyGlut.h"
#include <string>

using namespace std;
using namespace glut;

class TextView
{
private:
	string text;
	int rouge;
	int vert;
	int bleu;

public:
	// Constructeurs
	TextView(string text);
	TextView(string text, int rouge, int vert, int bleu);
	
	void placer(float x, float y);
	float computeLargeur();
	void setText(string text);
	void modifierCouleurs(int rouge, int vert, int bleu);

	// Getters
	string getText() {
		return text;
	}
};