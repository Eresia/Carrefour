#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Carrefour.h"
#include "GestionVoiture.h"

int main(int argc, char** argv){

	pthread_t threadG;
	pthread_t threadC;
	int* result;

	Carrefour* carrefour = init_carrefour();

	pthread_create(&threadC, NULL, start_feu, carrefour);
	pthread_create(&threadG, NULL, threadGestion, carrefour);

	pthread_join(threadG, (void**) &result);

	if(*result == 0){
		stop_carrefour(carrefour);

		pthread_join(threadC, NULL);

		while(waitpid(0, 0, 0) < 0);
	}

	return 0;
}
