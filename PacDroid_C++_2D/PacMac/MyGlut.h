//MyGlut.h

/* 
 * Cette "encapsulation" des includes des librairies glut et gl est n�cessaire pour �viter un probl�me de red�finition
 * d'une m�thode d'une librairie standard (la fonction "exit"), qui provoque l'erreur suivante :
 * Error C2381: 'exit' : redefinition; __declspec(noreturn) differs Z:/include\GL\glut.h(146) : see declaration of 'exit.
 */
namespace glut{
#include "GL/glut.h"
#include "gl/gl.h"
}
