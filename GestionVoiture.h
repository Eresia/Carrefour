#ifndef GESTIONVOITURE
#define GESTIONVOITURE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include "Carrefour.h"
#include "util.h"
#include "Voiture.h"

#define ARRIVE_MAX 1000000
#define ARRIVE_MIN 1000

int* start_gestion(Carrefour* carrefour, int nbVoitureMax, bool automatique);

#endif
