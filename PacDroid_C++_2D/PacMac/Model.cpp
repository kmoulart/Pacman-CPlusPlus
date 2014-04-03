// Model.cpp
#include "Model.h"

// Les membres static non constants doient êtres initialisés dans le .cpp
Model *Model::instance = 0;

/*
 * Constructeur du model
 */
Model::Model(){
	pacman = Pacman::getInstance();
	niveau = 1;
	nbrVies = NB_VIES_DEBUT;
	score = 0;
	scoreTotal = 0;
	status = START;
}

/*
 * Renvoi l'unique instance du model (Singleton)
 * @return Model *
 */
Model *Model::getInstance(){
	if (instance == 0)
		instance = new Model();
	return instance;
}

/*
 * Retourne au premier niveau pour une nouvelle partie
 * @return void
 */
void Model::firstLevel() {
	this->niveau = 1;
	this->scoreTotal = 0;
	resetLevel();
}

/*
 * Gagne un niveau
 * @return void
 */
void Model::levelUp() {
	this->niveau++;
	this->scoreTotal = score;
	resetLevel();
}

/*
 * Met le jeu en pause
 * @return void
 */
void Model::pauseUnpause() {
	if (!gameOver())
		this->status *= -1;
}

/*
 * Test si le jeu est actuellement en pause
 * @return bool
 */
bool Model::isPaused() {
	return this->gameOver() || this->status < 0;
}

/*
 * Réinitialise le niveau
 * @return void
 */
void Model::resetLevel() {
	ViewJeu::getInstance()->loadLaby();
	this->status = START;
	score = scoreTotal;
	int i = 0;
	for (Fantome *f = Map::getInstance()->getFantomes(); i < Map::getInstance()->getNbFantomes() ; f++, i++) {
		f->reset();
	}
	pacman->reset();
}

/*
 * Test si le jeu est fini
 * @return bool
 */
bool Model::gameOver() {
	if (this->nbrVies <= 0) {
		pacman->setGameOver(true);
		return true;
	}
	return false;
}

/*
 * Modifie le status du jeu
 * @param int newStatus
 * @return void
 */
void Model::setStatus(int newStatus) {
	this->status = newStatus;
}

/*
 * Décrémente le nombre de vies
 * @return void
 */
void Model::decrementNbrVies() {
	if (this->nbrVies > 0)
		this->nbrVies--;
}

/*
 * Incrémente le nombre de vie
 * @return void
 */
void Model::incrementNbrVies() {
	this->nbrVies++;
}

/*
 * Incrémente le score du joueur
 */
void Model::incrementScore() {
	this->score++;
}