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
#include "Voiture.h"
int* threadGestion(Carrefour* carrefour);

#endif
