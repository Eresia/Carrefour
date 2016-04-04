#ifndef VOITURE
#define VOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipcTools.h"
#include "Carrefour.h"

#define WAIT 20
#define TIME_IN_CARR 200

typedef struct Voiture Voiture;
struct Voiture{
		int id;
		int muxVoie;
		int muxCarrefour;
		int* feu;
		int voie;
};

Voiture* start_voiture(int id, int voie, Carrefour* carrefour, int* pid);
void enterCarrefour(Voiture* voiture);

void print_voiture_message(char* message);

#endif
