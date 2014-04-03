// PastilleModel.cpp

#include "PastilleModel.h"

/**
 * Constructeur d'une pastille
 * @param coord Coordonnée de la pastille
 * @param type Type de pastille
 */
PastilleModel::PastilleModel(Coordonnee coord, int type) : Entite(coord, Couleur()) {
	this->type = type;
}