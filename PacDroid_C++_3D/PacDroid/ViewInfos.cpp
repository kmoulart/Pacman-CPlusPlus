// ViewInfos.cpp

#include "ViewInfos.h"
#include "View.h"
#include "DisplayListPool.h"
#include "TextView.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
ViewInfos *ViewInfos::instance = 0;

/**
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

/**
 * Renvoi l'unique instance du ViewInfos (Application du pattern singleton)
 * @return ViewInfos* Pointeur vers l'instance unique de la classe
 */
ViewInfos *ViewInfos::getInstance() {
	if (ViewInfos::instance == 0 )
		instance = new ViewInfos();

	return instance;
}

/**
 * Initialise la viewport de ViewInfos
 * @return void
 */
void ViewInfos::viewport() {
	glViewport(coordViewport.getX(), coordViewport.getY(), wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftSideInfos, rightSideInfos, bottomSideInfos, topSideInfos);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Calcul les dimensions de la viewport et de la gluOrtho2D
 * @return void
 */
void ViewInfos::computeViewPort() {
	ViewJeu *viewJeu = View::getInstance()->getView();
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
	coordViewport.setX(viewJeu->getXViewport() + viewJeu->getWvp() + (w - wvp) / 2);
	coordViewport.setY(viewJeu->getYViewport() + viewJeu->getHvp() - hvp);
}

/**
 * Dessine une vie en pause ou non selon l'état du jeu
 * @return void
 */
void ViewInfos::dessineVie() {
	if (model->isPaused()) {
		glColor3f(0, 0, 1);
	}
	else {
		glColor3f(1, 1, 0);
	}
	glCallList(DisplayListPool::getInstance()->getList(VIE_PACMAN));
}

/**
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

/**
 * Affiche le score du joueur
 * @return void
 */
void ViewInfos::afficheScore() {
	Coordonnee c(1.25, -1.25);
	int niveau = model->getNiveau();
	stringstream s;
	s << niveau;
	TextView tvTitre = TextView("Niveau :");
	tvTitre.placer(c);
	TextView tvNiveau = TextView(s.str());
	c.setY(c.getY() - 1.25);
	tvNiveau.placer(c);
}

/**
 * Affiche le niveau du joueur
 * @return void
 */
void ViewInfos::afficheNiveau() {
	Coordonnee c(1.25, -1.25);
	int score = model->getScore();
	stringstream s;
	s << score;
	TextView tvTitre = TextView("Score :");
	tvTitre.placer(c);
	TextView tvScore = TextView(s.str());
	c.setY(c.getY() - 1.25);
	tvScore.placer(c);
}

/**
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

/**
 * Raffiche la vue
 * @return void
 */
void ViewInfos::display() {
	viewport();
	afficheInfos();
}

/**
 * Redimensionne la vue
 * @return void
 */
void ViewInfos::reshape() {
	computeViewPort();
}

/**
 * Redessine les différentes vues
 * @return void
 */
void ViewInfos::redraw() {
	glutPostRedisplay();
}

/**
 * Initialise la display liste des vies de pacman
 * @return void
 */
void ViewInfos::initDisplayList() {
	glNewList(DisplayListPool::getInstance()->getList(VIE_PACMAN), GL_COMPILE);
		glRotatef(-90, 0.0, 0.0, 1.0);
		GLUquadricObj *vie;
		vie = gluNewQuadric();
		gluQuadricDrawStyle(vie, GLU_FILL);
		gluPartialDisk(vie, 0.0, 1.0, 36, 1, 30, 300);
		gluDeleteQuadric(vie);
	glEndList();
}