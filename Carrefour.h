#ifndef CARREFOUR
#define CARREFOUR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ipcTools.h"
#include "util.h"

#define T 2000

typedef struct Carrefour Carrefour;
struct Carrefour{
	int muxVoie;
	int muxCarrefour;
	int* feu;
	bool* stop;
};

Carrefour* init_carrefour();
void stop_carrefour(Carrefour* carrefour);
void free_carrefour(Carrefour* carrefour);

void* start_feu(void* infos);

#endif
