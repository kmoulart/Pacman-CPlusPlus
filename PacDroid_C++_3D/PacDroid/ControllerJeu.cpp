// ControllerJeu.cpp

#include "ControllerJeu.h"
#include "FantomeView.h"
#include "PacmanView.h"
#include "MapView.h"
#include "View.h"
#include "Camera.h"
#include "Coordonnee.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
ControllerJeu *ControllerJeu::instance = 0;

/**
 * Fonctions C associée à l'animation de la bouche de pacman via un timer
 * @param val Inutilisé, mais imposé par l'usage des timers
 * @return void
 */
void animateDisplayCallBack(int val) {
	ControllerJeu::getInstance()->animateDisplay();
}

/**
 * Fonctions C associée à la gestion de la position de pacman selon la direction voulue
 * et des fantomes
 * @param val Inutilisé, mais imposé par l'usage des timers
 * @return void
 */
void updatePosition(int val) {
	if (!Model::getInstance()->isPaused()) {
		PacmanView * pacman = PacmanView::getInstance();
		Map *map = MapView::getInstance();
		bool touche = false;

		// Update les positions des entitees mobiles
		pacman->updatePosition();
		for (int i = 0; i < map->getNbFantomes(); i++) {
			touche = map->verifierFantome(i);
			map->getFantomes()[i].updatePosition();
			// 2 verifications sont necessaires car le pacman est d'abord bougé,
			// pouvant entrer en collision avec un fantome, puis le fantome,
			// pouvant entrer en collision avec le pacman
			if (!touche) map->verifierFantome(i);
		}

		// Verification sur les pastilles
		if (map->verifierPastilles()) {
			// si il n'y a plus de pastilles
			View::getInstance()->getView()->loadLaby();
			View::getInstance()->reshape();
		} else {
			pacman->decrementSuperPac();
			for (int i = 0; i < map->getNbFantomes(); i++) {
				map->getFantomes()[i].tuable(pacman->isSpecial());
			}
		}
	}
	View::getInstance()->redraw(); // Rafraichissement de l'affichage
	glutTimerFunc(5, updatePosition, 0); // Signal a glut d'appeler update dans 5 ms
}

/**
 * Constructeur de ControllerJeu
 */
ControllerJeu::ControllerJeu() 
{
	model = Model::getInstance();
	map = MapView::getInstance();
	viewJeu = View::getInstance()->getView();
	pacman = PacmanView::getInstance();
	pivot = glGenLists(1);
	glutTimerFunc(TEMPS_BASE_BOUCHE,animateDisplayCallBack,1); // Lance le "controleur" de l'animation
	glutTimerFunc(0, updatePosition, 0); // Signal a glut d'appeler update directement
}

/**
 * Renvoi l'unique instance du ControllerJeu (Application du pattern singleton)
 * @return ControllerJeu* Pointeur vers l'instance unique de la classe
 */
ControllerJeu *ControllerJeu::getInstance()
{
	if (instance == 0)
		instance = new ControllerJeu();
	return instance;
}

/**
 * Gestion du clavier étendu
 * @param key Code de la touche enfoncée
 * @param cMouse Coordonnées de la souris lors de l'évènement
 * @return void
 */
