#ifndef CARREFOUR
#define CARREFOUR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ipcTools.h"
#include "util.h"

#define T 1000
#define T2 500
#define NB_MAX_VOITURE_DEFAULT 10

//Structure du carrefour
typedef struct Carrefour Carrefour;
struct Carrefour{
	int* muxVoie;
	int muxCarrefour;
	int* feu;
	key_t keyFeu;
	bool* stop;
	int* secondaryTime;
};

//Création du carrefour
Carrefour* init_carrefour(int secondaryTime);

//Arrêt du carrefour
void stop_carrefour(Carrefour* carrefour);

//Libération du carrefour
void free_carrefour(Carrefour* carrefour);

//Lancement du carrefour (en thread)
void* start_feu(void* infos);

//Affichage des messages du carrefour
void print_carrefour_message(char* message);

#endif
