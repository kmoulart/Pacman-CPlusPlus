// Button.h
#pragma once

#include "TextView.h"
#include "MyGlut.h"
#include <string>

using namespace std;
using namespace glut;

class Button
{
private:
	TextView *text;
	float leftSide, rightSide, bottomSide, topSide;
	float bRouge, bVert, bBleu;
	float fRouge, fVert, fBleu;
	bool pressed;
	
	void change();
	void setCouleurText(float rouge, float vert, float bleu);
	void setBackground(float rouge, float vert, float bleu);
	void setForeground(float rouge, float vert, float bleu);

public:
	// Con(dé)structeurs
	Button();
	Button(string s);
	~Button();

	// Actions sur le bouton
	bool click(float x,float y);
	void press();
	void release();
	void placer(float x, float y);

	// Setters
	void setText(string text);

	// Getters
	TextView *getText() {
		return text;
	}
};