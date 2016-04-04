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

	Carrefour* carrefour = init_carrefour();

	pthread_create(&threadC, NULL, start_feu, carrefour);
	pthread_create(&threadG, NULL, threadGestion, NULL);

	sleep(5);

	stop_carrefour();

	pthread_join(threadG, NULL);
	pthread_join(threadC, NULL);

	free_carrefour(carrefour);

	while(waitpid(0, 0, 0) < 0);

	return 0;
}
