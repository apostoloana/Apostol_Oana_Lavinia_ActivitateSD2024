#include<stdio.h>
#include <malloc.h>
typedef struct CafeneaMea Cafenea;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct CafeneaMea
{
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct NodLdi {
    Cafenea info;
    NodLdi* urmator;
    NodLdi* anterior;
};

struct ListaDubla {
    NodLdi* cap;
    NodLdi* coada;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata)
{
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

void initLaInceput(Cafenea c, ListaDubla* lista) 
{
    if (lista != NULL) {
        NodLdi* nou = malloc(sizeof(NodLdi));
        nou->anterior = NULL;
        nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
        nou->urmator = lista->cap;
        if (lista->cap != NULL) {
            lista->cap->anterior = nou;
        }
        else {
            lista->coada = nou;
        }
        lista->cap = nou;
    }
}


void afisareCafenea(Cafenea c)
{
    printf("\nDenumire: %s Nr scaune: %i Suprafara %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareListaDublaDeLaInceput(ListaDubla ListaCafenele) 
{
    NodLdi* aux = ListaCafenele.cap; 
    while (aux) {
        afisareCafenea(aux->info); 
        aux = aux->urmator; 
    }
    printf("\n");
}

//stergem cafeneaua dupa nume
ListaDubla stergeCafeneaDupaNume(ListaDubla lista, const char* nume) 
{
    if (nume == NULL) {
        return lista;
    }
    NodLdi* nod = lista.cap;
    while (nod && strcmp(nod->info.nume, nume) != 0) {
        nod = nod->urmator;
    }
    if (nod != NULL) {
        if (nod->urmator == NULL && nod->anterior == NULL) {
            lista.cap = NULL;
            lista.coada = NULL;
        }
        else {
            if (nod->anterior == NULL) {
                lista.cap = nod->urmator;
                lista.cap->anterior = NULL;
            }
            else if (nod->urmator == NULL) {
                lista.coada = nod->anterior;
                lista.coada->urmator = NULL;
            }
            else {
                nod->anterior->urmator = nod->urmator;
                nod->urmator->anterior = nod->anterior;
            }
        }
        free(nod->info.nume);
        free(nod);
    }

    return lista;
}

ListaDubla stergereLD(ListaDubla listaCafenele) {
    NodLdi* aux = listaCafenele.cap;
    while (aux) {
        free(aux->info.nume);
        NodLdi* temp = aux->urmator;
        free(aux);
        aux = temp;
    }
    listaCafenele.cap = NULL;
    listaCafenele.coada = NULL;

    return listaCafenele;
}

int nrTotalLocuri(ListaDubla listaD) {
    if (listaD.cap == NULL) {
        return 0;
    }
    int nrLocuri = 0;
    NodLdi* nod = listaD.coada;
    while (nod != NULL) {
        nrLocuri += nod->info.nrLocuri;
        nod = nod->anterior;
    }
    return nrLocuri;
}


void main()
{
    ListaDubla ld;
    ld.cap = NULL;
    ld.coada = NULL;

    Cafenea cafe = initializareCafenea("Tucano", 12, 20);
    Cafenea cafe2 = initializareCafenea("Teds", 17, 17.3);
    Cafenea cafe3 = initializareCafenea("Urban", 65, 33);
    Cafenea sb = initializareCafenea("Sb", 25, 43);

    initLaInceput(cafe, &ld);
    initLaInceput(cafe2, &ld);
    initLaInceput(cafe3, &ld);
    initLaInceput(sb, &ld);

    afisareListaDublaDeLaInceput(ld);
    printf("\n-------------------------------Stergere---------------------------------\n");

    /*ld = stergeCafeneaDupaNume(ld, "Teds");
    afisareListaDublaDeLaInceput(ld);
    ld = stergeCafeneaDupaNume(ld, "Tucano");
    afisareListaDublaDeLaInceput(ld);
    ld = stergeCafeneaDupaNume(ld, "Starbucks");
    afisareListaDublaDeLaInceput(ld);
    ld = stergeCafeneaDupaNume(ld, "Sb");
    afisareListaDublaDeLaInceput(ld);
    ld = stergeCafeneaDupaNume(ld, "Urban");
    afisareListaDublaDeLaInceput(ld);*/

    printf("\n-----------------------------Nr total Locuri-----------------------------------\n");
    printf("Nr locuri total: %d", nrTotalLocuri(ld));

    printf("\n-----------------------------Sterge LD-----------------------------------\n");
    ld = stergereLD(ld);
    afisareListaDublaDeLaInceput(ld);


}
