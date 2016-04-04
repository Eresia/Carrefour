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

typedef struct Carrefour Carrefour;
struct Carrefour{
	int* muxVoie;
	int muxCarrefour;
	int* feu;
	key_t keyFeu;
	bool* stop;
	int* secondaryTime;
};

Carrefour* init_carrefour(int secondaryTime);
void stop_carrefour(Carrefour* carrefour);
void free_carrefour(Carrefour* carrefour);

void* start_feu(void* infos);

void print_carrefour_message(char* message);

#endif
