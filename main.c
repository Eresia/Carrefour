#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "GestionVoiture.h"

int main(int argc, char** argv){

	pthread_t threadG;

	pthread_create(&threadG, NULL, threadGestion, NULL);

	pthread_join(threadG, NULL);

	return 0;
}
