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
	char* message = malloc(100*sizeof(char));
	sprintf(message, "Arrivee de la voiture %d sur la voie %d", voiture->id, voiture->voie);
	print_voiture_message(message);
	P(muxVoie);
	sprintf(message, "La voiture %d arrive au feu", voiture->id);
	print_voiture_message(message);

	while(*feu != voiture->voie){
		usleep(WAIT*1000);
	}

	sprintf(message, "La voiture %d est engagée", voiture->id);
	print_voiture_message(message);
	P(muxCarrefour);
	sprintf(message, "La voiture %d passe", voiture->id);
	print_voiture_message(message);
	V(muxVoie);
	usleep(TIME_IN_CARR*1000);
	sprintf(message, "La voiture %d est passée", voiture->id);
	print_voiture_message(message);
	V(muxCarrefour);
	free(voiture);
}

void print_voiture_message(char* message){
	printf("\tVOITURE : %s\n", message);
}
