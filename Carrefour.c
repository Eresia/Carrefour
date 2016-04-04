#include "Carrefour.h"

Carrefour* init_carrefour(int secondaryTime){
	Carrefour* c = (Carrefour*) malloc(sizeof(Carrefour));
	key_t keyMuxCarrefour = ftok("/etc/passwd", 0);
	key_t keyMuxVoie0 = ftok("/etc/passwd", 1);
	key_t keyMuxVoie1 = ftok("/etc/passwd", 2);
	c->keyFeu = ftok("/etc/passwd", 3);

	c->feu = shmalloc(c->keyFeu, sizeof(int));
	if(c->feu == (int*) -1){
		perror("Erreur dans la création du feu");
		return NULL;
	}
	*c->feu = -1;

	c->stop = malloc(sizeof(bool));
	*c->stop = false;

	c->muxCarrefour = mutalloc(keyMuxCarrefour + 1);

	c->muxVoie = malloc(2*sizeof(int));
	c->muxVoie[0] = mutalloc(keyMuxVoie0 + 1);
	c->muxVoie[1] = mutalloc(keyMuxVoie1 + 1);
	if((c->muxVoie[0] == -1) || (c->muxVoie[1] == -1)){
		perror("Erreur dans la création des voies");
		return NULL;
	}

	c->secondaryTime = malloc(sizeof(int));
	*c->secondaryTime = secondaryTime;

	return c;
}

void stop_carrefour(Carrefour* carrefour){
	*carrefour->stop = true;
}

void free_carrefour(Carrefour* carrefour){
	free(carrefour->stop);
	shmfree(carrefour->keyFeu, carrefour->feu);
	mutfree(carrefour->muxCarrefour);
	mutfree(carrefour->muxVoie[0]);
	mutfree(carrefour->muxVoie[1]);
	free(carrefour);
}

void* start_feu(void* infos){
	Carrefour* carrefour = (Carrefour*) infos;
	int* feu = carrefour->feu;
	bool* stop = carrefour->stop;
	char* message = malloc(100*sizeof(char));

	*feu = 0;
	sprintf(message, "Le feu %d passe au rouge", !*feu);
	print_carrefour_message(message);
	sprintf(message, "Le feu %d passe au vert", *feu);
	print_carrefour_message(message);

	while(!*stop){
		int i;
		if(*feu == 0){
			i = T*1000;
		}
		else{
			i = *carrefour->secondaryTime*1000;
		}
		do{
			usleep(100);
			i -= 100;
		}while(i > 0 && !*stop);
		if(!*stop){
			sprintf(message, "Le feu %d passe au rouge", *feu);
			print_carrefour_message(message);
			sprintf(message, "Le feu %d passe au vert", !*feu);
			print_carrefour_message(message);
			*feu = !*feu;
		}
	}

	pthread_exit(NULL);
}

void print_carrefour_message(char* message){
	printf("CARREFOUR : %s\n", message);
}
