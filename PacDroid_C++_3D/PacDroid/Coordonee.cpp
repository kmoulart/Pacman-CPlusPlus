// Coordonnee.cpp

#include "Coordonnee.h"
#include "Utils.h"
#include <cmath>

/**
 * Constructeur par defaut
 */
Coordonnee::Coordonnee() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

/**
 * Constructeur de Coordonnee
 * @param x Position en x de la coordonnée
 * @param y Position en y de la coordonnée
 */
Coordonnee::Coordonnee(float x, float y) {
	this->x = x;
	this->y = y;
	this->z = 0;
}

/**
 * Constructeur de Coordonnee
 * @param x Position en x de la coordonnée
 * @param y Position en y de la coordonnée
 * @param z Position en z de la coordonnée
 */
Coordonnee::Coordonnee(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

/**
 * Test si les coordonnees sont identiques avec une autre coordonnee
 * @param c Coordonnée à tester
 * @return bool Vrai ou faux si la coordonnée est identique à celle donnée
 */
bool Coordonnee::equals(const Coordonnee &c) const {
	return c.x == this->x && c.y == this->y && c.z == this->z;
}

/**
 * Calcule la distance euclidienne entre deux coordonnees
 * @param c1 Première coordonnée
 * @param c2 Deuxième coordonnée
 * @return float Distance entre les deux coordonnées
 */
float Coordonnee::computeDistance(Coordonnee c1, Coordonnee c2) {
	return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}

/**
 * Vérifie si les coordonnées données sont entières
 * @param c Coordonnée à tester
 * @return bool Vrai ou faux si la coordonnée est entière
 */
bool Coordonnee::estEntiere(Coordonnee c) {
	return (
		c.getY() == Utils::round(c.getY()) && 
		c.getX() == Utils::round(c.getX()));
}

/**
 * Modifie la coordonnee
 * @param coord Nouvelle coordonnée
 * @return void
 */
void Coordonnee::setCoord(Coordonnee coord) {
	this->setX(coord.x);
	this->setY(coord.y);
	this->setZ(coord.z);
}

/**
 * Modifie la coordonnee en X
 * @param newX Nouvelle position en x
 * @return void
 */
void Coordonnee::setX(float newX) {
	this->x = Utils::floor2Decimal(newX);
}

/**
 * Modifie la coordonnee en Y
 * @param newY Nouvelle position en y
 * @return void
 */
void Coordonnee::setY(float newY) {
	this->y = Utils::floor2Decimal(newY);
}

/**
 * Modifie la coordonnee en Z
 * @param newz Nouvelle position en z
 * @return void
 */
void Coordonnee::setZ(float newZ) {
	this->z = Utils::floor2Decimal(newZ);
}