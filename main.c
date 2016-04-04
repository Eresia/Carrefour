#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Carrefour.h"
#include "GestionVoiture.h"

int main(int argc, char** argv){

	pthread_t threadC;
	int* pidFils = NULL;

	Carrefour* carrefour = init_carrefour();

	if(carrefour == NULL){
		return -1;
	}

	pthread_create(&threadC, NULL, start_feu, carrefour);

	pidFils = start_gestion(carrefour, true);

	if(pidFils != NULL){
		int i;
		for(i = 0; i < NB_MAX_VOITURE; i++){
			while(waitpid(pidFils[i], 0, 0) < 0);
		}

		printf("FIN : Les %d voitures sont passées\n", NB_MAX_VOITURE);

		stop_carrefour(carrefour);

		pthread_join(threadC, NULL);
	}
	return 0;
}