void ControllerJeu::keyPressed(int key, const Coordonnee &cMouse)
{
	if (!model->gameOver()) {
		// Actions ne pouvant être exécutées que si le pacman a encore des vies
		PacmanView *pacman = PacmanView::getInstance();
		switch(key) {
		case GLUT_KEY_DOWN:
			model->setStatus(START);
			pacman->setDirectionVoulue(map->isFirstPerson() ? ((BAS + pacman->getDirection()) % 360) : BAS);
			break;
		case GLUT_KEY_UP:
			model->setStatus(START);
			pacman->setDirectionVoulue(map->isFirstPerson() ? ((HAUT + pacman->getDirection()) % 360) : HAUT);
			break;
		case GLUT_KEY_RIGHT:
			model->setStatus(START);
			pacman->setDirectionVoulue(map->isFirstPerson() ? ((DROITE + pacman->getDirection()) % 360) : DROITE);
			break;
		case GLUT_KEY_LEFT:
			model->setStatus(START);
			pacman->setDirectionVoulue(map->isFirstPerson() ? ((GAUCHE + pacman->getDirection()) % 360) : GAUCHE);
			break;
		// Utile pour débugging ou cheat.
		//case 'u':
		//	model->levelUp();
		//	viewJeu->loadLaby();
		//	View::getInstance()->reshape();
		//	break;
		case 'r':
			model->resetLevel();
			break;
		case ' ':
			model->pauseUnpause();
		default:
			break;
		}
		View::getInstance()->redraw(); // Rafraichissement de l'affichage
	}
	// Actions pouvant être exécutées n'importe quand.
	switch(key) {
	// Utiles pour debugging ou cheat.
	//case 'l':
	//	model->incrementNbrVies();
	//	break;
	//case 'm':
	//	model->decrementNbrVies();
	//	break;
	case 'n':
		model->firstLevel();
		viewJeu->loadLaby();
		View::getInstance()->reshape();
		break;
	case 'b':
		std::exit(0);
		break;
	}
}

/**
 * Gestion de la souris sur le jeu
 * @param button Code du bouton qui a été cliqué
 * @param state Etat du bouton cliqué : enfoncé ou relâché
 * @param c Coordonnées de la souris sur la fenêtre lors du clique
 * @return void
 */
void ControllerJeu::picking(int button, int state, const Coordonnee &c) {
	if(button != GLUT_LEFT_BUTTON || state == GLUT_UP)
		return;
	GLint nbTouches, viewport[4];
	Map *map = MapView::getInstance();

	// recupère les paramètres de la viewport du labyrinthe
	viewport[0] = View::getInstance()->getView()->getXViewport();
	viewport[1] = View::getInstance()->getView()->getYViewport();
	viewport[2] = View::getInstance()->getView()->getWvp();
	viewport[3] = View::getInstance()->getView()->getHvp();

	// création du tableau d'entier non signé pour le buffer de selection
	GLuint bufferSelection[TAILLE_SELECTION];
	glSelectBuffer(TAILLE_SELECTION, bufferSelection);

	(void) glRenderMode(GL_SELECT); // passage en mode de selection

	glInitNames(); // initialise la pile pour les noms
	glPushName(0); // place un nom dans la pile des noms

	glPushMatrix();
		// Mode de Projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPickMatrix((GLdouble) c.getX(), (GLdouble) (View::getInstance()->getHGlobal() - c.getY()), 20.0, 20.0, viewport);
		// Recupère le type de projection dynamiquement
		View::getInstance()->getView()->projection();

		// Mode de Model View
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// Récupère le gluLookAt à l'identique de la vue 3D via Camera
		Camera::getInstance()->placer();
	
		// Charge chaque forme selectionnable
		glLoadName(1); // remplace le nom en haut de la liste
		// Affichage et translation de l'objet au centre de la map
		glPushMatrix();
			glTranslated(MapView::getInstance()->getNbrColonnes()/2.0 - 0.5, MapView::getInstance()->getNbrLignes()/2.0 - 0.5, 0);
			glPushMatrix();
				GLUquadricObj *forme = gluNewQuadric();
				gluQuadricDrawStyle(forme, GLU_FILL);
				gluSphere(forme, 1.0, 36, 36);
				gluDeleteQuadric(forme);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glFlush(); // force l'execution de toutes les instructions précédentes
	nbTouches = glRenderMode(GL_RENDER); // retour en mode de rendu
	if (nbTouches == 1) { // 1 élément séléctionné
		map->setRotation(map->isRotation() ? false : true);// Effectuer une rotation
		glutPostRedisplay(); // redessine
	}
}

/**
 * Anime la bouche de pacman sur base d'un timer
 * @return void
 */
void ControllerJeu::animateDisplay() {
	if (!model->isPaused()) {
		pacman->anime();
		View::getInstance()->redraw();
	}
	glutTimerFunc(TEMPS_BASE_BOUCHE,animateDisplayCallBack,1);
}