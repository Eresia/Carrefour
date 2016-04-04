#include "Voiture.h"

Voiture* start_voiture(int id, int voie, Carrefour* carrefour){

	if(fork() == 0){
		Voiture* v = malloc(sizeof(Voiture));
		v->keyFeu = carrefour->keyFeu;
		v->keyMuxVoie = carrefour->keyMuxVoie;
		v->keyMuxCarrefour = carrefour->keyMuxCarrefour;
		v->voie = voie;
		v->id = id;

		return v;
	}
	else{
		return NULL;
	}

}

void enterCarrefour(Voiture* voiture){
	key_t keyFeu = voiture->keyFeu;
	key_t keyMuxVoie = voiture->keyMuxVoie;
	key_t keyMuxCarrefour = voiture->keyMuxCarrefour;

	int* feu = shmalloc(keyFeu, sizeof(int));
	int muxVoie = mutalloc(keyMuxVoie);
	int muxCarrefour = mutalloc(keyMuxCarrefour);

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
	shmfree(keyFeu, feu);
	mutfree(muxVoie);
	mutfree(muxCarrefour);
	free(voiture);
}

void print_voiture_message(char* message){
	printf("\tVOITURE : %s\n", message);
}
