//Main.cpp
#include "Model.h"
#include "View.h"
#include "ControllerJeu.h"

#define NOM_APPLICATION "PacTron"

/*
 * Fonctions C appellée chaque fois que la vue est redessinée
 * @return void
 */
void displayCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	View::getInstance()->display();
	glutSwapBuffers();
}

/*
 * Fonctions C appellée chaque fois que l'utilisateur redimensionne la fenêtre
 * @param int width
 * @param int height
 * @return void
 */
void reshapeCallBack(int width, int height)
{
	View::getInstance()->reshape(width, height);
}

/*
 * Fonctions C appellée chaque fois que l'utilisateur sollicite la souris
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
 * Fonctions C appellée chaque fois que l'utilisateur appuie sur une touche spécial du clavier
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
 * Fonctions C appellée chaque fois que l'utilisateur appuie sur une touche du clavier
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Initialise les modes liés à l'affichage
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

	// Le controller est un singleton
	ControllerJeu::getInstance();

	// Démarre une boucle éternelle d'écoute des call back
	glutMainLoop();

   return 0;
}