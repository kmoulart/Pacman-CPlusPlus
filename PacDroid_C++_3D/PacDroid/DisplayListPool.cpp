// DisplayListPool.cpp

#include "DisplayListPool.h"
#include "Constantes.h"
#include "MyGlut.h"

using namespace glut;

// Les membres static non constants doivent êtres initialisés dans le .cpp
DisplayListPool *DisplayListPool::instance = 0;

/**
 * Construteur vide de DisplayListPool
 */
DisplayListPool::DisplayListPool() {
	// Définis les diplays lists
	idLists = glGenLists(NB_DISPLAY_LIST); // Obtiens NB_DISPLAY_LIST Ids pour les NB_DISPLAY_LIST listes
}

/**
 * Renvoi l'unique instance du DisplayListPool (Application du pattern singleton)
 * @return DisplayListPool* Pointeur vers l'instance unique de la classe
 */
DisplayListPool *DisplayListPool::getInstance() {
	if (DisplayListPool::instance == 0 )
		instance = new DisplayListPool();
	return instance;
}

/**
 * Renvoie la display liste souhaitée
 * @param nomList Nom de la display liste souhaitée
 * @return int Nom de la display liste
 */
int DisplayListPool::getList(int nomList) {
	return idLists + nomList;
}
