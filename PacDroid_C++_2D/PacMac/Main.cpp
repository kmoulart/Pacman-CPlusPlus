//Main.cpp
#include "Model.h"
#include "View.h"
#include "ControllerJeu.h"

#define NOM_APPLICATION "PacTron"

/*
 * Fonctions C appell�e chaque fois que la vue est redessin�e
 * @return void
 */
void displayCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	View::getInstance()->display();
	glutSwapBuffers();
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur redimensionne la fen�tre
 * @param int width
 * @param int height
 * @return void
 */
void reshapeCallBack(int width, int height)
{
	View::getInstance()->reshape(width, height);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur sollicite la souris
 * @param int button
 * @param int state
 * @param int x
 * @param int y
 * @return void
 */
void mouseCallBack(int button, int state, int x, int y)
{
	ControllerButton::getInstance()->mouse(button, state, x, y);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur appuie sur une touche sp�cial du clavier
 * @param int key
 * @param int x
 * @param int y
 * @return void
 */
void specialCallBack(int key, int x, int y)
{
	ControllerJeu::getInstance()->keyPressed(key, x, y);
}

/*
 * Fonctions C appell�e chaque fois que l'utilisateur appuie sur une touche du clavier
 * @param unsigned int key
 * @param int x
 * @param int y
 * @return void
 */
void keyboardCallBack(unsigned char key, int x, int y) {
	ControllerJeu::getInstance()->keyPressed(key, x, y);
}

int main(int argc, char** argv)
{	
	// Intialisation de glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Initialise les modes li�s � l'affichage
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

	// Le controller est un singleton
	ControllerJeu::getInstance();

	// D�marre une boucle �ternelle d'�coute des call back
	glutMainLoop();

   return 0;
}