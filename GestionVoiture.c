#include "GestionVoiture.h"

int* threadGestion(Carrefour* carrefour){

	int nbVoitureMax = NB_MAX_VOITURE;
	int nbVoiture = 0;

	char* buf = (char*) malloc(sizeof(char));
	Voiture* newVoiture;
	int* pidFils = malloc(nbVoitureMax*sizeof(int));

	do{
		*buf = '\0';
		read(0, buf, 1);
		if(*buf == 'a'){
			newVoiture = start_voiture(nbVoiture+1, 0, carrefour, pidFils + nbVoiture);
			if(newVoiture != NULL){
				enterCarrefour(newVoiture);
				return NULL;
			}
			nbVoiture++;
		}
		else if(*buf == 'z'){
			newVoiture = start_voiture(nbVoiture+1, 1, carrefour, pidFils + nbVoiture);
			if(newVoiture != NULL){
				enterCarrefour(newVoiture);
				return NULL;
			}
			nbVoiture++;
		}
	}while(nbVoiture < nbVoitureMax && *buf != '\0');

	return pidFils;
}
