#ifndef CARREFOUR
#define CARREFOUR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ipcTools.h"
#include "util.h"

#define T 5000
#define NB_MAX_VOITURE 10

typedef struct Carrefour Carrefour;
struct Carrefour{
	int* muxVoie;
	int muxCarrefour;
	int* feu;
	key_t keyFeu;
	bool* stop;
};

Carrefour* init_carrefour();
void stop_carrefour(Carrefour* carrefour);
void free_carrefour(Carrefour* carrefour);

void* start_feu(void* infos);

void print_carrefour_message(char* message);

#endif
