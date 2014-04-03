// ViewJeu3D.cpp

#include "ViewJeu3D.h"
#include "PacmanView.h"
#include "Constantes.h"

/**
 * Constructeur vide de la vue 3D
 */
ViewJeu3D::ViewJeu3D() : ViewJeu() {
	this->camera = Camera::getInstance();
}

/**
 * Initialise la vue 3D en définissant les lumières, 
 * en activant les tests de profondeur et la normalisation des vecteurs normaux
 * @return void
 */
void ViewJeu3D::init() {
	GLfloat blanc[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat blanc_pale[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat blanc_clair[] = { 0.95, 0.95, 0.95};
	GLfloat rouge[] = { 1, 0, 0, 1.0 };
	GLfloat obscurite[] = { 0.1, 0.2, 0.1, 1.0 };
	GLfloat directionSpot[] = { 0.0, 0.0, -1.0 };

	GLfloat *couleur_0 = blanc_clair;
	GLfloat *couleur_1 = blanc_pale;
	// Change certaines couleurs de lumière si en "Dark Mode"
	if (map->isDarkMode()) {
		// Brouillard
		glEnable(GL_FOG);
		GLfloat fogColor[] = { 0.8f, 0.8f, 0.8f, 1 };
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogi(GL_FOG_START, 0.0f);
		glFogi(GL_FOG_END, 20.0f + map->getNbrLignes());
		// Couleur lumière
		couleur_0 = obscurite;
		couleur_1 = blanc;
	} else {
		glDisable(GL_FOG);
	}
	// Change certaines couleurs de lumière si on est en mode super pacman
	if (PacmanView::getInstance()->isSpecial()) {
		couleur_1 = rouge;
	}

	// Lumière 0 : lumière ambiante blanche
	glLightfv(GL_LIGHT0, GL_AMBIENT, couleur_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, couleur_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, blanc);
	// Lumière 1 : spot directionnel
	glLightfv(GL_LIGHT1, GL_AMBIENT, couleur_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, couleur_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blanc);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, directionSpot);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);

	// Allume les lumières définies
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_LIGHTING); // éclairage permanent
	glEnable(GL_LIGHT0); // lumière 0
	glEnable(GL_LIGHT1); // lumière 1

	// Active la profondeur
	glEnable(GL_DEPTH_TEST);
	// Active la normalisation des vecteurs normaux (qui ont donc tous une norme de 1)
	glEnable(GL_NORMALIZE);
}

/**
 * Initialise la viewport de la vue 3D, ainsi que la camera et les positions des lampes
 * @return void
 */
void ViewJeu3D::viewport() {
	// Récupère les coordonnées de pacman pour le spot et la caméra
	PacmanView *pacman = PacmanView::getInstance();
	float xPacman = pacman->getCoord().getX();
	float yPacman = pacman->getCoord().getY();
	float zPacman = pacman->getCoord().getZ();
	int direction = pacman->getDirection();

	glViewport(coordViewport.getX(), coordViewport.getY(), wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Projection appelle la méthode définissant le type de projection : Parallèle ou Perspective
	projection();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Camera
	Coordonnee eye = Coordonnee(map->getNbrColonnes()/2.0 - 0.5, -3.0, 12.0);
	Coordonnee center = Coordonnee(map->getNbrColonnes()/2.0 - 0.5, map->getNbrLignes(), 0.0);
	Coordonnee up = Coordonnee(0.0, 0.0, 1.0);
	if (map->isFirstPerson()) {
		float xLigneDeVue = 0.0, yLigneDeVue = 0.0, zLigneDeVue = 0.0;
		switch (direction) {
		case GAUCHE:
			xLigneDeVue = xPacman - map->getNbrColonnes();
			yLigneDeVue = yPacman;
			break;
		case DROITE:
			xLigneDeVue = xPacman + map->getNbrColonnes();
			yLigneDeVue = yPacman;
			break;
		case HAUT:
			xLigneDeVue = xPacman;
			yLigneDeVue = yPacman + map->getNbrLignes();
			break;
		case BAS:
			xLigneDeVue = xPacman;
			yLigneDeVue = yPacman - map->getNbrLignes();
			break;
		}
		eye.setCoord(Coordonnee(xPacman, yPacman, zPacman + 1));
		center.setCoord(Coordonnee(xLigneDeVue, yLigneDeVue, zLigneDeVue));
	}
	this->camera->setEye(eye);
	this->camera->setCenter(center);
	this->camera->setUp(up);
	this->camera->placer();

	// positionnement directionnel de la lumière 0
	GLfloat position0[] = { 0.0, -1.0, 3.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	// positionnement positionnel de la lumière 1
	glPushMatrix();
		// Permettre au spot de suivre pacman lors de la rotation
		glTranslated(map->getNbrColonnes()/2.0 - 0.5, map->getNbrLignes()/2.0 - 0.5 - 0.7, 0);
		glRotated(map->getAngle(), 0, 0, 1);
		glTranslated(-map->getNbrColonnes()/2.0 + 0.5, -map->getNbrLignes()/2.0 + 0.5 + 0.7, 0);
		GLfloat position1[] = { xPacman, yPacman - 0.7, zPacman + 1, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glPopMatrix();
}

/**
 * Dessine le labyrinthe
 * @return void
 */
void ViewJeu3D::dessineMap() {
	map->dessine3D();
}

/**
 * Réaffiche la vue
 * @return void
 */
void ViewJeu3D::display() {
	init();
	viewport();
	dessineMap();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glFlush();
}