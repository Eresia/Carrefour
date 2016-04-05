#ifndef VOITURE
#define VOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipcTools.h"
#include "Carrefour.h"

#define WAIT 20
#define TIME_IN_CARR 100

//Structure des voitures
typedef struct Voiture Voiture;
struct Voiture{
		int id;
		int muxVoie;
		int muxCarrefour;
		int* feu;
		int voie;
};

//Création des voitures
Voiture* start_voiture(int id, int voie, Carrefour* carrefour, int* pid);

//Entrée dans le carrefour
void enterCarrefour(Voiture* voiture);

//Affichage des messages des voitures
void print_voiture_message(char* message);

#endif
