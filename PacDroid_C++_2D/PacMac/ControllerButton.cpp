//ControllerButton.cpp
#include "ControllerButton.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
ControllerButton *ControllerButton::instance=0;

/*
 * Constructeur du controleur des boutons
 */
ControllerButton::ControllerButton() 
{
	model = Model::getInstance();
	pacman = Pacman::getInstance();
	wController = 14;
	hController = 18;
	rightSideController = -1;
	leftSideController = rightSideController - wController;
	topSideController = -1;
	bottomSideController = topSideController - hController;
	computeViewPort();
	tabButton = new Button[9];
	Button *b = tabButton;
	b->setText("HAUT");
	b++;
	b->setText("BAS");
	b++;
	b->setText("DROITE");
	b++;
	b->setText("GAUCHE");
	b++;
	b->setText("START");
	b++;
	b->setText("PAUSE");
	b++;
	b->setText("NOUVELLE PARTIE");
	b++;
	b->setText("RESET");
	b++;
	b->setText("QUITTER");
}

/*
 * Renvoi l'unique instance du ControllerButton (Singleton)
 * @return ControllerButton *
 */
ControllerButton *ControllerButton::getInstance()
{
	if (instance == 0)
		instance = new ControllerButton();
	return instance;
}

/*
 * Initialise la viewport du ControllerButton
 * @return void
 */
void ControllerButton::viewport() {
	glViewport(xViewport, yViewport, wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftSideController, rightSideController, bottomSideController, topSideController);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Calcul les dimensions de la viewport et de la gluOrtho2D
 * @return void
 */
void ControllerButton::computeViewPort() {
	ViewJeu *viewJeu = ViewJeu::getInstance();
	// Le controlleur prend la place laissée par le labyrinthe à droite, soit 1/3 de sa largeur 
	// et les 3/4 de sa hauteur
	float h = viewJeu->getHvp() / 4.0 * 3.0;
	float w = viewJeu->getWvp() / 3.0;

	hvp = h;
	wvp = (hvp * wController) / hController;
	// Dimensions de la viewport
	// De telle sorte que le rapport wvp / hvp = wLaby / hLaby
	
	if (w / h <= wController / hController) {
	// Si le controlleur a une proportion différente de la viewport (rapport largeur/hauteur différent)
	// on change la dimension qui prendra toute la place dans la viewport : par défaut c'est la hauteur
	// mais on prend donc la largeur
		wvp = w;
		hvp = (wvp * hController) / wController;
	}
	// coordonnées du coin inférieur gauche de la viewport dans la fenetre
	xViewport = viewJeu->getXViewport() + viewJeu->getWvp() + (w - wvp) / 2;
	yViewport = viewJeu->getYViewport() + h - hvp;
}

/*
 * Affichage des boutons
 * @return void
 */
void ControllerButton::afficheButtons() {
	// il est hélas impossible de faire une boucle ici car les boutons sont mis en place différemment selon leur action
	// ex : les boutons directionnels sont placé dans la même disposition que les flèches d'un clavier.
	glPushMatrix();
	Button *b = tabButton;
	// HAUT
	int largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 2.0 - largeurBouton/2.0 + rightSideController, -hController/5.0);
	b++;
	// BAS
	int largeurBoutonBas = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 2.0 - largeurBoutonBas/2.0 + rightSideController, -hController/5.0 * 2);
	b++;
	// DROITE
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 3.0 + largeurBoutonBas - largeurBouton/2.0 + rightSideController, -hController/5.0 *2);
	b++;
	// GAUCHE
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController * 2 / 3.0 - largeurBoutonBas - largeurBouton/2.0 + rightSideController, -hController/5.0 * 2);
	b++;
	// START
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 3.0 - largeurBouton/2.0 + rightSideController, -hController/5.0 * 3);
	b++;
	// PAUSE
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController + largeurBouton/2.0 + rightSideController, -hController/5.0 * 3);
	b++;
	// NOUVELLE PARTIE
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 2.0 - largeurBouton/2.0 + rightSideController, -hController/5.0 * 4);
	b++;
	// RESET
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController / 3.0 - largeurBouton/2.0 + rightSideController, -hController/5.0 * 5);
	b++;
	// QUITTER
	largeurBouton = b->getText()->computeLargeur() + 0.60;
	b->placer(-wController + largeurBouton/2.0 + rightSideController, -hController/5.0 * 5);
	glPopMatrix();
}

/*
 * Gestion de la souris
 * @param int button
 * @param int state
 * @param int x
 * @param int y
 * @return void
 */
void ControllerButton::mouse(int button, int state, int x, int y) 
{
	if(button != GLUT_LEFT_BUTTON) {
		return;
	}

	// Dans ce cas-ci, comme on n'utilise qu'une seule viewport pour detecter des clicks,
	// on ne s'en fait pas de savoir si on a cliqué dedans ou non, les coordonnées de dessin et les
	// controles effectués dessus étant suffisants

	float xDansViewport = x - xViewport;
	float yDansViewport = View::getInstance()->getHGlobal() - yViewport - y;

	x_dessin = leftSideController + xDansViewport * (wController / wvp);
	y_dessin = bottomSideController + yDansViewport * (hController / hvp);
	
	for (int i = 0; i < 9; i++) {
		tabButton[i].release();
		if (tabButton[i].click(x_dessin, y_dessin)) {
			if (state == GLUT_DOWN) {
				string button = tabButton[i].getText()->getText();
				if (button == "HAUT") {
					model->setStatus(START);
					pacman->setDirectionVoulue(HAUT);
				} else if (button == "DROITE") {
					model->setStatus(START);
					pacman->setDirectionVoulue(DROITE);
				} else if (button == "BAS") {
					model->setStatus(START);
					pacman->setDirectionVoulue(BAS);
				} else if (button == "GAUCHE") {
					model->setStatus(START);
					pacman->setDirectionVoulue(GAUCHE);
				} else if (button == "START") {
					model->setStatus(START);
				} else if (button == "PAUSE") {
					model->pauseUnpause();
				} else if (button == "NOUVELLE PARTIE") {
					model->firstLevel();
					ViewJeu::getInstance()->loadLaby();
					View::getInstance()->reshape();
				} else if (button == "RESET") {
					if (!model->gameOver()){
						model->resetLevel();
					}
				} else if (button == "QUITTER") {
					std::exit(0);
				}
				tabButton[i].press();
			}
		}
	}
}

/*
 * Affichage de la viewport et ses composants
 * @return void
 */
void ControllerButton::display() {
	viewport();
	afficheButtons();
}

/*
 * Recalcul la viewport
 * @return void
 */
void ControllerButton::reshape() {
	computeViewPort();
}

/*
 * Redessine la viewport
 * @return void
 */
void ControllerButton::redraw() {
	glutPostRedisplay();
}