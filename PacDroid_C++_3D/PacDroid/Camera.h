// Camera.h
#pragma once

#include "Coordonnee.h"

class Camera
{
private:
	Coordonnee eye;
	Coordonnee center;
	Coordonnee up;
	static Camera *instance;

	// Constructeur
	Camera();
public:
	// Singleton
	static Camera *getInstance();

	// Placement
	void placer();

	// Setter
	void setEye(Coordonnee &c);
	void setCenter(Coordonnee &c);
	void setUp(Coordonnee &c);
};
