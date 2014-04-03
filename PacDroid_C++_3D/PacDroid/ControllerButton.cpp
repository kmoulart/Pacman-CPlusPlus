//ControllerButton.cpp

#include "ControllerButton.h"
#include "ViewJeu2D.h"
#include "ViewJeu3DParalleles.h"
#include "ViewJeu3DPerspective.h"
#include "View.h"
#include "Coordonnee.h"

// Les membres static non constants doivent êtres initialisés dans le .cpp
ControllerButton *ControllerButton::instance=0;

/**
 * Constructeur du controleur des boutons
 */
ControllerButton::ControllerButton() 
{
	model = Model::getInstance();
	pacman = PacmanView::getInstance();
	wController = 14;
	hController = 18;
	rightSideController = -1;
	leftSideController = rightSideController - wController;
	topSideController = -1;
	bottomSideController = topSideController - hController;
	computeViewPort();

	// Initialisation des boutons
	tabButton = new Button[NB_BOUTON];
	Button *b = tabButton;
	b->setText("HAUT");
	b++;
	b->setText("BAS");
	b++;
	b->setText("DROITE");
	b++;
	b->setText("GAUCHE");
	b++;
	b->setText("PARALLELE");
	b++;
	b->setText("2D");
	b++;
	b->setText("FP");
	b++;
	b->setText("+");
	b++;
	b->setText("PERSPECTIVE");
	b++;
	b->setText("DARK");
	b++;
	b->setText("-");
	b++;
	b->setText("START");
	b++;
	b->setText("PAUSE");
	b++;
	b->setText("ROTATE");
	b++;
	b->setText("NOUVELLE PARTIE");
	b++;
	b->setText("RESET");
	b++;
	b->setText("QUITTER");
}

/**
 * Renvoi l'unique instance du ControllerButton (Application du pattern singleton)
 * @return ControllerButton* Pointeur vers l'instance unique de la classe
 */
ControllerButton *ControllerButton::getInstance()
{
	if (instance == 0)
		instance = new ControllerButton();
	return instance;
}

/**
 * Initialise la viewport du ControllerButton
 * @return void
 */
