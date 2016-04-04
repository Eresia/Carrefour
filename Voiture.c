#include "Voiture.h"

Voiture* start_voiture(int id, int voie, key_t keyFeu, key_t keySemVoie, key_t keySemCar){

	if(fork() == 0){
		Voiture* v = malloc(sizeof(Voiture));
		int* feu = shmalloc(keyFeu, sizeof(int));
		int* semVoie = (int*) shmalloc(keySemVoie, sizeof(int));
		int* semCar = (int*) shmalloc(keySemVoie, sizeof(int));
		v->feu = feu;
		v->semVoie = semVoie;
		v->semCar = semCar;
		v->id = id;
		v->voie = voie;

		return v;
	}
	else{
		return NULL;
	}

}

void enterCarrefour(Voiture* voiture){
	P(*voiture->semVoie);
	printf("VOITURE : arrivee de la voiture %d sur la voie %d", voiture->id, voiture->voie);
}
