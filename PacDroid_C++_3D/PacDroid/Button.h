// Button.h
#pragma once

#include "TextView.h"
#include "Couleur.h"
#include "Coordonnee.h"
#include <string>
#include <memory>

class Button
{
private:
	// Texte du bouton
	shared_ptr<TextView> text;
	// Positions des bords du bouton
	float leftSide, rightSide, bottomSide, topSide;
	// Couleur du bord du bouton (background)
	Couleur bCouleur;
	// Couleur du centre du bouton (foreground)
	Couleur fCouleur;
	// Définit si le bouton est à l'état pressé ou non
	bool pressed;
	
	void change();
	void setCouleurText(Couleur couleur);
	void setBackground(Couleur couleur);
	void setForeground(Couleur couleur);

public:
	// Constructeurs et destructeur
	Button();
	Button(string s);
	~Button();

	// Actions sur le bouton
	bool click(const Coordonnee &cClick);
	void press();
	void release();
	void placer(const Coordonnee &cPlacement);

	// Setters
	void setText(string text);

	// Getters
	TextView *getText() {
		return text.get();
	}
};