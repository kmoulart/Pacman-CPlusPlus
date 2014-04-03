//Main.cpp

#include "View.h"
#include "ControllerJeu.h"
#include "ControllerButton.h"
#include "Constantes.h"
#include "Coordonnee.h"

/**
 * Fonctions C appellée chaque fois que la vue est redessinée
 * @return void
 */
void displayCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	View::getInstance()->display();
	glutSwapBuffers();
}

/**
 * Fonctions C appellée chaque fois que l'utilisateur redimensionne la fenêtre
 * @param width Nouvelle largeur de la fenêtre
 * @param height Nouvelle hauteur de la fenêtre
 * @return void
 */
void reshapeCallBack(int width, int height)
{
	View::getInstance()->reshape(width, height);
}

/*
 * Fonctions C appellée chaque fois que l'utilisateur sollicite la souris
 * @param button Code du bouton qui a été cliqué
 * @param state Etat du bouton cliqué : enfoncé ou relâché
 * @param x Position en x de la souris sur la fenêtre lors du clique
 * @param y Position en y de la souris sur la fenêtre lors du clique
 * @return void
 */
void mouseCallBack(int button, int state, int x, int y) {
	Coordonnee c(x, y);
	ControllerButton::getInstance()->mouse(button, state, c);
	ControllerJeu::getInstance()->picking(button, state, c);
}

/*
 * Fonctions C appellée chaque fois que l'utilisateur appuie sur une touche spéciale du clavier
 * @param key Code de la touche enfoncée
 * @param x Position en x de la souris sur la fenêtre lors de l'évènement
 * @param y Position en y de la souris sur la fenêtre lors du l'évènement
 * @return void
 */
void specialCallBack(int key, int x, int y) {
	Coordonnee c(x, y);
	ControllerJeu::getInstance()->keyPressed(key, c);
}

/*
 * Fonctions C appellée chaque fois que l'utilisateur appuie sur une touche du clavier
 * @param key Code de la touche enfoncée
 * @param x Position en x de la souris sur la fenêtre lors de l'évènement
 * @param y Position en y de la souris sur la fenêtre lors du l'évènement
 * @return void
 */
void keyboardCallBack(unsigned char key, int x, int y) {
	Coordonnee c(x, y);
	ControllerJeu::getInstance()->keyPressed(key, c);
}

/**
 * Fonction principale, point d'entrée du programme.
 * @param argc
 * @param argv
 * @return int Statut de l'application
 */
int main(int argc, char** argv)
{
	// Intialisation de glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Initialise les modes liés à l'affichage
	glutInitWindowSize(LARGEUR_FENETRE_INIT,HAUTEUR_FENETER_INIT); // Définit la taille de la fenêtre d'écran
	glutInitWindowPosition(100, 100); // Définit la position de la fenêtre d'écran
	glutCreateWindow(NOM_APPLICATION); // Crée la fenêtre d'écran avec le nom passé en argument
	
	// Chaque call back glut est délégué à une méthode de la classe View ou Controller
	// Ceci est nécessaire car glut ne connait que les fonctions C.
	glutDisplayFunc(displayCallBack);
	glutReshapeFunc(reshapeCallBack);
	glutMouseFunc(mouseCallBack);
	glutSpecialFunc(specialCallBack);
	glutKeyboardFunc(keyboardCallBack);

	// Démarre une boucle éternelle d'écoute des call back
	glutMainLoop();

   return 0;
}