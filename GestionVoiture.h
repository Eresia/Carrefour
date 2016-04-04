#ifndef GESTIONVOITURE
#define GESTIONVOITURE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

void* threadGestion(void *arg){

	int nbvoitureMax = 10;
	int nbVoiture = 0;

	char* buf = (char*) malloc(1);

	while(nbVoiture < nbvoitureMax){
		read(0, buf, 1);
		if(*buf == 'a'){
			printf("VOITURE : La voiture %d est en attente voie 1\n", nbvoiture);
		}
		else if(*buf == 'z'){
			printf("VOITURE : La voiture %d est en attente voie 2\n", nbvoiture);
		}
	}

	(void) arg;
	pthread_exit(NULL);
}

#endif
