#include<stdio.h>
#include<malloc.h>

typedef struct Avion Avion;

struct Avion {
	int nrPasageri;
	char* companie;
	float pretBilet;
};

Avion initAvion(int nrPasageri, const char* companie, float pretBilet) {
	Avion avion;
	avion.nrPasageri = nrPasageri;
	avion.companie = (char*)malloc(sizeof(char)* strlen(companie) + 1);
	strcpy(avion.companie, companie);
	avion.pretBilet = pretBilet;
	return avion;
}

void afisareAvion(Avion avion) {
	printf("\nNume Companie: %s", avion.companie);
	printf("\nNr Pasageri: %d", avion.nrPasageri);
	printf("\nPret Bilet: %5.2F", avion.pretBilet);
}

void afisareVectAvioane(Avion* avioane, int nrAvioane)
{
	for (int i = 0; i < nrAvioane; i++) {
		afisareAvion(avioane[i]);
	}

}

Avion* copiazaPrimeleNAvioane(Avion* avioane, int nrAvioane, int nrAvioaneCopiate) {
	if (nrAvioaneCopiate < nrAvioane && nrAvioaneCopiate>0) {
		Avion* avioaneCopiate = (Avion*)malloc(sizeof(Avion)* nrAvioaneCopiate);
		for (int i = 0; i < nrAvioaneCopiate; i++) {
			avioaneCopiate[i] = initAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet); 
		}

		return avioaneCopiate;
	}
	else {
		return NULL;
	}
}

void dezalocare(Avion** avioane, int* nrAvioane)
{
	if ((*avioane) != NULL) {
		for (int i = 0; i < *nrAvioane; i++) {
			free((*avioane)[i].companie); 
		}
		free(*avioane); 
		*nrAvioane = 0; 
		*avioane = NULL; 
	}

}

void copiazaAvioaneCuBileteReduse(Avion* avioane, int nrAvioane, float pragPret, struct Avion** avioaneNoi, int* dimensiune) 
{
	if (*avioaneNoi != NULL) {
		dezalocare(avioaneNoi, dimensiune);
	}
	else {
		*dimensiune = 0;
	}
	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].pretBilet < pragPret) {
			(*dimensiune)++;
		}
	}
	*avioaneNoi = (Avion*)malloc(sizeof(Avion)*(*dimensiune));
	int k = 0;
	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].pretBilet < pragPret) {
			(*avioaneNoi)[k++] = initAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet);
		}
	}

}

Avion getPrimulAvionDupaNumeCompanie(Avion* avioane, int nrAvioane, const char* companie)
{
	if (avioane != NULL && companie != NULL) {
		for (int i = 0; i < nrAvioane; i++) {
			if (avioane[i].companie != NULL) {
				if (strcmp(avioane[i].companie, companie) == 0) {
					return initAvion(avioane[i].nrPasageri, avioane[i].companie, avioane[i].pretBilet);
				}

			}

		}
	}
	else {
		return initAvion(-1, "N\A", -1);
	}
}

void main() {
	int nrAvioane = 5;
	Avion* vectAvioane = (Avion*)malloc(sizeof(Avion)*nrAvioane); 

	for (int i = 0; i < nrAvioane; i++) {
		vectAvioane[i] = initAvion(i + 50, "Tarom", 10 * i + 40);
	}

	afisareVectAvioane(vectAvioane, nrAvioane);
	printf("\n------------------------------------------------------\n");


	int nrAvCopiate = 3;
	Avion* avioaneCopiate = copiazaPrimeleNAvioane(vectAvioane, nrAvioane, nrAvCopiate);
	afisareVectAvioane(avioaneCopiate, nrAvCopiate);
	printf("\n------------------------------------------------------\n");

	Avion* avioaneCuBileteReduse = NULL;
	int nrAvioaneCuBileteReduse = 0;

	vectAvioane[4].pretBilet = 50;

	copiazaAvioaneCuBileteReduse(vectAvioane, nrAvioane, 60, &avioaneCuBileteReduse, &nrAvioaneCuBileteReduse);
	afisareVectAvioane(avioaneCuBileteReduse, nrAvioaneCuBileteReduse);
	printf("\n------------------------------------------------------\n");

	Avion avion = getPrimulAvionDupaNumeCompanie(vectAvioane, nrAvioane, "Tarom");
	printf("\nAvion cautat: ");
	afisareAvion(avion);



	dezalocare(&vectAvioane, &nrAvioane);
	dezalocare(&avioaneCopiate, &nrAvCopiate);
	dezalocare(&avioaneCuBileteReduse, &nrAvioaneCuBileteReduse);
	free(avion.companie);
}

