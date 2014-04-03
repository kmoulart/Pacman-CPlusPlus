// Utils.cpp

#include "Utils.h"
#include <cmath>

/**
 * Arrondi la valeur passée en paramètre
 * @param i Valeur à arrondir
 * @return int Valeur arrondi
 */
int Utils::round(float i) {
	if (i < ((int) i) + 0.5f)
		return (int) i;
	return (int) ceil(i);
}

/**
 * Arrondi la valeur passée en parametre a 2 decimales
 * @param i Valeur à arrondir
 * @return float Arrondi à 2 decimals
 */
float Utils::floor2Decimal(float i) {
	return floor((i + 0.005f) * 100) / 100.0f;
}
