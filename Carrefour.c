#include "Carrefour.h"

//Création du carrefour
Carrefour* init_carrefour(int secondaryTime){
	Carrefour* c = (Carrefour*) malloc(sizeof(Carrefour));

	//Génération des clés
	key_t keyMuxCarrefour = ftok("/etc/passwd", 0);
	key_t keyMuxVoie0 = ftok("/etc/passwd", 1);
	key_t keyMuxVoie1 = ftok("/etc/passwd", 2);
	c->keyFeu = ftok("/etc/passwd", 3);

	//Allocation des feux
	c->feu = shmalloc(c->keyFeu, sizeof(int));
	if(c->feu == (int*) -1){
		perror("Erreur dans la création du feu");
		return NULL;
	}
	*c->feu = -1;

	//Allocation du stop
	c->stop = malloc(sizeof(bool));
	*c->stop = false;

	//Allocation du mutex pour le carrefour
	c->muxCarrefour = mutalloc(keyMuxCarrefour + 1);

	//Allocation des mutex pour chaque voie
	c->muxVoie = malloc(2*sizeof(int));
	c->muxVoie[0] = mutalloc(keyMuxVoie0 + 1);
	c->muxVoie[1] = mutalloc(keyMuxVoie1 + 1);
	if((c->muxVoie[0] == -1) || (c->muxVoie[1] == -1)){
		perror("Erreur dans la création des voies");
		return NULL;
	}

	//Allocation du temps de la voie secondaire
	c->secondaryTime = malloc(sizeof(int));
	*c->secondaryTime = secondaryTime;

	return c;
}

//Arrêt du carrefour
void stop_carrefour(Carrefour* carrefour){
	*carrefour->stop = true;
}

//Libération du carrefour
void free_carrefour(Carrefour* carrefour){
	free(carrefour->stop);
	shmfree(carrefour->keyFeu, carrefour->feu);
	mutfree(carrefour->muxCarrefour);
	mutfree(carrefour->muxVoie[0]);
	mutfree(carrefour->muxVoie[1]);
	free(carrefour);
}

//Lancement du carrefour (en thread)
void* start_feu(void* infos){
	Carrefour* carrefour = (Carrefour*) infos;
	int* feu = carrefour->feu;
	bool* stop = carrefour->stop;
	char* message = malloc(100*sizeof(char));

	//Initialisation du feu
	*feu = 0;
	sprintf(message, "Le feu %d passe au rouge", !*feu);
	print_carrefour_message(message);
	sprintf(message, "Le feu %d passe au vert", *feu);
	print_carrefour_message(message);

	//Tant qu'on a pas toppé le carrefour
	while(!*stop){
		int i;

		//On attribue le temps d'attente
		if(*feu == 0){
			i = T*1000;
		}
		else{
			i = *carrefour->secondaryTime*1000;
		}

		//On l'attend
		do{
			usleep(100);
			i -= 100;
		}while(i > 0 && !*stop);

		//Et change de feu
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

//Affichage des messages du carrefour
void print_carrefour_message(char* message){
	printf("CARREFOUR : %s\n", message);
}
