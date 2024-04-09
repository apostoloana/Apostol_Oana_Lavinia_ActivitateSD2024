#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Heap Heap;
typedef struct Quiz Quiz;

struct Quiz {
    char* numeMaterie;
    int nrGrileGresite;
};

struct Heap {
    Quiz* vector;
    int dimensiune;
    int dimensiuneTotala;
};

Heap initHeap(int nr) {
    Heap heap;
    heap.vector = malloc(sizeof(Quiz) * nr);
    heap.dimensiune = 0;
    heap.dimensiuneTotala = nr;
    return heap;
}

Quiz initQuiz(char* numeMaterie, int nrGrileGresite) {
    Quiz quiz;
    quiz.numeMaterie = malloc(strlen(numeMaterie) + 1);
    strcpy_s(quiz.numeMaterie, strlen(numeMaterie) + 1, numeMaterie);
    quiz.nrGrileGresite = nrGrileGresite;
    return quiz;
}

Heap inserareQuizInHeap(Quiz quiz, Heap heap) {
    if (heap.dimensiune < heap.dimensiuneTotala) {
        heap.vector[heap.dimensiune] = quiz;
        heap.dimensiune++;
    }
    return heap;
}

void afisareQuiz(Quiz q) {
    printf("Materie: %s, Grile gresite: %d\n", q.numeMaterie, q.nrGrileGresite);
}

void afisareHeap(Heap heap) {
    for (int i = 0; i < heap.dimensiune; i++) {
        afisareQuiz(heap.vector[i]);
    }
}

void afisareTotalaHeap(Heap heap) {
    for (int i = 0; i < heap.dimensiuneTotala; i++) {
        afisareQuiz(heap.vector[i]);
    }
}

void filtreazaHeap(Heap heap, int pozRadacina) {
    int pozFiuStanga = 2 * pozRadacina + 1;
    int pozFiuDreapta = 2 * pozRadacina + 2;
    int indexMin = pozRadacina;

    if (pozFiuStanga < heap.dimensiune && heap.vector[pozFiuStanga].nrGrileGresite < heap.vector[indexMin].nrGrileGresite) {
        indexMin = pozFiuStanga;
    }

    if (pozFiuDreapta < heap.dimensiune && heap.vector[pozFiuDreapta].nrGrileGresite < heap.vector[indexMin].nrGrileGresite) {
        indexMin = pozFiuDreapta;
    }

    if (indexMin != pozRadacina) {
        Quiz aux;
        aux = heap.vector[pozRadacina];
        heap.vector[pozRadacina] = heap.vector[indexMin];
        heap.vector[indexMin] = aux;
        if (2 * indexMin + 1 < heap.dimensiune - 1) {
            filtreazaHeap(heap, indexMin);
        }
    }
}

Quiz extragereMinim(Heap* heap) {
    if (heap->dimensiune > 0) {
        Quiz aux;
        aux = heap->vector[0];
        heap->vector[0] = heap->vector[heap->dimensiune - 1];
        heap->vector[heap->dimensiune - 1] = aux;
        heap->dimensiune--;
        for (int i = (heap->dimensiune) / 2 - 1; i >= 0; i--) {
            filtreazaHeap((*heap), i);
        }
        return aux;
    }
    else {
        return initQuiz("N\\A", -1);
    }
}

void dezalocareHeap(Heap* heap) {
    for (int i = 0; i < heap->dimensiuneTotala; i++) {
        free(heap->vector[i].numeMaterie);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->dimensiune = 0;
    heap->dimensiuneTotala = 0;
}

void main() {
    Heap heap;
    heap = initHeap(6);
    heap.vector[0] = initQuiz("SDD", 3);
    heap.vector[1] = initQuiz("JAVA", 7);
    heap.vector[2] = initQuiz("POO", 5);
    heap.vector[3] = initQuiz("SGBD", 2);
    heap.vector[4] = initQuiz("CTS", 9);
    heap.vector[5] = initQuiz("TW", 4);
    heap.dimensiune = 6;

    afisareHeap(heap);
    printf("\n\n");

    for (int i = (heap.dimensiune) / 2 - 1; i >= 0; i--) {
        filtreazaHeap(heap, i);
    }
    afisareHeap(heap);
    printf("\n\n");
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    printf("\n\n");
    afisareTotalaHeap(heap);

    dezalocareHeap(&heap);
}