void ControllerButton::viewport() {
	glViewport(coordViewport.getX(), coordViewport.getY(), wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftSideController, rightSideController, bottomSideController, topSideController);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Calcul les dimensions de la viewport et de la gluOrtho2D
 * @return void
 */
void ControllerButton::computeViewPort() {
	ViewJeu *viewJeu = View::getInstance()->getView();
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
	coordViewport.setX(viewJeu->getXViewport() + viewJeu->getWvp() + (w - wvp) / 2);
	coordViewport.setY(viewJeu->getYViewport() + h - hvp);
}

/**
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
		Coordonnee c(rightSideController - wController/2.0 - largeurBouton/2.0, -hController/NB_LIGNE_BOUTON);
		b->placer(c);
		b++;
		// BAS
		int ligne = b->getText()->computeLargeur() + 0.60;
		c.setX(rightSideController - wController/2.0 - ligne/2.0);
		c.setY(-hController/NB_LIGNE_BOUTON * 2);
		b->placer(c);
		b++;
		// DROITE
		largeurBouton = b->getText()->computeLargeur() + 0.60;
		c.setX(-wController / 3.0 + ligne - largeurBouton/2.0 + rightSideController);
		b->placer(c);
		b++;
		// GAUCHE
		largeurBouton = b->getText()->computeLargeur() + 0.60;
		c.setX(-wController * 2 / 3.0 - ligne - largeurBouton/2.0 + rightSideController);
		b->placer(c);
		b++;
		// PARALLELE
		ligne = rightSideController - wController + 0.60;
		c.setX(ligne - 0.60);
		c.setY(-hController/NB_LIGNE_BOUTON * 3);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// 2D
		c.setX(ligne - 0.60);
		b->placer(c);
		ligne += b->getText()->computeLargeur();
		b++;
		// FIRST PERSON
		c.setX(ligne);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// +
		c.setX(ligne + 0.60);
		b->placer(c);
		b++;
		// PERSPECTIVE
		ligne = rightSideController - wController + 0.60;
		c.setX(ligne - 0.60);
		c.setY(-hController/NB_LIGNE_BOUTON * 4);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// DARK MODE
		c.setX(ligne - 0.60);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// -
		c.setX(ligne - 0.60);
		b->placer(c);
		b++;
		// START
		ligne = rightSideController - wController + 0.60;
		c.setX(ligne - 0.60);
		c.setY(-hController/NB_LIGNE_BOUTON * 5);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// PAUSE
		c.setX(ligne - 0.20);
		b->placer(c);
		ligne += b->getText()->computeLargeur() + 0.60;
		b++;
		// ROTATE
		c.setX(ligne - 0.60);
		b->placer(c);
		b++;
		// NOUVELLE PARTIE
		largeurBouton = b->getText()->computeLargeur() + 0.60;
		c.setX(rightSideController - wController/2.0 - largeurBouton/2.0);
		c.setY(-hController/NB_LIGNE_BOUTON * 6);
		b->placer(c);
		b++;
		// RESET
		largeurBouton = b->getText()->computeLargeur() + 0.60;
		c.setX(-wController / 3.0 - largeurBouton/2.0 + rightSideController);
		c.setY(-hController/NB_LIGNE_BOUTON * 7);
		b->placer(c);
		b++;
		// QUITTER
		largeurBouton = b->getText()->computeLargeur() + 0.60;
		c.setX(-wController + largeurBouton/2.0 + rightSideController);
		b->placer(c);
	glPopMatrix();
}

/**
 * Gestion de la souris
 * @param button Code du bouton qui a été cliqué
 * @param state Etat du bouton cliqué : enfoncé ou relâché
 * @param cClick Coordonnées de la souris sur la fenêtre lors du clique
 * @return void
 */
void ControllerButton::mouse(int button, int state, const Coordonnee &cClick) 
{
	if(button != GLUT_LEFT_BUTTON) {
		return;
	}

	// on ne s'en fait pas de savoir si on a cliqué dedans ou non, les coordonnées de dessin et les
	// controles effectués dessus étant suffisants

	Coordonnee coordDansViewport(cClick.getX() - coordViewport.getX(), View::getInstance()->getHGlobal() - cClick.getY() - coordViewport.getY());

	coordDessin.setX(leftSideController + coordDansViewport.getX() * (wController / wvp));
	coordDessin.setY(bottomSideController + coordDansViewport.getY() * (hController / hvp));
	
	for (int i = 0; i < NB_BOUTON; i++) {
		tabButton[i].release();
		if (tabButton[i].click(coordDessin)) {
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
				} else if (button == "PARALLELE") {
					View::getInstance()->changeView(ViewJeu3DParalleles::getInstance());
				} else if (button == "PERSPECTIVE") {
					View::getInstance()->changeView(ViewJeu3DPerspective::getInstance());
				} else if (button == "2D") {
					View::getInstance()->changeView(ViewJeu2D::getInstance());
				} else if (button == "+") {
					View::getInstance()->getView()->zoomer();
				} else if (button == "-") {
					View::getInstance()->getView()->dezoomer();
				} else if (button == "ROTATE") {
					MapView::getInstance()->setRotation(false);
					MapView::getInstance()->setAngle(0);
				} else if (button == "DARK") {
					MapView::getInstance()->setDarkMode(MapView::getInstance()->isDarkMode() ? false : true);
				} else if (button == "FP") {
					View::getInstance()->changeView(ViewJeu3DPerspective::getInstance());
					MapView::getInstance()->setFirstPerson(true);
				} else if (button == "START") {
					model->setStatus(START);
				} else if (button == "PAUSE") {
					model->pauseUnpause();
				} else if (button == "NOUVELLE PARTIE") {
					model->firstLevel();
					View::getInstance()->getView()->loadLaby();
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

/**
 * Affichage de la viewport et ses composants
 * @return void
 */
void ControllerButton::display() {
	viewport();
	afficheButtons();
}

/**
 * Recalcul la viewport
 * @return void
 */
void ControllerButton::reshape() {
	computeViewPort();
}

/**
 * Redessine la viewport
 * @return void
 */
void ControllerButton::redraw() {
	glutPostRedisplay();
}