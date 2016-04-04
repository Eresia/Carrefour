#include "GestionVoiture.h"

int* start_gestion(Carrefour* carrefour, bool automatique){

	int nbVoitureMax = NB_MAX_VOITURE;
	int nbVoiture = 0;

	int* pidFils = malloc(nbVoitureMax*sizeof(int));

	if(automatique){
		srand(time(NULL));
		while(nbVoiture < nbVoitureMax){
			Voiture* newVoiture;
			int voie;
			int delay = rand()%((ARRIVE_MAX+1) - ARRIVE_MIN) + ARRIVE_MIN;
			usleep(delay);

			voie = rand()%2;

			newVoiture = start_voiture(nbVoiture+1, voie, carrefour, pidFils + nbVoiture);
			if(newVoiture != NULL){
				enterCarrefour(newVoiture);
				return NULL;
			}
			nbVoiture++;
		}
	}
	else{
		char* buf = (char*) malloc(sizeof(char));
		do{
			*buf = '\0';
			read(0, buf, 1);
			if(*buf == 'a'){
				Voiture* newVoiture;
				newVoiture = start_voiture(nbVoiture+1, 0, carrefour, pidFils + nbVoiture);
				if(newVoiture != NULL){
					enterCarrefour(newVoiture);
					return NULL;
				}
				nbVoiture++;
			}
			else if(*buf == 'z'){
				Voiture* newVoiture;
				newVoiture = start_voiture(nbVoiture+1, 1, carrefour, pidFils + nbVoiture);
				if(newVoiture != NULL){
					enterCarrefour(newVoiture);
					return NULL;
				}
				nbVoiture++;
			}
		}while(nbVoiture < nbVoitureMax && *buf != '\0');
	}

	return pidFils;
}
