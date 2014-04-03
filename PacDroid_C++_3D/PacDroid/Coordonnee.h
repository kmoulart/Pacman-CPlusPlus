// Coordonnee.h
#pragma once

class Coordonnee
{
private:
	float x, y, z;

public:
	// Constructeurs
	Coordonnee(float x, float y, float z);
	Coordonnee(float x, float y);
	Coordonnee();

	// Methodes de classe
	bool equals(const Coordonnee &c) const;
	static float computeDistance(Coordonnee c1, Coordonnee c2);
	static bool estEntiere(Coordonnee c);

	// Setters
	void setCoord(Coordonnee coord);
	void setX(float newX);
	void setY(float newY);
	void setZ(float newZ);

	// Getters
	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	float getZ() const {
		return z;
	}
};
