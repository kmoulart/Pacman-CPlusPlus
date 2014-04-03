// PastilleModel.h
#pragma once

#include "Entite.h"

class PastilleModel : public Entite {
protected:
	// Pastille ou super pastille
	int type;
public:
	// Constructeur
	PastilleModel(Coordonnee coord, int type);
};