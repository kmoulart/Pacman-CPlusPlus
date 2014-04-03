// Camera.cpp

#include "Camera.h"
#include "MyGlut.h"

using namespace glut;

// Les membres static non constants doient êtres initialisés dans le .cpp
Camera *Camera::instance = 0;

/**
 * Constructeur vide de la Camera
 */
Camera::Camera() {
}

/**
 * Renvoi l'unique instance de la caméra (Application du pattern singleton)
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
 * Modifie la coordonnée "eye" de la caméra
 * @param c Nouvelle coordonnée des "eye" de la caméra
 * @return void
 */
void Camera::setEye(Coordonnee &c) {
	this->eye = Coordonnee(c);
}

/**
 * Modifie la coordonnée "center" de la caméra
 * @param c Nouvelle coordonnée des "center" de la caméra
 * @return void
 */
void Camera::setCenter(Coordonnee &c) {
	this->center = Coordonnee(c);
}

/**
 * Modifie la coordonnée "up" de la caméra
 * @param c Nouvelle coordonnée des "up" de la caméra
 * @return void
 */
void Camera::setUp(Coordonnee &c) {
	this->up = Coordonnee(c);
}
