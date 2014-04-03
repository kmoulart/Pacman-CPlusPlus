// Camera.cpp

#include "Camera.h"
#include "MyGlut.h"

using namespace glut;

// Les membres static non constants doient �tres initialis�s dans le .cpp
Camera *Camera::instance = 0;

/**
 * Constructeur vide de la Camera
 */
Camera::Camera() {
}

/**
 * Renvoi l'unique instance de la cam�ra (Application du pattern singleton)
 * @return Camera* Pointeur vers l'instance unique de la classe
 */
Camera *Camera::getInstance(){
	if (instance == 0)
		instance = new Camera();
	return instance;
}

/**
 * Place la camera
 * @return void
 */
void Camera::placer() {
	gluLookAt(this->eye.getX(), this->eye.getY(), this->eye.getZ(), 
				this->center.getX(), this->center.getY(), this->center.getZ(), 
				this->up.getX(), this->up.getY(), this->up.getZ());
}

/**
 * Modifie la coordonn�e "eye" de la cam�ra
 * @param c Nouvelle coordonn�e des "eye" de la cam�ra
 * @return void
 */
void Camera::setEye(Coordonnee &c) {
	this->eye = Coordonnee(c);
}

/**
 * Modifie la coordonn�e "center" de la cam�ra
 * @param c Nouvelle coordonn�e des "center" de la cam�ra
 * @return void
 */
void Camera::setCenter(Coordonnee &c) {
	this->center = Coordonnee(c);
}

/**
 * Modifie la coordonn�e "up" de la cam�ra
 * @param c Nouvelle coordonn�e des "up" de la cam�ra
 * @return void
 */
void Camera::setUp(Coordonnee &c) {
	this->up = Coordonnee(c);
}
