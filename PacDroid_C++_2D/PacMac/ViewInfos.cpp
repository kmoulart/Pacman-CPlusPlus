// ViewInfos.cpp
#include "ViewInfos.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
ViewInfos *ViewInfos::instance = 0;

/*
 * Constructeur du ViewInfos
 */
ViewInfos::ViewInfos() {
	model = Model::getInstance();
	leftSideInfos = 0;
	rightSideInfos = 15;
	bottomSideInfos = -9;
	topSideInfos = -1;
	computeViewPort();
}

/*
 * Renvoi l'unique instance du ViewInfos (Singleton)
 * @return ViewInfos *
 */
ViewInfos *ViewInfos::getInstance() {
	if (ViewInfos::instance == 0 )
		instance = new ViewInfos();

	return instance;
}

/*
 * Initialise la viewport de ViewInfos
 * @return void
 */
void ViewInfos::viewport() {
	glViewport(xViewport, yViewport, wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftSideInfos, rightSideInfos, bottomSideInfos, topSideInfos);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Calcul les dimensions de la viewport et de la gluOrtho2D
 * @return void
 */
void ViewInfos::computeViewPort() {
	ViewJeu *viewJeu = ViewJeu::getInstance();
	// Les infos prennent la place laissée par le labyrinthe à droite, soit 1/3 de sa largeur 
	// et le quart de sa hauteur (le reste etant pour les boutons du controleur)
	float h = viewJeu->getHvp() / 4.0;
	float w = viewJeu->getWvp() / 3.0;
	float hInfos = topSideInfos - bottomSideInfos;
	float wInfos = rightSideInfos - leftSideInfos;

	hvp = h;
	wvp = (hvp * wInfos) / hInfos;
	// Dimensions de la viewport
	// De telle sorte que le rapport wvp / hvp = wLaby / hLaby
	
	if (w / h <= wInfos / hInfos) {
	// Si les infos ont une proportion différente de la viewport (rapport largeur/hauteur différent)
	// on change la dimension qui prendra toute la place dans la viewport : par défaut c'est la hauteur
	// mais on prend donc la largeur
		wvp = w;
		hvp = (wvp * hInfos) / wInfos;
	}
	// coordonnées du coin inférieur gauche de la viewport dans la fenetre
	xViewport = viewJeu->getXViewport() + viewJeu->getWvp() + (w - wvp) / 2;
	yViewport = viewJeu->getYViewport() + viewJeu->getHvp() - hvp;
}

/*
 * Dessine une vie en pause ou non, morte ou non selon l'état du jeu
 * @return void
 */
void ViewInfos::dessineVie() {
	glRotatef(-90, 0.0, 0.0, 1.0);
	if (model->isPaused()) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(1, 1, 0);
	}
	GLUquadricObj *vie;
	vie = gluNewQuadric();
	gluQuadricDrawStyle(vie, GLU_FILL);
	gluPartialDisk(vie, 0.0, 1.0, 36, 1, 30, 300);
	gluDeleteQuadric(vie);
}

/*
 * Dessine autant de vie que le joueur en a
 * @return void
 */
void ViewInfos::dessineVies() {
	glPushMatrix();
		if (model->gameOver()) {
			glPushMatrix();
				glTranslated(1, -2, 0);
				glScaled(0.5, 0.5, 0);
				dessineVie();
				Pacman::getInstance()->dessineGameOver(0.2, 1.5);
			glPopMatrix();
		}
		else {
			for (int i = 0; i < model->getNbrVies(); i++) {
				glPushMatrix();
					glTranslated(1 + i, -2, 0);
					glScaled(0.5, 0.5, 0);
					dessineVie();
				glPopMatrix();
			}
		}
	glPopMatrix();
}

/*
 * Affiche le score du joueur
 * @return void
 */
void ViewInfos::afficheScore() {
	int niveau = model->getNiveau();
	stringstream s;
	s << niveau;
	TextView tvTitre = TextView("Niveau :");
	tvTitre.placer(1.25, -1.25);
	TextView tvNiveau = TextView(s.str());
	tvNiveau.placer(1.25, -2.5);
}

/*
 * Affiche le niveau du joueur
 * @return void
 */
void ViewInfos::afficheNiveau() {
	int score = model->getScore();
	stringstream s;
	s << score;
	TextView tvTitre = TextView("Score :");
	tvTitre.placer(1.25, -1.25);
	TextView tvScore = TextView(s.str());
	tvScore.placer(1.25, -2.5);
}

/*
 * Affiche le score, le niveau et les vies du joueur
 * @return void
 */
void ViewInfos::afficheInfos() {
	glPushMatrix();
		glTranslated(0, -1.5, 0);
		afficheScore();
		glTranslated(0, -2.5, 0);
		afficheNiveau();
		glTranslated(0.5, -1.5, 0);
		dessineVies();
	glPopMatrix();
}

/*
 * Raffiche la vue
 * @return void
 */
void ViewInfos::display() {
	viewport();
	afficheInfos();
}

/*
 * Redimensionne la vue
 * @return void
 */
void ViewInfos::reshape() {
	computeViewPort();
}

/*
 * Redessine les différentes vues
 * @return void
 */
void ViewInfos::redraw() {
	glutPostRedisplay();
}