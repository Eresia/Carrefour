#ifndef VOITURE
#define VOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipcTools.h"

#define WAIT 20
#define TIME_IN_CARR 100

enum bool {false = 0, true = 1};

typedef struct Voiture Voiture;
struct Voiture{
		int id;
		key_t keyMuxVoie;
		key_t keyMuxCarrefour;
		key_t keyFeu;
		int voie;
};

Voiture* start_voiture(int id, int voie, key_t keyFeu, key_t keyMuxVoie, key_t keyMuxCarrefour);
void enterCarrefour(Voiture* voiture);

#endif
