// Couleur.h
#pragma once

class Couleur {
private:
	float rouge;
	float vert;
	float bleu;
	float alpha;
public:
	// Constructeurs
	Couleur();
	Couleur(float rouge, float vert, float bleu);
	Couleur(float rouge, float vert, float bleu, float alpha);

	// Modifie la couleur
	void modifier(Couleur couleur);

	// Getters
	float getRouge() {
		return rouge;
	}
	float getVert() {
		return vert;
	}
	float getBleu() {
		return bleu;
	}
};