#include "GestionVoiture.h"

//Fonction de gestion de la création de voitures
int* start_gestion(Carrefour* carrefour, int nbVoitureMax, bool automatique){

	int nbVoiture = 0;

	int* pidFils = malloc(nbVoitureMax*sizeof(int));

	//Si en mode automatique
	if(automatique){
		srand(time(NULL));
		//Tant qu'on a pas dépassé le nombre de voitures nécessaires
		while(nbVoiture < nbVoitureMax){
			Voiture* newVoiture;
			int voie;
			//On attend un temps au hasard
			int delay = rand()%((ARRIVE_MAX+1) - ARRIVE_MIN) + ARRIVE_MIN;
			usleep(delay);

			//On chosiit une voie au hasard
			voie = rand()%2;

			//On créé la voiture sur cette voie
			newVoiture = start_voiture(nbVoiture+1, voie, carrefour, pidFils + nbVoiture);
			if(newVoiture != NULL){
				//Et on la fait entrer dans le carrefour
				enterCarrefour(newVoiture);
				return NULL;
			}
			nbVoiture++;
		}
	}
	//Si en mode manuel
	else{
		char* buf = (char*) malloc(sizeof(char));
		//Tant qu'on a pas dépassé le nombre de voitures nécessaires
		do{
			*buf = '\0';
			//On lit l'entrée standart
			read(0, buf, 1);
			//Si on rentre a
			if(*buf == 'a'){
				Voiture* newVoiture;
				//On créé la voiture sur la voie 0
				newVoiture = start_voiture(nbVoiture+1, 0, carrefour, pidFils + nbVoiture);
				if(newVoiture != NULL){
					//Et on la fait entrer dans le carrefour
					enterCarrefour(newVoiture);
					return NULL;
				}
				nbVoiture++;
			}
			//Si on rentre z
			else if(*buf == 'z'){
				Voiture* newVoiture;
				//On créé la voiture sur la voie 1
				newVoiture = start_voiture(nbVoiture+1, 1, carrefour, pidFils + nbVoiture);
				if(newVoiture != NULL){
					//Et on la fait entrer dans le carrefour
					enterCarrefour(newVoiture);
					return NULL;
				}
				nbVoiture++;
			}
		}while(nbVoiture < nbVoitureMax && *buf != '\0');
	}

	return pidFils;
}
