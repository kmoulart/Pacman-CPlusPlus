//Main.cpp

#include "View.h"
#include "ControllerJeu.h"
#include "ControllerButton.h"
#include "Constantes.h"
#include "Coordonnee.h"

/**
 * Fonctions C appell�e chaque fois que la vue est redessin�e
 * @return void
 */
void displayCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	View::getInstance()->display();
	glutSwapBuffers();
}

/**
 * Fonctions C appell�e chaque fois que l'utilisateur redimensionne la fen�tre
 * @param width Nouvelle largeur de la fen�tre
 * @param height Nouvelle hauteur de la fen�tre
 * @return void
 */
void reshapeCallBack(int width, int height)
{
	View::getInstance()->reshape(width, height);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur sollicite la souris
 * @param button Code du bouton qui a �t� cliqu�
 * @param state Etat du bouton cliqu� : enfonc� ou rel�ch�
 * @param x Position en x de la souris sur la fen�tre lors du clique
 * @param y Position en y de la souris sur la fen�tre lors du clique
 * @return void
 */
void mouseCallBack(int button, int state, int x, int y) {
	Coordonnee c(x, y);
	ControllerButton::getInstance()->mouse(button, state, c);
	ControllerJeu::getInstance()->picking(button, state, c);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur appuie sur une touche sp�ciale du clavier
 * @param key Code de la touche enfonc�e
 * @param x Position en x de la souris sur la fen�tre lors de l'�v�nement
 * @param y Position en y de la souris sur la fen�tre lors du l'�v�nement
 * @return void
 */
void specialCallBack(int key, int x, int y) {
	Coordonnee c(x, y);
	ControllerJeu::getInstance()->keyPressed(key, c);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur appuie sur une touche du clavier
 * @param key Code de la touche enfonc�e
 * @param x Position en x de la souris sur la fen�tre lors de l'�v�nement
 * @param y Position en y de la souris sur la fen�tre lors du l'�v�nement
 * @return void
 */
void keyboardCallBack(unsigned char key, int x, int y) {
	Coordonnee c(x, y);
	ControllerJeu::getInstance()->keyPressed(key, c);
}

/**
 * Fonction principale, point d'entr�e du programme.
 * @param argc
 * @param argv
 * @return int Statut de l'application
 */
int main(int argc, char** argv)
{
	// Intialisation de glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Initialise les modes li�s � l'affichage
	glutInitWindowSize(LARGEUR_FENETRE_INIT,HAUTEUR_FENETER_INIT); // D�finit la taille de la fen�tre d'�cran
	glutInitWindowPosition(100, 100); // D�finit la position de la fen�tre d'�cran
	glutCreateWindow(NOM_APPLICATION); // Cr�e la fen�tre d'�cran avec le nom pass� en argument
	
	// Chaque call back glut est d�l�gu� � une m�thode de la classe View ou Controller
	// Ceci est n�cessaire car glut ne connait que les fonctions C.
	glutDisplayFunc(displayCallBack);
	glutReshapeFunc(reshapeCallBack);
	glutMouseFunc(mouseCallBack);
	glutSpecialFunc(specialCallBack);
	glutKeyboardFunc(keyboardCallBack);

	// D�marre une boucle �ternelle d'�coute des call back
	glutMainLoop();

   return 0;
}