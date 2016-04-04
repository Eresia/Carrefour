#ifndef VOITURE
#define VOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipcTools.h"
#include "Carrefour.h"

#define WAIT 20
#define TIME_IN_CARR 1000

typedef struct Voiture Voiture;
struct Voiture{
		int id;
		key_t keyMuxVoie;
		key_t keyMuxCarrefour;
		key_t keyFeu;
		int voie;
};

Voiture* start_voiture(int id, int voie, Carrefour* carrefour);
void enterCarrefour(Voiture* voiture);

void print_voiture_message(char* message);

#endif
