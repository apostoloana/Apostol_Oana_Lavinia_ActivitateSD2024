#include<stdio.h>
#include<malloc.h>

typedef struct Cafenea Cafenea;
typedef struct Nod Nod;

struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};

struct Nod {
	Cafenea info;
	Nod* next;
};

Cafenea initCafenea(const char* nume, int nrLocuri, float suprafata) {
	Cafenea cafe;
	cafe.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	//cafe.nume = malloc(strlen(nume)+1);
	strcpy(cafe.nume, nume);
	cafe.nrLocuri = nrLocuri;
	cafe.suprafata = suprafata;

	return cafe;
}

Nod* inserareLaInceput(Cafenea c, Nod* cap) {
	Nod* nou = malloc(sizeof(Nod));
	nou->next = cap;
	nou->info = initCafenea(c.nume, c.nrLocuri, c.suprafata);
	return nou;
}


void afisareCafenea(Cafenea c) {
	printf("Nume: %s, Nr scaune: %d, Suprafata: %5.2F\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* lista) {
	while (lista != NULL) {
		afisareCafenea(lista->info);
		lista = lista->next;
	}
}

char* numeCafDensitateMica(Nod* lista) {
	if (lista) {
		if (lista->info.suprafata != 0) {
			float minim = lista->info.nrLocuri / lista->info.suprafata;
			Nod* adresa = lista;
			lista = lista->next;
			while (lista != NULL) {
				if (lista->info.nrLocuri / lista->info.suprafata < minim) {
					minim = lista->info.nrLocuri / lista->info.suprafata;
					adresa = lista;
				}
				lista = lista->next;
			}
			char* nume = malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
			strcpy(nume, adresa->info.nume);

			return nume;
		}
	}
	return NULL;
}


void inserareLaFinal(Nod** lista, Cafenea c) {
	if ((*lista) == NULL) {
		(*lista) = inserareLaInceput(c, *lista);
	}
	else {
		Nod* curent = (*lista);
		while (curent->next != NULL) {
			curent = curent->next;
		}
		Nod* n = (Nod*)malloc(sizeof(Nod));
		n->info = initCafenea(c.nume, c.nrLocuri, c.suprafata);
		n->next = NULL;
		curent->next = n;
	}
}


void stergeLista(Nod** nod) {
	while (*nod != NULL) {
		Nod* aux = *nod; 
		*nod = (*nod)->next; 
		free(aux->info.nume);
		free(aux); 
	}
}


void main() {

	Nod* cap = NULL;

	Cafenea cafe1 = initCafenea("Tucano", 10, 20);
	Cafenea cafe2 = initCafenea("Starbucks", 20, 30);
	Cafenea cafe3 = initCafenea("5ToGo", 5, 10);

	cap = inserareLaInceput(cafe1, cap);
	cap = inserareLaInceput(cafe2, cap);
	cap = inserareLaInceput(cafe3, cap);

	afisareCafenele(cap);

	char* numeMin = numeCafDensitateMica(cap);
	printf("\nCafeneaua cu dens minima: %s\n\n", numeMin);

	Cafenea cafe4 = initCafenea("Teds", 15, 30);
	inserareLaFinal(&cap, cafe4);
	afisareCafenele(cap);

	stergeLista(&cap);
	afisareCafenele(cap);

	free(cafe1.nume);
	cafe1.nume = NULL;

	free(cafe2.nume);
	cafe2.nume = NULL;

	free(cafe3.nume);
	cafe3.nume = NULL;

	free(cafe4.nume);
	cafe4.nume = NULL;
}