#include "GestionVoiture.h"

void* threadGestion(void *arg){

	int nbvoitureMax = 10;
	int nbVoiture = 1;

	char* buf = (char*) malloc(sizeof(char));
	int* result = (int*) malloc(sizeof(int));
	Voiture* newVoiture;
	Carrefour* carr = (Carrefour*) arg;

	do{
		*buf = '\0';
		read(0, buf, 1);
		if(*buf == 'a'){
			//printf("\tVOITURE : La voiture %d est en attente voie 1\n", nbVoiture);
			newVoiture = start_voiture(nbVoiture, 0, carr);
			if(newVoiture != NULL){
				enterCarrefour(newVoiture);
				*result = 1;
				pthread_exit(result);
			}
			nbVoiture++;
		}
		else if(*buf == 'z'){
			//printf("\tVOITURE : La voiture %d est en attente voie 2\n", nbVoiture);
			newVoiture = start_voiture(nbVoiture, 1, carr);
			if(newVoiture != NULL){
				enterCarrefour(newVoiture);
				*result = 1;
				pthread_exit(result);
			}
			nbVoiture++;
		}
	}while(nbVoiture <= nbvoitureMax && *buf != '\0');

	printf("FIN : Les %d voitures sont passées\n", nbvoitureMax);

	pthread_exit(NULL);
}
