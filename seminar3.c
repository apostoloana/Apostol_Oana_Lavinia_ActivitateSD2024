#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h> 

typedef struct Locuinta Locuinta;

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserareLocuinta(Locuinta** vector, int* dim, Locuinta loc) {
	Locuinta* nou = malloc(sizeof(Locuinta) * ((*dim) + 1)); 
	for (int i = 0; i < (*dim); i++) {
		nou[i] = (*vector)[i]; 
	}
	nou[(*dim)] = loc;
	(*dim)++;
	if ((*vector) != NULL) {
		free((*vector));
	}
	(*vector) = nou;

}


void citesteFisier(const char* nume_fisier, Locuinta** vector, int* dim) 
{
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r"); 
		if (f != NULL) {
			(*dim) = 0; 
			
			char buffer[100];
			
			char delimitator[] = ",\n";

			
			while (fgets(buffer, 100, f) != NULL) 
			{
				
				char* token;
				
				token = strtok(buffer, delimitator); 
				
				Locuinta locuinta;
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

void afisareLocuinta(Locuinta l) {
	printf("ID: %d | Strada: %s | Numarul: %d\n", l.id, l.strada, l.numar);
}

void afisareVectorLocuinta(Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareLocuinta(vector[i]);
	}
}

void stergeLocuinta(Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		Locuinta* copie = (Locuinta*)malloc(sizeof(Locuinta) * ((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) 
			{
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		if ((*vector) != NULL) {
			free((*vector));
		}
		(*vector) = copie;

	}
}

void main() {
	Locuinta* loc = NULL;
	int nr = 0;
	citesteFisier("locuinta.txt", &loc, &nr);
	afisareVectorLocuinta(loc, nr);

	printf("\n---------Stergere Locuinta------------------\n");

	stergeLocuinta(&loc, &nr, 10);
	afisareVectorLocuinta(loc, nr);


}