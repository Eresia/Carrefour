#ifndef VOITURE
#define VOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipcTools.h"

enum bool {false = 0, true = 1};

typedef struct Voiture Voiture;
struct Voiture{
		int id;
		int* semVoie;
		int* semCar;
		int* feu;
		int voie;
};

Voiture* start_voiture(int id, int voie, key_t feu, key_t keySemVoie, key_t keySemCar);
void enterCarrefour(Voiture* voiture);
#endif
