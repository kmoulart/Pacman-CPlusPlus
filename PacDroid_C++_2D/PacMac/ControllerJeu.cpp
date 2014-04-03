//ControllerJeu.cpp
#include "ControllerJeu.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
ControllerJeu *ControllerJeu::instance = 0;

/*
 * Fonctions C associée à l'animation de la bouche de pacman (timer)
 * @param int val (imposé par l'usage des timers)
 * @return void
 */
void animateDisplayCallBack(int val)
{
	ControllerJeu::getInstance()->animateDisplay();
}

/*
 * Fonctions C associée à la gestion de la position de pacman selon la direction voulue
 * et des fantomes
 * @param int value (imposé par l'usage des timers)
 * @return void
 */
void updatePosition(int value) {
	if (!Model::getInstance()->isPaused()) {
		Pacman * pacman = Pacman::getInstance();
		Map *map = Map::getInstance();
		bool touche = false;
		pacman->updatePosition();
		// Verification sur les fantomes
		touche = map->verifierFantomes();
		// vérification des fantomes une première fois AVANT le mouvement de ceux-ci
		for (int i = 0; i < map->getNbFantomes(); i++) {
			map->getFantomes()[i].updatePosition();
		}
		if (!touche)
			// Verification sur les fantomes une seconde fois APRES le mouvement de ceux-ci
			// SI le pacman n'a pas déja été touché
			map->verifierFantomes();

		// Verification sur les pastilles
		if (map->verifierPastilles()) {
			// si il n'y a plus de pastilles
			ViewJeu::getInstance()->loadLaby();
			View::getInstance()->reshape();
		} else {
			pacman->decrementSuperPac();
		}
	}
	View::getInstance()->redraw(); // Rafraichissement de l'affichage
	glutTimerFunc(5, updatePosition, 0); // Signal a glut d'appeler update dans 25 ms
}

/*
 * Constructeur de ControllerJeu
 */
ControllerJeu::ControllerJeu() 
{
	model = Model::getInstance();
	viewJeu = ViewJeu::getInstance();
	pacman = Pacman::getInstance();
	glutTimerFunc(TEMPS_BASE_BOUCHE,animateDisplayCallBack,true); // Lance le "controleur" de l'animation
	glutTimerFunc(0, updatePosition, 0); // Signal a glut d'appeler update dans 25 ms
}

/*
 * Renvoi l'unique instance du ControllerJeu (Singleton)
 * @return ControllerJeu *
 */
ControllerJeu *ControllerJeu::getInstance()
{
	if (instance == 0)
		instance = new ControllerJeu();
	return instance;
}

/*
 * Gestion du clavier étendu
 * @param int key
 * @param sint x
 * @param sint y
 * @return void
 */
void ControllerJeu::keyPressed(int key, int x, int y)
{
	if (!model->gameOver()) {
		switch(key) {
		case GLUT_KEY_DOWN:
			model->setStatus(START);
			pacman->setDirectionVoulue(BAS);
			break;
		case GLUT_KEY_UP:
			model->setStatus(START);
			pacman->setDirectionVoulue(HAUT);
			break;
		case GLUT_KEY_RIGHT:
			model->setStatus(START);
			pacman->setDirectionVoulue(DROITE);
			break;
		case GLUT_KEY_LEFT:
			model->setStatus(START);
			pacman->setDirectionVoulue(GAUCHE);
			break;
		case 'u':
			model->levelUp();
			ViewJeu::getInstance()->loadLaby();
			View::getInstance()->reshape();
			break;
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
	switch(key) {
	case 'l':
		model->incrementNbrVies();
		break;
	case 'm':
		model->decrementNbrVies();
		break;
	case 'n':
		model->firstLevel();
		ViewJeu::getInstance()->loadLaby();
		View::getInstance()->reshape();
		break;
	case 'b':
		std::exit(0);
	}
}

/*
 * Anime la bouche de pacman
 * @return void
 */
void ControllerJeu::animateDisplay() {
	if (!model->isPaused()) {
		pacman->anime();
		View::getInstance()->redraw();
	}
	glutTimerFunc(TEMPS_BASE_BOUCHE,animateDisplayCallBack,true);
}