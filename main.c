#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "Carrefour.h"
#include "GestionVoiture.h"

int main(int argc, char** argv){

	pthread_t threadC;
	int* pidFils = NULL;

	bool automatique = false;
	int nbVoitureMax = NB_MAX_VOITURE_DEFAULT;
	int secondaryTime = T2;

	int i;

	//Parsage des paramètres
	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-a") == 0){
			automatique = true;
		}
		else if(strcmp(argv[i], "-t") == 0){
			if(i != (argc-1)){
				int temp = atoi(argv[i+1]);
				if(temp != 0){
					secondaryTime = temp;
				}
				i++;
			}
		}
		else if(strcmp(argv[i], "-n") == 0){
			if(i != (argc-1)){
				int temp = atoi(argv[i+1]);
				if(temp != 0){
					nbVoitureMax = temp;
				}
				i++;
			}
		}
	}

	//Création du carrefour
	Carrefour* carrefour = init_carrefour(secondaryTime);

	if(carrefour == NULL){
		return -1;
	}

	//Lancement du carrefour
	pthread_create(&threadC, NULL, start_feu, carrefour);

	//Lancement de la gestion des voitures
	pidFils = start_gestion(carrefour, nbVoitureMax, automatique);

	//Si on est dans le père
	if(pidFils != NULL){
		int i;
		//On attends que les fils finissent
		for(i = 0; i < nbVoitureMax; i++){
			while(waitpid(pidFils[i], 0, 0) < 0);
		}

		//On affiche l'état de fin
		printf("FIN : Les %d voitures sont passées\n", nbVoitureMax);

		//On arrête le carrefour
		stop_carrefour(carrefour);

		pthread_join(threadC, NULL);
	}
	return 0;
}
