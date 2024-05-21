#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Metrou Metrou;
typedef struct NodPrincipal NodP;
typedef struct NodSecundar NodS;

struct Metrou {
	int serie;
	int nrStatii;
	char* magistrala;
};

struct NodPrincipal {
	Metrou info;
	NodP* next;
	NodS* vecini;
};

struct NodSecundar {
	NodP* nod;
	NodS* next;
};

//initMetrou
Metrou initMetrou(int serie, int nrStatii, const char* magistrala) {
	Metrou m;
	m.serie = serie;
	m.nrStatii = nrStatii;
	m.magistrala = malloc(strlen(magistrala) + 1);
	strcpy(m.magistrala, magistrala);

	return m;
}

//inserareInListaPLaInceput
void inserareInListaPLaInceput(NodP** cap, Metrou m) {
	NodP* nou = (NodP*)malloc(sizeof(NodP));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}

// functie cautaNodDupaSerie
NodP* cautaNodDupaSerie(NodP* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}

//inserareInListaSLaFinal
NodS* inserareInListaSecLaFinal(NodS* cap, NodP* nod) {
	NodS* nou = (NodS*)malloc(sizeof(NodS));
	nou->next = NULL;
	nou->nod = nod;
	if (cap) {
		NodS* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

//functie de inserareMuchie
void inserareMuchie(NodP* graf, int serieStart, int serieStop) {
	NodP* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodP* nodStop = cautaNodDupaSerie(graf, serieStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareInListaSecLaFinal(nodStart->vecini, nodStop);
		nodStop->vecini = inserareInListaSecLaFinal(nodStop->vecini, nodStart);
	}
}

//afisare


//dezalocare

void main() {
	NodP* graf = NULL;

	Metrou m4 = initMetrou(4, 4, "M2");
	Metrou m3 = initMetrou(3, 7, "M1");
	Metrou m2 = initMetrou(2, 8, "M4");
	Metrou m1 = initMetrou(1, 12, "M3");
	Metrou m0 = initMetrou(0, 4, "M5");

	inserareInListaPLaInceput(&graf, m4);
	inserareInListaPLaInceput(&graf, m3);
	inserareInListaPLaInceput(&graf, m2);
	inserareInListaPLaInceput(&graf, m1);
	inserareInListaPLaInceput(&graf, m0);

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);

}
