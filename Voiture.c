#include "Voiture.h"

Voiture* start_voiture(int id, int voie, Carrefour* carrefour){

	if(fork() == 0){
		Voiture* v = malloc(sizeof(Voiture));
		v->feu = carrefour->feu;
		v->muxVoie = carrefour->muxVoie;
		v->muxCarrefour = carrefour->muxCarrefour;
		v->voie = voie;
		v->id = id;

		return v;
	}
	else{
		return NULL;
	}

}

void enterCarrefour(Voiture* voiture){
	int* feu = voiture->feu;
	int muxVoie = voiture->muxVoie;
	int muxCarrefour = voiture->muxCarrefour;
	printf("VOITURE : arrivee de la voiture %d sur la voie %d\n", voiture->id, voiture->voie);
	P(muxVoie);
	printf("VOITURE : La voiture %d arrive au feu\n", voiture->id);

	while(*feu != voiture->voie){
		usleep(WAIT*1000);
	}

	printf("VOITURE : La voiture %d est engagée\n", voiture->id);
	P(muxCarrefour);
	printf("VOITURE : La voiture %d passe\n", voiture->id);
	V(muxVoie);
	usleep(TIME_IN_CARR*1000);
	printf("VOITURE : La voiture %d est passée\n", voiture->id);
	V(muxCarrefour);
}
