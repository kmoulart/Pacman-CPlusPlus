// ViewJeu.cpp
#include "ViewJeu.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
ViewJeu *ViewJeu::instance = 0;

/*
 * Constructeur du ViewJeu
 */
ViewJeu::ViewJeu()
{
	map = Map::getInstance();
	laby = Labyrinthe::getInstance();
	pacman = Pacman::getInstance();
	leftSideLaby = -1;
	bottomSideLaby = -1;
	loadLaby();
	glClearColor(0,0,0,0);
	computeViewPort();
}

/*
 * Renvoi l'unique instance du ViewJeu (Singleton)
 * @return ViewJeu *
 */
ViewJeu *ViewJeu::getInstance()
{
	if (ViewJeu::instance == 0 )
		instance = new ViewJeu();

	return instance;
}

/*
 * Initialise la viewport de ViewInfos
 * @return void
 */
void ViewJeu::viewport()
{
	glViewport(xViewport, yViewport, wvp, hvp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(leftSideLaby, rightSideLaby, bottomSideLaby, topSideLaby);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Calcul les dimensions de la viewport et de la gluOrtho2D
 * @return void
 */
void ViewJeu::computeViewPort() {
	float w = 3 * View::getInstance()->getWGlobal() / 4.0;
	float h = View::getInstance()->getHGlobal();
	// Le laby ne prend que 3/4 de la largeur de la fenêtre, le quart restant etant réservé pour les infos de jeu
	// Il prend par contre toute la hauteur disponible
	float hLaby = map->getNbrLignes() + 1;
	float wLaby = map->getNbrColonnes() + 1;
	// Dimensions dans l'espace de travail du labyrinthe
	// Les + 1 servent a avoir une marge extérieure de 1/2 case de large tout autour du laby
	hvp = h;
	wvp = (hvp * wLaby) / hLaby;
	// Dimensions de la viewport
	// De telle sorte que le rapport wvp / hvp = wLaby / hLaby
	
	if (w / h <= wLaby / hLaby) {
	// Si le labyrinthe a une proportion différente de la viewport (rapport largeur/hauteur différent)
	// on change la dimension qui prendra toute la place dans la viewport : par défaut c'est la hauteur
	// mais on prend donc la largeur ici
		wvp = w;
		hvp = (wvp * hLaby) / wLaby;
	}
	// on divise donc par 2 la largeur (resp la hauteur) restante afin de centrer la viewport sur la fenetre
	xViewport = (w - wvp) / 2;
	yViewport = (h - hvp) / 2;
}

/*
 * Dessine le labyrinthe
 * @return void
 */
void ViewJeu::dessineLaby() {
	glPushMatrix();
	glTranslated(0, map->getNbrLignes() - 1, 0);
	laby->dessine();
	glPopMatrix();
}

/*
 * Dessine pacman
 * @return void
 */
void ViewJeu::dessinePacMan()
{
	pacman->dessine();
}

/*
 * Dessine les fantômes
 * @return void
 */
void ViewJeu::dessineFantomes() {
	Fantome *f = map->getFantomes();
	for (int i = 0; i < map->getNbFantomes(); i++) {
		if (pacman->isSuper())
			f->tuable(0, 1, 0, true);
		else
			f->tuable(1, 1, 1, false);
		f->dessine();
	}
}

/*
 * Récupère le nom du fichier du niveau
 * @return string
 */
string ViewJeu::getFileName() {
	ostringstream lect;
	lect << Model::getInstance()->getNiveau();
	return "laby_" + lect.str() + EXTENSION;
}

/*
 * Charge le labyrinthe à partir du fichier dans les sources
 * @return void
 */
void ViewJeu::loadLaby() {
	string nomFichier = getFileName();
	ifstream fichierLaby(nomFichier);
	// ouverture du fichier donné
	if (fichierLaby.is_open())
	{
		// si le fichier s'est bien ouvert
		fichierLaby >> *laby;
		fichierLaby.close();
		rightSideLaby = map->getNbrColonnes();
		topSideLaby = map->getNbrLignes();
		computeViewPort();
	}
	else
	{
		std::exit(0);
	}
}

/*
 * Raffiche la vue
 * @return void
 */
void ViewJeu::display(void)
{
	viewport();
	dessineLaby();
	dessineFantomes();
	dessinePacMan();
}

/*
 * Redimensionne la vue
 * @return void
 */
void ViewJeu::reshape()
{
	computeViewPort();
}

/*
 * Redessine les différentes vues
 * @return void
 */
void ViewJeu::redraw()
{
	glutPostRedisplay();
}