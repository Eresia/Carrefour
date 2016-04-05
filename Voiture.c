#include "Voiture.h"

//Création des voitures
Voiture* start_voiture(int id, int voie, Carrefour* carrefour, int* pid){

	//On fork et on rempli la structure si c'est le fils
	if((*pid = fork()) == 0){
		Voiture* v = malloc(sizeof(Voiture));
		v->feu = carrefour->feu;
		v->muxVoie = carrefour->muxVoie[voie];
		v->muxCarrefour = carrefour->muxCarrefour;
		v->voie = voie;
		v->id = id;
		return v;
	}
	//Ou on renvoit null si c'est le père
	else{
		return NULL;
	}

}

//Entrée dans le carrefour
void enterCarrefour(Voiture* voiture){

	int* feu = voiture->feu;
	int muxVoie = voiture->muxVoie;
	int muxCarrefour = voiture->muxCarrefour;
	char* message = malloc(100*sizeof(char));
	sprintf(message, "Arrivee de la voiture %d sur la voie %d", voiture->id, voiture->voie);
	print_voiture_message(message);

	//On demande l'accès à la première place du feu
	P(muxVoie);
	sprintf(message, "La voiture %d arrive au feu", voiture->id);
	print_voiture_message(message);

	//On attend que le feu passe au vert
	while(*feu != voiture->voie){
		usleep(WAIT*1000);
	}

	sprintf(message, "La voiture %d est engagée", voiture->id);
	print_voiture_message(message);

	//On demande le carrefour
	P(muxCarrefour);
	sprintf(message, "La voiture %d passe", voiture->id);
	print_voiture_message(message);

	//On libère la première place du feu
	V(muxVoie);

	//On passe
	usleep(TIME_IN_CARR*1000);
	sprintf(message, "La voiture %d est passée", voiture->id);
	print_voiture_message(message);

	//On libère le carrefour
	V(muxCarrefour);

	//On continu sa route
	free(voiture);
}

//Affichage des messages des voitures
void print_voiture_message(char* message){
	printf("\tVOITURE : %s\n", message);
}
