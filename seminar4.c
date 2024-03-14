#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Locuinta Locuinta;

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserareLocuinta(struct Locuinta** vector, int* dim,
	struct Locuinta l)
{
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) *
		(++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++)
	{
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL)
	{
		free((*vector));
	}
	(*vector) = copie;
}

void citesteFisier(const char* nume_fisier, struct Locuinta** vector,
	int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				inserareLocuinta(vector, dim, locuinta);
			}
			fclose(f);
		}
	}
}


void citesteMatriceFisier(const char* nume_fisier, Locuinta** matrice, int nrLinii, int* nrCol)  
{
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);

				
				int poz = locuinta.numar % 2;
				inserareLocuinta(&(matrice[poz]), &(nrCol[poz]), locuinta);
			}
			fclose(f);
		}
	}
}

void afisareLocuinta(struct Locuinta l) {
	printf("ID-ul: %d\t%s numarul %d\t",
		l.id, l.strada, l.numar);
}
void afisareVectorLocuinte(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++)
		afisareLocuinta(vector[i]);
}

void afisareMatrice(Locuinta** matrice, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			afisareLocuinta(matrice[i][j]);
		}
		printf("\n");
	}

}


void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) { 
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta)
			* ((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		if ((*vector) != NULL)
		{
			free((*vector));
		}
		(*vector) = copie;
	}
}

afisareIDDePeOParte(int par, Locuinta** matrice, int nrLinii, int* nrCol) {
	par = par % 2;
	for (int j = 0; j < nrCol[par]; j++) {
		printf("Id: %d", (matrice[par][j]).id);
	}
}

Locuinta cautareLocDupaId(Locuinta** matrice, int idCautat, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if ((matrice[i][j]).id == idCautat) {
				return matrice[i][j];
			}
		}
	}
	Locuinta copie;
	copie.id = -1;
	copie.numar = -1;
	copie.strada = NULL;

	return copie;
}

void schimbareNrLocuinta(Locuinta** matrice, int nrLinii, int* nrCol, int nrLoc) {
	int pozitie = nrLoc % 2;
	int idLoc = -1;
	int indexInVector = -1;
	for (int i = 0; i < nrCol[pozitie]; i++) {
		if (matrice[pozitie][i].numar == nrLoc) 
		{
			matrice[pozitie][i].numar++;
			idLoc = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}
	if (idLoc != -1) {
		int index = (nrLoc + 1) % 2;
		inserareLocuinta(&(matrice[index]), &(nrCol[index]), matrice[pozitie][indexInVector]);
		stergeLocuinta(&(matrice[pozitie]), &(nrCol[pozitie]), idLoc);
	}

}

void dezalocareMatrice(Locuinta*** matrice, int nrLinii, int** nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrCol)[i]; j++) {
			free((*matrice)[i][j].strada);
			
		}
		free((*matrice)[i]);
	}

	free(*matrice);
	*matrice = NULL;
	nrLinii = 0;
	free(*nrCol);
	*nrCol = NULL; 
}

void main() {
	int nrLinii;
	int* nrCol;
	Locuinta** matrice;

	nrLinii = 2;
	nrCol = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (Locuinta**)malloc(sizeof(Locuinta*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		matrice[i] = NULL;
		nrCol[i] = 0;
	}


	citesteMatriceFisier("locuinte.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);

	printf("Id-urile: \n");
	afisareIDDePeOParte(11, matrice, nrLinii, nrCol);

	printf("\nCautare dupa id: %d \n");
	Locuinta loc1 = cautareLocDupaId(matrice, 22, nrLinii, nrCol);
	afisareLocuinta(loc1);

	dezalocareMatrice(&matrice, nrLinii, &nrCol);

}

