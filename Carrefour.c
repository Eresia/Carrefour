#include "Carrefour.h"

Carrefour* init_carrefour(){
	Carrefour* c = (Carrefour*) malloc(sizeof(Carrefour));
	key_t keyMuxCarrefour = ftok("/etc/passwd", 1);
	key_t keyMuxVoie = ftok("/etc/passwd", 2);
	c->feu = malloc(sizeof(int));
	*c->feu = -1;
	c->stop = malloc(sizeof(bool));
	*c->stop = false;
	c->muxCarrefour = mutalloc(keyMuxCarrefour + 1);
	c->muxVoie = mutalloc(keyMuxVoie + 1);
	return c;
}

void stop_carrefour(Carrefour* carrefour){
	*carrefour->stop = true;
}

void free_carrefour(Carrefour* carrefour){
	free(carrefour->feu);
	free(carrefour->stop);
	mutfree(carrefour->muxCarrefour);
	mutfree(carrefour->muxVoie);
	free(carrefour);
}

void* start_feu(void* infos){

	Carrefour* carrefour = (Carrefour*) infos;
	int* feu = carrefour->feu;
	bool* stop = carrefour->stop;

	*feu = 0;
	while(!*stop){
		usleep(T);
		*feu = !*feu;
	}

	pthread_exit(NULL);
}
