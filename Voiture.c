#include "Voiture.h"

Voiture* start_voiture(int id, int voie, key_t keyFeu, key_t keyMuxVoie, key_t keyMuxCarrefour){

	if(fork() == 0){
		Voiture* v = malloc(sizeof(Voiture));
		v->keyFeu = keyFeu;
		v->keyMuxVoie = keyMuxVoie;
		v->keyMuxCarrefour = keyMuxCarrefour;
		v->id = id;
		v->voie = voie;

		return v;
	}
	else{
		return NULL;
	}

}

void enterCarrefour(Voiture* voiture){
	int* feu = shmalloc(voiture->keyFeu, sizeof(int));
	int* muxVoie = (int*) shmalloc(voiture->keyMuxVoie, sizeof(int));
	int* muxCarrefour = (int*) shmalloc(voiture->keyMuxCarrefour, sizeof(int));
	printf("VOITURE : arrivee de la voiture %d sur la voie %d\n", voiture->id, voiture->voie);
	P(*muxVoie);
	printf("VOITURE : La voiture %d arrive au feu\n", voiture->id);

	while(*feu != voiture->voie){
		usleep(WAIT);
	}

	printf("VOITURE : La voiture %d est engagée\n", voiture->id);
	P(*muxCarrefour);
	printf("VOITURE : La voiture %d passe\n", voiture->id);
	V(*muxVoie);
	usleep(TIME_IN_CARR);
	printf("VOITURE : La voiture %d est passée\n", voiture->id);
	V(*muxCarrefour);
	shmfree(voiture->keyMuxVoie, muxCarrefour);
	shmfree(voiture->keyMuxCarrefour, muxCarrefour);
	shmfree(voiture->keyFeu, feu);
}
