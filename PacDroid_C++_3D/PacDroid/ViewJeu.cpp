// ViewJeu.cpp

#include "ViewJeu.h"
#include "View.h"

/**
 * Constructeur du ViewJeu
 */
ViewJeu::ViewJeu() {
	map = MapView::getInstance();
	leftSideLaby = -1;
	bottomSideLaby = -1;
	glClearColor(0,0,0,0);
}

/**
 * Calcul les dimensions de la viewport
 * @return void
 */
void ViewJeu::computeViewPort() {
	float w = 3 * View::getInstance()->getWGlobal() / 4.0;
	float h = View::getInstance()->getHGlobal();
	// Le laby ne prend que 3/4 de la largeur de la fen�tre, le quart restant etant r�serv� pour les infos de jeu
	// Il prend par contre toute la hauteur disponible
	float hLaby = map->getNbrLignes() + 1;
	float wLaby = map->getNbrColonnes() + 1;
	// Dimensions dans l'espace de travail du labyrinthe
	// Les + 1 servent a avoir une marge ext�rieure de 1/2 case de large tout autour du laby
	hvp = h;
	wvp = (hvp * wLaby) / hLaby;
	// Dimensions de la viewport
	// De telle sorte que le rapport wvp / hvp = wLaby / hLaby
	
	if (w / h <= wLaby / hLaby) {
	// Si le labyrinthe a une proportion diff�rente de la viewport (rapport largeur/hauteur diff�rent)
	// on change la dimension qui prendra toute la place dans la viewport : par d�faut c'est la hauteur
	// mais on prend donc la largeur ici
		wvp = w;
		hvp = (wvp * hLaby) / wLaby;
	}
	// on divise donc par 2 la largeur (resp la hauteur) restante afin de centrer la viewport sur la fenetre
	coordViewport.setX((w - wvp) / 2);
	coordViewport.setY((h - hvp) / 2);
}

/**
 * R�cup�re le nom du fichier du niveau
 * @return string
 */
string ViewJeu::getFileName() {
	ostringstream lect;
	lect << Model::getInstance()->getNiveau();
	return "laby_" + lect.str() + EXTENSION;
}

/**
 * Charge le labyrinthe � partir du fichier dans les sources
 * @return void
 */
void ViewJeu::loadLaby() {
	string nomFichier = getFileName();
	ifstream fichierLaby(nomFichier);
	// ouverture du fichier donn�
	if (fichierLaby.is_open()) {
		// si le fichier s'est bien ouvert
		fichierLaby >> *map;
		fichierLaby.close();
		rightSideLaby = map->getNbrColonnes();
		topSideLaby = map->getNbrLignes();
		computeViewPort();
	} else {
		std::exit(0);
	}
}

/**
 * Zoom sur la sc�ne de jeu
 * @return void
 */
void ViewJeu::zoomer() {
	//r�impl�ment� par la classe concr�te si besoin, par d�faut => ne fait rien
}

/**
 * D�zoom sur la sc�ne de jeu
 * @return void
 */
void ViewJeu::dezoomer() {
	//r�impl�ment� par la classe concr�te si besoin, par d�faut => ne fait rien
}

/**
 * Redimensionne la vue
 * @return void
 */
void ViewJeu::reshape() {
	computeViewPort();
}

/**
 * Redessine les diff�rentes vues
 * @return void
 */
void ViewJeu::redraw() {
	glutPostRedisplay();
}