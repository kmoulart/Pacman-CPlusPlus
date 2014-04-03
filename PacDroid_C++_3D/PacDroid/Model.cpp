// Model.cpp

#include "Model.h"
#include "ViewJeu2D.h"
#include "FantomeView.h"
#include "MapView.h"
#include "Constantes.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
Model *Model::instance = 0;

/**
 * Constructeur vide du model
 */
Model::Model(){
	pacman = PacmanView::getInstance();
	niveau = 1;
	nbrVies = NB_VIES_DEBUT;
	score = 0;
	scoreTotal = 0;
	status = PAUSE;
}

/**
 * Renvoi l'unique instance du model (Application du pattern singleton)
 * @return Model* Pointeur vers l'instance unique de la classe
 */
Model *Model::getInstance(){
	if (instance == 0)
		instance = new Model();
	return instance;
}

/**
 * Retourne au premier niveau pour une nouvelle partie
 * @return void
 */
void Model::firstLevel() {
	this->niveau = 1;
	this->scoreTotal = 0;
	this->nbrVies = NB_VIES_DEBUT;
	resetLevel();
}

/**
 * Gagne un niveau
 * @return void
 */
void Model::levelUp() {
	this->niveau++;
	this->scoreTotal = score;
	resetLevel();
}

/**
 * Met le jeu en pause ou le relance
 * @return void
 */
void Model::pauseUnpause() {
	if (!gameOver())
		this->status *= -1;
}

/**
 * Test si le jeu est actuellement en pause
 * @return bool Vrai ou faux si le jeu est en pause ou non
 */
bool Model::isPaused() {
	return this->gameOver() || this->status < 0;
}

/**
 * Réinitialise le niveau
 * @return void
 */
void Model::resetLevel() {
	ViewJeu2D::getInstance()->loadLaby();
	this->status = START;
	score = scoreTotal;
	MapView::getInstance()->setRotation(false);
	MapView::getInstance()->setAngle(0);
	int i = 0;
	for (FantomeView *f = MapView::getInstance()->getFantomes(); i < MapView::getInstance()->getNbFantomes() ; f++, i++) {
		f->reset();
	}
	pacman->reset();
}

/**
 * Test si le jeu est fini
 * @return bool Vérifie si le jeu est en game over ou non
 */
bool Model::gameOver() {
	if (this->nbrVies <= 0) {
		pacman->setMort(true);
		return true;
	}
	return false;
}

/**
 * Modifie le status du jeu
 * @param newStatus Nouveau status du jeu
 * @return void
 */
void Model::setStatus(int newStatus) {
	this->status = newStatus;
}

/**
 * Décrémente le nombre de vies
 * @return void
 */
void Model::decrementNbrVies() {
	// Si le joueur n'a plus de vies, on le transfère juste dans un écran de game overt
	if (this->nbrVies - 1 <= 0)
		this->niveau = NIVEAU_GAME_OVER;
	else if (this->nbrVies > 0)
		this->nbrVies--;
}

/**
 * Incrémente le nombre de vie
 * @return void
 */
void Model::incrementNbrVies() {
	this->nbrVies++;
}

/**
 * Incrémente le score du joueur
 * @return void
 */
void Model::incrementScore() {
	this->score++;
}