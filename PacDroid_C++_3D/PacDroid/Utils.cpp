// Utils.cpp

#include "Utils.h"
#include <cmath>

/**
 * Arrondi la valeur pass�e en param�tre
 * @param i Valeur � arrondir
 * @return int Valeur arrondi
 */
int Utils::round(float i) {
	if (i < ((int) i) + 0.5f)
		return (int) i;
	return (int) ceil(i);
}

/**
 * Arrondi la valeur pass�e en parametre a 2 decimales
 * @param i Valeur � arrondir
 * @return float Arrondi � 2 decimals
 */
float Utils::floor2Decimal(float i) {
	return floor((i + 0.005f) * 100) / 100.0f;
}
