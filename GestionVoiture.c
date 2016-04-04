#include "GestionVoiture.h"

void* threadGestion(void *arg){

	int nbvoitureMax = 10;
	int nbVoiture = 0;

	char* buf = (char*) malloc(1);

	while(nbVoiture < nbvoitureMax){
		read(0, buf, 1);
		if(*buf == 'a'){
			printf("VOITURE : La voiture %d est en attente voie 1\n", nbVoiture);
		}
		else if(*buf == 'z'){
			printf("VOITURE : La voiture %d est en attente voie 2\n", nbVoiture);
		}
	}
	
	pthread_exit(NULL);
}
