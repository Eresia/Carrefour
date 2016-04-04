#include "GestionVoiture.h"

void* threadGestion(void *arg){

	int nbvoitureMax = 10;
	int nbVoiture = 1;

	char* buf = (char*) malloc(1);
	Voiture* newVoiture;
	Carrefour* carr = (Carrefour*) arg;

	while(nbVoiture <= nbvoitureMax){
		read(0, buf, 1);
		if(*buf == 'a'){
			//printf("\tVOITURE : La voiture %d est en attente voie 1\n", nbVoiture);
			newVoiture = start_voiture(nbVoiture, 1, carr);
			if(newVoiture == NULL) return 0;
			else{
				enterCarrefour(newVoiture);
			}
			nbVoiture++;
		}
		else if(*buf == 'z'){
			//printf("\tVOITURE : La voiture %d est en attente voie 2\n", nbVoiture);
			newVoiture = start_voiture(nbVoiture, 2, carr);
			if(newVoiture == NULL) return 0;
			else{
				enterCarrefour(newVoiture);
			}
			nbVoiture++;
		}
	}

	printf("FIN : Les %d voitures sont passées\n", nbvoitureMax);

	pthread_exit(NULL);
}
