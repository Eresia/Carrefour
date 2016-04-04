#include "Carrefour.h"

Carrefour* init_carrefour(){
	Carrefour* c = (Carrefour*) malloc(sizeof(Carrefour));
	c->keyMuxCarrefour = ftok("/etc/passwd", 1);
	c->keyMuxVoie = ftok("/etc/passwd", 2);
	c->keyFeu = ftok("/etc/passwd", 3);
	c->stop = malloc(sizeof(bool));
	*c->stop = false;
	return c;
}

void stop_carrefour(Carrefour* carrefour){
	*carrefour->stop = true;
}

void free_carrefour(Carrefour* carrefour, int* feu){
	free(carrefour->stop);
	shmfree(carrefour->keyFeu, feu);
	free(carrefour);
}

void* start_feu(void* infos){

	Carrefour* carrefour = (Carrefour*) infos;
	bool* stop = carrefour->stop;
	char* message = malloc(100*sizeof(char));
	int* feu = shmalloc(carrefour->keyFeu, sizeof(int));

	*feu = 0;

	while(!*stop){
		usleep(T*1000);
		sprintf(message, "Le feu %d passe au rouge", *feu);
		print_carrefour_message(message);
		sprintf(message, "Le feu %d passe au vert", !*feu);
		print_carrefour_message(message);
		*feu = !*feu;
	}

	free_carrefour(carrefour, feu);
	pthread_exit(NULL);
}

void print_carrefour_message(char* message){
	printf("CARREFOUR : %s\n", message);
}
